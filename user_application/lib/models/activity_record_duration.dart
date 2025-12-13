import 'activity_record.dart';

class ActivityRecordWithDuration {
  final ActivityRecord record;
  final Duration duration;

  ActivityRecordWithDuration({
    required this.record,
    required this.duration,
  });

  /// Static helper: compute durations between consecutive records
  static List<ActivityRecordWithDuration> compute(List<ActivityRecord> recs) {
    if (recs.isEmpty) return [];

    final List<ActivityRecordWithDuration> out = [];

    for (int i = 0; i < recs.length; i++) {
      final current = recs[i];

      DateTime? nextTime;
      if (i < recs.length - 1) {
        nextTime = recs[i + 1].timestamp;
      }

      final duration = nextTime == null
          ? Duration.zero
          : nextTime.difference(current.timestamp);

      out.add(
        ActivityRecordWithDuration(
          record: current,
          duration: duration,
        ),
      );
    }

    return out;
  }
}
