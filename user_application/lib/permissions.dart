import 'dart:io';
import 'package:permission_handler/permission_handler.dart';

Future<bool> requestBlePermissions() async {

  if (!Platform.isAndroid) return true;
  final scan = await Permission.bluetoothScan.request();
  final connect = await Permission.bluetoothConnect.request();
  final location = await Permission.location.request();
  final ok =
      (scan.isGranted || scan.isLimited) &&
          (connect.isGranted || connect.isLimited) &&
          (location.isGranted || location.isLimited);

  return ok;
}
