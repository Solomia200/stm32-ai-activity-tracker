import 'dart:async';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import '../models/activity.dart';
import '../utils/ble_parsing.dart';
import '../models/activity_entry.dart';

class BluetoothService {

  static const _envLikePacketLen = 8;

  final StreamController<ActivityEntry> _activityCtl =
  StreamController<ActivityEntry>.broadcast();
  int? _timeOffsetSec;
  int? _lastUnix;
  int? _lastRel;

  Stream<ActivityEntry> get activityStream => _activityCtl.stream;

  Future<void> startScan({Duration timeout = const Duration(seconds: 6)}) async {
    await FlutterBluePlus.startScan(timeout: timeout);
  }

  Stream<List<ScanResult>> get scanResults => FlutterBluePlus.scanResults;

  Future<void> stopScan() => FlutterBluePlus.stopScan();

  Future<void> connect(BluetoothDevice device) async {
    print("📡 Connecting to device ${device.remoteId}...");

    try {
      await device.disconnect();
    } catch (_) {}

    await device.connect(autoConnect: false);

    print("✅ Connected!");
    await _discoverAndSubscribe(device);
  }

  static final Guid envUuid =
  Guid("00140000-0001-11e1-ac36-0002a5d5c51b");


  Future<void> _discoverAndSubscribe(BluetoothDevice d) async {
    final services = await d.discoverServices();

    for (final s in services) {
      for (final c in s.characteristics) {

        // Логи щоб бачити все
        print("CHAR FOUND: ${c.uuid} notify=${c.properties.notify}");

        // Підписуємося на ВСІ, що мають notify
        if (c.properties.notify) {
          print("➡️ SUBSCRIBING TO ${c.uuid}");
          await c.setNotifyValue(true);

          c.lastValueStream.listen((value) {
            print("📩 RAW PACKET FROM ${c.uuid}: $value");
            if (c.uuid.toString().toLowerCase() == envUuid.toString().toLowerCase()) {
              print("🟢 DETECTED SYNC PACKET — decoding...");
              handleSyncPacket(value);
            }
          });
        }
      }
    }
  }


  Future<void> disconnect(BluetoothDevice d) => d.disconnect();

  void dispose() {
    _activityCtl.close();
  }


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

  void handleSyncPacket(List<int> packet) {
    if (packet.length != 8) {
      print("⚠ Invalid packet (not 8 bytes): $packet");
      return;
    }

    // timestamp (4 bytes)
    final relTime = _readUint32LE(packet, 0);

    // activity (2 bytes)
    final activityId = _readUint16LE(packet, 4);
    final activity = _activityName(activityId);

    // Розрахунок offset при першому пакеті
    if (_timeOffsetSec == null) {
      final nowUnix = DateTime.now().millisecondsSinceEpoch ~/ 1000;
      _timeOffsetSec = nowUnix - relTime;
      print("⏱ Calculated offset: $_timeOffsetSec sec");
    }

    // Обчислюємо реальний Unix Time
    final realUnix = relTime + (_timeOffsetSec ?? 0);

    final realDate =
    DateTime.fromMillisecondsSinceEpoch(realUnix * 1000);

    print("📦 SYNC RECORD:");
    print(" → relativeTime: $relTime sec");
    print(" → activity: $activity ($activityId)");
    print(" → realTime: $realDate");
  }
}

