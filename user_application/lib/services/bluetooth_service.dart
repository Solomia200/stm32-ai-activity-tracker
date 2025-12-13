import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

import '../models/activity.dart';
import '../models/activity_entry.dart';
import '../models/activity_record.dart';
import '../db/activity_database.dart';


class BluetoothService extends ChangeNotifier {
  // ---- BLE STATE ----
  bool isConnected = false;
  final StreamController<bool> _connectionCtl =
  StreamController<bool>.broadcast();
  Stream<bool> get connectionStream => _connectionCtl.stream;

  // ---- ACTIVITY STREAM ----
  final StreamController<ActivityEntry> _activityCtl =
  StreamController<ActivityEntry>.broadcast();
  Stream<ActivityEntry> get activityStream => _activityCtl.stream;

  // ---- TIME SYNC ----
  int? _timeOffsetSec;

  // Characteristic UUID (environmental-like)
  static final Guid envUuid =
  Guid("00140000-0001-11e1-ac36-0002a5d5c51b");

  // -------------------------------
  // START SCAN
  // -------------------------------
  Future<void> startScan() async {
    if (FlutterBluePlus.isScanningNow) return;

    await FlutterBluePlus.startScan(
      androidUsesFineLocation: true,
    );
  }


  Stream<List<ScanResult>> get scanResults => FlutterBluePlus.scanResults;

  Future<void> stopScan() async {
    if (FlutterBluePlus.isScanningNow) {
      await FlutterBluePlus.stopScan();
    }
  }


  // -------------------------------
  // CONNECT
  // -------------------------------
  Future<void> connect(BluetoothDevice device) async {
    print("📡 Connecting to ${device.remoteId}...");

    // IMPORTANT: Start listening *before* connecting
    device.connectionState.listen((state) {
      print("🔵 DEVICE STATE = $state");

      if (state == BluetoothConnectionState.connected) {
        if (!isConnected) {
          isConnected = true;
          _connectionCtl.add(true);
          notifyListeners();
          print("🔵 UI notified: CONNECTED");
        }
      } else {
        if (isConnected) {
          isConnected = false;
          _connectionCtl.add(false);
          notifyListeners();
          print("🔴 UI notified: DISCONNECTED");
        }
      }
    });

    try {
      await device.disconnect();
    } catch (_) {}

    await device.connect(autoConnect: false);

    // Must be called to initialize services!
    await device.discoverServices();

    print("✅ Connected & services discovered!");

    await _discoverAndSubscribe(device);
  }

  // -------------------------------
  // DISCOVER SERVICES & SUBSCRIBE
  // -------------------------------
  Future<void> _discoverAndSubscribe(BluetoothDevice d) async {
    final services = await d.discoverServices();

    for (final s in services) {
      for (final c in s.characteristics) {
        print("CHAR FOUND: ${c.uuid} notify=${c.properties.notify}");

        if (c.properties.notify) {
          print("➡️ SUBSCRIBING TO ${c.uuid}");
          await c.setNotifyValue(true);

          c.lastValueStream.listen((value) {
            print("📩 RAW PACKET FROM ${c.uuid}: $value");

            // Filter only our environmental-like characteristic
            if (c.uuid.toString().toLowerCase() ==
                envUuid.toString().toLowerCase()) {
              print("🟢 DETECTED SYNC PACKET");
              handleSyncPacket(value);
            }
          });
        }
      }
    }
  }

  // -------------------------------
  // DISCONNECT
  // -------------------------------
  Future<void> disconnect(BluetoothDevice d) async {
    await d.disconnect();
    isConnected = false;
    _connectionCtl.add(false);
    notifyListeners();
  }

  // -------------------------------
  // PACKET PARSING HELPERS
  // -------------------------------
  int _readUint32LE(List<int> data, int offset) {
    return data[offset] |
    (data[offset + 1] << 8) |
    (data[offset + 2] << 16) |
    (data[offset + 3] << 24);
  }

  int _readUint16LE(List<int> data, int offset) {
    return data[offset] | (data[offset + 1] << 8);
  }

  String _activityName(int id) {
    switch (id) {
      case 0: return "walking";
      case 1: return "running";
      case 2: return "climbing_down";
      case 3: return "climbing_up";
      case 4: return "lying";
      case 5: return "sitting";
      case 6: return "standing";
      default: return "unknown";
    }
  }

  // -------------------------------
  // HANDLE SYNC PACKET (8 bytes)
  // -------------------------------
  Future<void> handleSyncPacket(List<int> packet) async {
    if (packet.length != 8) {
      print("⚠ Invalid packet: $packet");
      return;
    }

    final relTime = _readUint32LE(packet, 0);
    final activityId = _readUint16LE(packet, 4);
    final activity = _activityName(activityId);

    // ---- Time synchronisation ----
    if (_timeOffsetSec == null) {
      final nowUnix = DateTime.now().millisecondsSinceEpoch ~/ 1000;
      _timeOffsetSec = nowUnix - relTime;
      print("⏱ OFFSET SET = $_timeOffsetSec sec");
    }

    final realUnix = relTime + (_timeOffsetSec ?? 0);
    final realDate = DateTime.fromMillisecondsSinceEpoch(realUnix * 1000);

    print("📦 SYNC RECORD:");
    print(" → relativeTime: $relTime");
    print(" → activity: $activity ($activityId)");
    print(" → realTime: $realDate");

    // Save to local DB
    final record = ActivityRecord(
      activityClass: activity,
      timestamp: realDate,
    );

    await ActivityDatabase.instance.insertRecord(record);

    print("💾 Saved: ${record.activityClass} at ${record.timestamp}");
  }
}
