import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';

class ActivityPieChart extends StatelessWidget {
  final Map<String, Duration> data;

  const ActivityPieChart({super.key, required this.data});

  @override
  Widget build(BuildContext context) {
    final totalMinutes =
    data.values.fold<int>(0, (sum, d) => sum + d.inMinutes);

    if (totalMinutes == 0) {
      return const Center(child: Text("No activity data"));
    }

    return Column(
      children: [
        SizedBox(
          height: 250,
          child: PieChart(
            PieChartData(
              sectionsSpace: 2,
              centerSpaceRadius: 40,
              sections: _buildSections(),
            ),
          ),
        ),

        const SizedBox(height: 20),

        // Legend
        Wrap(
          spacing: 16,
          runSpacing: 8,
          children: data.entries.map((e) {
            final color = _activityColor(e.key);
            final percent = (e.value.inMinutes / totalMinutes * 100).toStringAsFixed(1);

            return Row(
              mainAxisSize: MainAxisSize.min,
              children: [
                Container(
                  width: 14,
                  height: 14,
                  decoration: BoxDecoration(
                    color: color,
                    borderRadius: BorderRadius.circular(4),
                  ),
                ),
                const SizedBox(width: 6),
                Text("${e.key} ($percent%)"),
              ],
            );
          }).toList(),
        ),
      ],
    );
  }

  List<PieChartSectionData> _buildSections() {
    final total = data.values.fold<int>(0, (sum, d) => sum + d.inMinutes);

    return data.entries.map((e) {
      final minutes = e.value.inMinutes.toDouble();
      final color = _activityColor(e.key);

      return PieChartSectionData(
        value: minutes,
        color: color,
        radius: 60,
        title: "",
      );
    }).toList();
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
}
