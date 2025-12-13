import 'package:flutter/material.dart';
import '../../db/activity_database.dart';
import '../widgets/stacked_weekly_chart.dart';

class WeeklyScreen extends StatelessWidget {
  const WeeklyScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder(
      future: ActivityDatabase.instance.getStackedWeeklyData(),
      builder: (_, snapshot) {
        if (!snapshot.hasData) {
          return const Center(child: CircularProgressIndicator());
        }

        return Padding(
          padding: const EdgeInsets.all(16),
          child: StackedWeeklyChart(data: snapshot.data!),
        );
      },
    );
  }
}
