import 'package:flutter/material.dart';
import '../../models/activity.dart';

class ActivityBadge extends StatelessWidget {
  final Activity activity;
  const ActivityBadge({super.key, required this.activity});

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        const SizedBox(height: 16),
        const Text("Current Activity:", style: TextStyle(
            fontSize: 18, fontWeight: FontWeight.w600)),
        const SizedBox(height: 8),
        Text(activity.label, style: const TextStyle(
            fontSize: 26, color: Colors.teal, fontWeight: FontWeight.bold)),
      ],
    );
  }
}
