// lib/utils/activity_stats.dart

import '../db/activity_database.dart';
import '../models/activity_record.dart';

class ActivityStats {

  static Future<Map<String, int>> getActivityCounts() async {
    final List<ActivityRecord> records =
    await ActivityDatabase.instance.getAllRecords();

    final Map<String, int> counts = {};

    for (final r in records) {
      counts[r.activityClass] = (counts[r.activityClass] ?? 0) + 1;
    }

    return counts;
  }


  static Future<Map<DateTime, int>> getDailyCounts() async {
    final List<ActivityRecord> records =
    await ActivityDatabase.instance.getAllRecords();

    final Map<DateTime, int> perDay = {};

    for (final r in records) {
      final day = DateTime(r.timestamp.year, r.timestamp.month, r.timestamp.day);
      perDay[day] = (perDay[day] ?? 0) + 1;
    }

    return perDay;
  }
}
