import 'package:flutter/material.dart';
import 'summary_screen.dart';
import 'timeline_screen.dart';
import 'weekly_screen.dart';

class StatisticsTabsScreen extends StatelessWidget {
  const StatisticsTabsScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return DefaultTabController(
      length: 3,
      child: Scaffold(
        appBar: AppBar(
          title: const Text("Activity Statistics"),
          bottom: const TabBar(
            tabs: [
              Tab(text: "Summary"),
              Tab(text: "Timeline"),
              Tab(text: "Weekly"),
            ],
          ),
        ),
        body: const TabBarView(
          children: [
            SummaryScreen(),
            TimelineScreen(),
            WeeklyScreen(),
          ],
        ),
      ),
    );
  }
}
