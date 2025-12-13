import 'package:flutter/material.dart';
import 'permissions.dart';

import 'services/bluetooth_service.dart' as custom;
import 'viewmodels/scan_view_model.dart';
import 'ui/screens/home_menu_screen.dart';



// ГЛОБАЛЬНІ SINGLETON-и
final custom.BluetoothService ble = custom.BluetoothService();
final ScanViewModel vm = ScanViewModel(ble);

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await requestBlePermissions();


  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {

    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: HomeMenuScreen(ble: ble, vm: vm),
    );
  }
}
