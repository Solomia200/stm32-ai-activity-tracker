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
    case 0: activity = Activity.walking; break;
    case 1: activity = Activity.jogging; break;
    case 2: activity = Activity.climbingdown; break;
    case 3: activity = Activity.climbingup; break;
    case 4: activity = Activity.stationary; break;

    default: activity = Activity.unknown;
  }
// 0: "walking",
//     1: "running",
//     2: "climbingdown",
//     3: "climbingup",
//     4: "resting"

  return ActivityEntry(
    timestamp: timeSec,
    activity: activity,
  );
}
