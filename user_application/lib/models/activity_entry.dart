import 'activity.dart';

class ActivityEntry {
  final int timestamp;
  final Activity activity;

  ActivityEntry({
    required this.timestamp,
    required this.activity,
  });

  @override
  String toString() =>
      'ActivityEntry(timestamp: $timestamp, activity: ${activity.label})';
}
