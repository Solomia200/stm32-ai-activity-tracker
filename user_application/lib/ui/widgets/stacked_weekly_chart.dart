import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';

class StackedWeeklyChart extends StatelessWidget {
  final Map<DateTime, Map<String, Duration>> data;

  const StackedWeeklyChart({super.key, required this.data});

  @override
  Widget build(BuildContext context) {
    final days = data.keys.toList()..sort();

    return Card(
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(16)),
      elevation: 4,
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: BarChart(
          BarChartData(
            maxY: _maxTotal(),
            barGroups: days.asMap().entries.map((entry) {
              final index = entry.key;
              final day = entry.value;
              final activities = data[day]!;

              return BarChartGroupData(
                x: index,
                barRods: [
                  BarChartRodData(
                    toY: activities.values
                        .fold(0, (sum, d) => sum + d.inMinutes)
                        .toDouble(),
                    rodStackItems: _segments(activities),
                    width: 20,
                    borderRadius: BorderRadius.circular(4),
                  ),
                ],
              );
            }).toList(),
            titlesData: FlTitlesData(
              leftTitles: AxisTitles(
                sideTitles: SideTitles(showTitles: true, reservedSize: 40),
              ),
              bottomTitles: AxisTitles(
                sideTitles: SideTitles(
                  showTitles: true,
                  getTitlesWidget: (i, meta) {
                    final day = days[i.toInt()];
                    return Padding(
                      padding: const EdgeInsets.only(top: 8.0),
                      child: Text(
                        "${day.month}/${day.day}",
                        style: const TextStyle(fontSize: 12),
                      ),
                    );
                  },
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }

  // створюємо сегменти
  List<BarChartRodStackItem> _segments(Map<String, Duration> acts) {
    double offset = 0;
    List<BarChartRodStackItem> segments = [];

    acts.forEach((activity, duration) {
      final minutes = duration.inMinutes.toDouble();
      final color = _activityColor(activity);

      segments.add(
        BarChartRodStackItem(
          offset,
          offset + minutes,
          color,
        ),
      );
      offset += minutes;
    });

    return segments;
  }

  // максимальна висота графіка
  double _maxTotal() {
    return data.values
        .map((day) =>
    day.values.fold(0, (sum, d) => sum + d.inMinutes) as int)
        .fold(0, (max, v) => v > max ? v : max)
        .toDouble();
  }

  Color _activityColor(String name) {
    switch (name) {
      case "walking": return Colors.green;
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
