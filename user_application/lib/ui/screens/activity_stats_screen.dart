// lib/ui/screens/activity_stats_screen.dart

import 'package:flutter/material.dart';
import '../../utils/activity_stats.dart';
import '../widgets/weekly_bar_chart.dart';
import '../../db/activity_database.dart';



class ActivityStatsScreen extends StatelessWidget {
  const ActivityStatsScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Activity statistics'),
      ),
      body: FutureBuilder(
        future: Future.wait([
          ActivityStats.getActivityCounts(),
          ActivityStats.getDailyCounts(),
        ]),
        builder: (context, snapshot) {
          if (snapshot.connectionState == ConnectionState.waiting) {
            return const Center(child: CircularProgressIndicator());
          }

          if (snapshot.hasError) {
            return Center(
              child: Text('Error: ${snapshot.error}'),
            );
          }


          final activityCounts =
          snapshot.data![0] as Map<String, int>;
          final dailyCounts =
          snapshot.data![1] as Map<DateTime, int>;

          return ListView(
            padding: const EdgeInsets.all(16),
            children: [
              const Text(
                'By activity class',
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              const SizedBox(height: 8),
              ...activityCounts.entries.map(
                    (e) => ListTile(
                  leading: const Icon(Icons.directions_run),
                  title: Text(e.key),
                  trailing: Text(e.value.toString()),
                ),
              ),
              const Divider(height: 32),
              const Text(
                'By day (total records)',
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              const SizedBox(height: 8),
              ...dailyCounts.entries.map(
                    (e) => ListTile(
                  leading: const Icon(Icons.calendar_today),
                  title: Text(
                    '${e.key.year}-${e.key.month.toString().padLeft(2, '0')}-${e.key.day.toString().padLeft(2, '0')}',
                  ),
                  trailing: Text(e.value.toString()),

                ),
              ),
              const SizedBox(height: 24),

              FutureBuilder<Map<DateTime, int>>(
                future: ActivityDatabase.instance.getCountsForLast7Days(),
                builder: (context, snapshot) {
                  if (!snapshot.hasData) {
                    return const Center(child: CircularProgressIndicator());
                  }

                  final data = snapshot.data!;

                  return Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      const SizedBox(height: 16),
                      const Text(
                        "Weekly Activity",
                        style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                      ),
                      WeeklyBarChart(data: data),
                    ],
                  );
                },
              ),

            ],
          );
        },
      ),
    );
  }
}
