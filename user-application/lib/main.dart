import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'permissions.dart';
import 'dart:typed_data'; // залишаємо, якщо десь знадобиться

import 'services/bluetooth_service.dart' as custom;
import 'viewmodels/scan_view_model.dart';
import 'ui/screens/scan_screen.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});
  @override
  Widget build(BuildContext context) {
    final ble = custom.BluetoothService();

    final vm  = ScanViewModel(ble);


    Future.microtask(() async {
      final granted = await requestBlePermissions();
      if (granted) {
        await vm.startScan();
      }
    });

    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: ScanScreen(vm: vm),
    );
  }
}
