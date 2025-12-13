import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import '../models/activity_record.dart';

import '../models/activity_record_duration.dart';
import 'dart:async';

class ActivityDatabase {
  ActivityDatabase._init();
  static final ActivityDatabase instance = ActivityDatabase._init();

  final StreamController<ActivityRecord> _lastRecordController =
  StreamController<ActivityRecord>.broadcast();

  Stream<ActivityRecord> get liveLastRecordStream =>
      _lastRecordController.stream;


  Database? _database;

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDB('activities.db');
    return _database!;
  }

  Future<Database> _initDB(String fileName) async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, fileName);

    return await openDatabase(
      path,
      version: 1,
      onCreate: _createDB,
    );
  }

  Future _createDB(Database db, int version) async {
    await db.execute('''
      CREATE TABLE activity_records (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        class TEXT NOT NULL,
        timestamp TEXT NOT NULL
      );
    ''');
  }

  // INSERT
  Future<int> insertRecord(ActivityRecord record) async {
    _lastRecordController.add(record);

    final db = await database;
    return await db.insert('activity_records', record.toMap());
  }

  // GET ALL RECORDS
  Future<List<ActivityRecord>> getAllRecords() async {
    final db = await database;

    final result = await db.query(
      'activity_records',
      orderBy: 'timestamp DESC',
    );

    return result.map((m) => ActivityRecord.fromMap(m)).toList();
  }

  // COUNT BY ACTIVITY CLASS
  Future<Map<String, int>> getCountsByActivityClass() async {
    final db = await database;

    final result = await db.rawQuery('''
      SELECT class, COUNT(*) as count
      FROM activity_records
      GROUP BY class
    ''');

    final map = <String, int>{};
    for (final row in result) {
      map[row['class'] as String] = row['count'] as int;
    }
    return map;
  }

  // RECORDS FOR ONE DAY
  Future<List<ActivityRecord>> getRecordsForDay(DateTime day) async {
    final db = await database;

    final start = DateTime(day.year, day.month, day.day);
    final end = start.add(const Duration(days: 1));

    final result = await db.query(
      'activity_records',
      where: 'timestamp >= ? AND timestamp < ?',
      whereArgs: [start.toIso8601String(), end.toIso8601String()],
      orderBy: 'timestamp DESC',
    );

    return result.map((m) => ActivityRecord.fromMap(m)).toList();
  }

  // COUNTS FOR LAST 7 DAYS
  Future<Map<DateTime, int>> getCountsForLast7Days() async {
    final db = await database;

    final today = DateTime.now();
    final lastWeek = today.subtract(const Duration(days: 7));

    final result = await db.rawQuery('''
      SELECT DATE(timestamp) as day, COUNT(*) as count
      FROM activity_records
      WHERE timestamp >= ?
      GROUP BY DATE(timestamp)
    ''', [lastWeek.toIso8601String()]);

    final map = <DateTime, int>{};
    for (final row in result) {
      final dayStr = row['day'] as String;
      final day = DateTime.parse(dayStr);
      map[day] = row['count'] as int;
    }
    return map;
  }

  // TIMELINE FOR DAY
  Future<List<ActivityRecord>> getTimelineForDay(DateTime day) async {
    return getRecordsForDay(day);
  }

  Future close() async {
    final db = await database;
    db.close();
  }


  Future<List<ActivityRecordWithDuration>> getRecordsWithDuration() async {
    final db = await instance.database;

    final result = await db.query(
      'activity_records',
      orderBy: 'timestamp ASC',   // важливо!
    );

    final records = result.map((e) => ActivityRecord.fromMap(e)).toList();


    final List<ActivityRecordWithDuration> list = [];

    for (int i = 0; i < records.length; i++) {
      final current = records[i];

      DateTime? nextTime;
      if (i < records.length - 1) {
        nextTime = records[i + 1].timestamp;
      }

      final duration = nextTime == null
          ? Duration.zero
          : nextTime.difference(current.timestamp);

      list.add(
        ActivityRecordWithDuration(
          record: current,
          duration: duration,
        ),
      );
    }

    return list;
  }

  Future<Map<DateTime, Map<String, Duration>>> getStackedWeeklyData() async {
    final db = await instance.database;

    final today = DateTime.now();
    final startWeek = today.subtract(const Duration(days: 6));


    final result = await db.query(
      'activity_records',
      where: 'timestamp >= ?',
      whereArgs: [startWeek.toIso8601String()],
      orderBy: 'timestamp ASC',
    );

    final recs = result.map((e) => ActivityRecord.fromMap(e)).toList();


    final List<ActivityRecordWithDuration> withDur =
    ActivityRecordWithDuration.compute(recs);


    final Map<DateTime, Map<String, Duration>> out = {};

    for (var r in withDur) {
      final day = DateTime(r.record.timestamp.year,
          r.record.timestamp.month,
          r.record.timestamp.day);

      out.putIfAbsent(day, () => {});
      out[day]!.putIfAbsent(r.record.activityClass, () => Duration.zero);

      out[day]![r.record.activityClass] =
          out[day]![r.record.activityClass]! + r.duration;
    }

    return out;
  }

}
