import 'package:flutter/material.dart';
import '../../db/activity_database.dart';
import '../../models/activity_record_duration.dart';
import '../widgets/activity_pie_chart.dart';

class SummaryScreen extends StatelessWidget {
  const SummaryScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<List<ActivityRecordWithDuration>>(
      future: ActivityDatabase.instance.getRecordsWithDuration(),
      builder: (context, snapshot) {
        if (!snapshot.hasData) {
          return const Center(child: CircularProgressIndicator());
        }

        final records = snapshot.data!;
        final totals = <String, Duration>{};

        for (var r in records) {
          totals[r.record.activityClass] =
              (totals[r.record.activityClass] ?? Duration.zero) + r.duration;
        }

        return ListView(
          padding: const EdgeInsets.all(16),
          children: [

            // PIE CHART (NEW)
            Card(
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(16)),
              elevation: 4,
              child: Padding(
                padding: const EdgeInsets.all(16),
                child: ActivityPieChart(data: totals),
              ),
            ),

            const SizedBox(height: 20),

            // SUMMARY CARDS
            ...totals.entries.map((e) {
              final mins = e.value.inMinutes;
              final color = _activityColor(e.key);

              return Container(
                margin: const EdgeInsets.only(bottom: 16),
                padding: const EdgeInsets.all(20),
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(16),
                  boxShadow: [
                    BoxShadow(
                      color: color.withOpacity(0.2),
                      blurRadius: 10,
                      offset: const Offset(0, 6),
                    )
                  ],
                ),
                child: Row(
                  children: [
                    CircleAvatar(
                      backgroundColor: color.withOpacity(0.15),
                      radius: 28,
                      child: Icon(Icons.timelapse, color: color, size: 28),
                    ),
                    const SizedBox(width: 20),
                    Expanded(
                      child: Text(
                        e.key,
                        style: const TextStyle(
                          fontSize: 20,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    ),
                    Text(
                      "$mins min",
                      style: TextStyle(
                        fontSize: 18,
                        fontWeight: FontWeight.w600,
                        color: color,
                      ),
                    ),
                  ],
                ),
              );
            }).toList(),
          ],
        );

      },
    );
  }

  Color _activityColor(String name) {
    switch (name) {
      case "walking": return Colors.greenAccent.shade700;
      case "running": return Colors.redAccent;
      case "sitting": return Colors.deepPurpleAccent;
      case "standing": return Colors.blueAccent;
      default: return Colors.grey;
    }
  }
}
