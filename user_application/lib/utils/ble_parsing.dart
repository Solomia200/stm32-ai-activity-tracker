import 'dart:typed_data';
import '../models/activity.dart';
import '../models/activity_entry.dart';

ActivityEntry parseActivityFromEnvironmentalPacket(List<int> value) {
  if (value.length < 8) {
    return ActivityEntry(timestamp: 0, activity: Activity.unknown);
  }

  final bytes = Uint8List.fromList(value);
  final bd = ByteData.sublistView(bytes);


  final int timeSec = bd.getInt32(2, Endian.little);


  final int classCode = bd.getInt16(6, Endian.little);

  Activity activity;
  switch (classCode) {
    case 0: activity = Activity.jogging; break;
    case 1: activity = Activity.stationary; break;
    case 2: activity = Activity.stairs; break;
    case 3: activity = Activity.walking; break;
    default: activity = Activity.unknown;
  }

  return ActivityEntry(
    timestamp: timeSec,
    activity: activity,
  );
}
