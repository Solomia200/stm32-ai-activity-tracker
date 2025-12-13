import 'package:flutter/material.dart';
import '../../db/activity_database.dart';
import '../../models/activity_record_duration.dart';

class TimelineScreen extends StatelessWidget {
  const TimelineScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<List<ActivityRecordWithDuration>>(
      future: ActivityDatabase.instance.getRecordsWithDuration(),
      builder: (context, snapshot) {
        if (!snapshot.hasData) {
          return const Center(child: CircularProgressIndicator());
        }

        final recs = snapshot.data!;
        if (recs.isEmpty) {
          return const Center(child: Text("No activity data yet"));
        }

        return ListView.builder(
          padding: const EdgeInsets.all(20),
          itemCount: recs.length,
          itemBuilder: (_, i) {
            final r = recs[i];
            final start = r.record.timestamp;
            final end = start.add(r.duration);

            return _TimelineEntry(
              isFirst: i == 0,
              isLast: i == recs.length - 1,
              activity: r.record.activityClass,
              start: start,
              end: end,
              duration: r.duration,
            );
          },
        );
      },
    );
  }
}

class _TimelineEntry extends StatelessWidget {
  final bool isFirst;
  final bool isLast;
  final String activity;
  final DateTime start;
  final DateTime end;
  final Duration duration;

  const _TimelineEntry({
    required this.isFirst,
    required this.isLast,
    required this.activity,
    required this.start,
    required this.end,
    required this.duration,
  });

  @override
  Widget build(BuildContext context) {
    final color = _activityColor(activity);

    return Row(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [

        Column(
          children: [

            if (isFirst) const SizedBox(height: 6),

            // circle
            Container(
              width: 18,
              height: 18,
              decoration: BoxDecoration(
                color: color,
                shape: BoxShape.circle,
              ),
            ),

            // bottom line
            if (!isLast)
              Container(
                width: 3,
                height: 50,
                color: Colors.grey.shade300,
              ),
          ],
        ),

        const SizedBox(width: 14),

        // RIGHT SIDE: text block
        Expanded(
          child: Padding(
            padding: const EdgeInsets.only(bottom: 24),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  activity,
                  style: const TextStyle(
                    fontSize: 18,
                    fontWeight: FontWeight.bold,
                    letterSpacing: -0.3,
                  ),
                ),

                const SizedBox(height: 4),

                Text(
                  "${_fmt(start)} – ${_fmt(end)}   (${duration.inMinutes} min)",
                  style: TextStyle(
                    fontSize: 15,
                    color: Colors.grey.shade700,
                  ),
                ),
              ],
            ),
          ),
        )
      ],
    );
  }

  Color _activityColor(String name) {
    switch (name) {
      case "walking": return Colors.greenAccent.shade700;
      case "running": return Colors.redAccent;
      case "sitting": return Colors.deepPurpleAccent;
      case "standing": return Colors.blueAccent;
      case "lying": return Colors.orangeAccent;
      case "climbing_up": return Colors.teal;
      case "climbing_down": return Colors.indigo;
      default: return Colors.grey;
    }
  }

  String _fmt(DateTime dt) =>
      "${dt.hour.toString().padLeft(2, '0')}:${dt.minute.toString().padLeft(2, '0')}";
}
