import '../db/activity_database.dart';
import '../models/activity_record.dart';

Future<void> fillTestDatabase() async {
  final now = DateTime.now();

  final samples = [
    ActivityRecord(activityClass: "walking", timestamp: now.subtract(const Duration(minutes: 1))),
    ActivityRecord(activityClass: "running", timestamp: now.subtract(const Duration(minutes: 5))),
    ActivityRecord(activityClass: "sitting", timestamp: now.subtract(const Duration(minutes: 10))),
    ActivityRecord(activityClass: "walking", timestamp: now.subtract(const Duration(hours: 1))),
    ActivityRecord(activityClass: "running", timestamp: now.subtract(const Duration(hours: 2))),
  ];

  for (final r in samples) {
    await ActivityDatabase.instance.insertRecord(r);
  }

  print("🔥 Test DB filled");
}
