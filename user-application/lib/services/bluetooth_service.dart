import 'dart:async';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import '../models/activity.dart';
import '../utils/ble_parsing.dart';

class BluetoothService {

  static const _envLikePacketLen = 8;

  final StreamController<Activity> _activityCtl = StreamController.broadcast();
  Stream<Activity> get activityStream => _activityCtl.stream;

  Future<void> startScan({Duration timeout = const Duration(seconds: 6)}) async {
    await FlutterBluePlus.startScan(timeout: timeout);
  }

  Stream<List<ScanResult>> get scanResults => FlutterBluePlus.scanResults;

  Future<void> stopScan() => FlutterBluePlus.stopScan();

  Future<void> connect(BluetoothDevice device) async {
    await device.connect();
    await _discoverAndSubscribe(device);
  }

  Future<void> _discoverAndSubscribe(BluetoothDevice d) async {
    final services = await d.discoverServices();
    for (final s in services) {
      for (final c in s.characteristics) {
        if (c.properties.notify) {
          await c.setNotifyValue(true);
          c.lastValueStream.listen((value) {

            if (value.length >= _envLikePacketLen) {
              final act = parseActivityFromEnvironmentalPacket(value);
              _activityCtl.add(act);
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
}
