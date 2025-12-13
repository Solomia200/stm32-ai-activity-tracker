import 'package:flutter/foundation.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import '../models/activity.dart';
import '../services/bluetooth_service.dart' as custom;

import 'dart:async';


class ScanViewModel extends ChangeNotifier {
  Stream<List<ScanResult>> get scanResults => _ble.scanResults;

  final custom.BluetoothService _ble;
  ScanViewModel(this._ble) {
    _subs.add(_ble.scanResults.listen((r) {
      _results = r;
      notifyListeners();
    }));
    _subs.add(_ble.activityStream.listen((entry) {
      _currentActivity = entry.activity;
      _currentTimestamp = entry.timestamp;
      notifyListeners();
    }));
  }

  final List<StreamSubscription> _subs = [];
  List<ScanResult> _results = [];
  List<ScanResult> get results => _results;



  Activity _currentActivity = Activity.unknown;
  Activity get currentActivity => _currentActivity;

  int _currentTimestamp = 0;
  int get currentTimestamp => _currentTimestamp;

  Future<void> startScan() async {
    if (FlutterBluePlus.isScanningNow) {
      debugPrint("Scan already running");
      return;
    }

    await _ble.startScan();
  }


  Future<void> stopScan() async {
    if (FlutterBluePlus.isScanningNow) {
      await _ble.stopScan();
    }
  }


  Future<void> connect(BluetoothDevice d) async {
    await _ble.stopScan();
    await _ble.connect(d);
  }

  @override
  void dispose() {
    for (final s in _subs) { s.cancel(); }
    _ble.dispose();
    super.dispose();
  }
}
