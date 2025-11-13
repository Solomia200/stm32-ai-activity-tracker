import 'dart:typed_data';
import '../models/activity.dart';


Activity parseActivityFromEnvironmentalPacket(List<int> value) {
  if (value.length < 8) return Activity.unknown;

  final bytes = Uint8List.fromList(value);
  final bd = ByteData.sublistView(bytes);

  final code = bd.getInt16(6, Endian.little);

  switch (code) {
    case 0: return Activity.jogging;
    case 1: return Activity.stationary;
    case 2: return Activity.stairs;
    case 3: return Activity.walking;
    default: return Activity.unknown;
  }
}
