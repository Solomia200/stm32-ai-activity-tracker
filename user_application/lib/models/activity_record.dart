class ActivityRecord {
  final int? id;
  final String activityClass;
  final DateTime timestamp;

  ActivityRecord({
    this.id,
    required this.activityClass,
    required this.timestamp,
  });

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'class': activityClass,
      'timestamp': timestamp.toIso8601String(),
    };
  }

  factory ActivityRecord.fromMap(Map<String, dynamic> map) {
    return ActivityRecord(
      id: map['id'] as int?,
      activityClass: map['class'] as String,
      timestamp: DateTime.parse(map['timestamp']),
    );
  }
}
