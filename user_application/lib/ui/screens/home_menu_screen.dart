import 'package:flutter/material.dart';
import '../../viewmodels/scan_view_model.dart';
import '../../services/bluetooth_service.dart';
import 'scan_screen.dart';
import 'statistics_tabs_screen.dart';
import '../widgets/menu_card.dart';
import '../../db/activity_database.dart';
import '../../models/activity_record.dart';




class HomeMenuScreen extends StatelessWidget {
  final BluetoothService ble;
  final ScanViewModel vm;

  const HomeMenuScreen({
    super.key,
    required this.ble,
    required this.vm,
  });

  IconData _activityIcon(String act) {
    switch (act) {
      case "walking":
        return Icons.directions_walk;
      case "running":
        return Icons.directions_run;
      case "climbing_up":
        return Icons.arrow_upward;
      case "climbing_down":
        return Icons.arrow_downward;
      case "sitting":
        return Icons.chair;
      case "lying":
        return Icons.king_bed;
      case "standing":
        return Icons.accessibility;
      default:
        return Icons.device_unknown;
    }
  }

  Widget _currentActivityCard(String activity) {
    return Container(
      padding: const EdgeInsets.all(18),
      decoration: BoxDecoration(
        color: Colors.blue.shade50,
        borderRadius: BorderRadius.circular(16),
        boxShadow: const [
          BoxShadow(
            blurRadius: 10,
            spreadRadius: 1,
            offset: Offset(0, 4),
            color: Colors.black12,
          ),
        ],
      ),
      child: Row(
        children: [
          CircleAvatar(
            radius: 26,
            backgroundColor: Colors.blue.shade100,
            child: Icon(
              _activityIcon(activity),
              color: Colors.blue.shade700,
              size: 32,
            ),
          ),
          const SizedBox(width: 18),
          Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                activity.toUpperCase(),
                style: const TextStyle(
                  fontSize: 22,
                  fontWeight: FontWeight.bold,
                ),
              ),
              Text(
                "Current activity",
                style: TextStyle(color: Colors.grey.shade600),
              ),
            ],
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("Activity Tracker")),
      body: StreamBuilder<bool>(
        stream: ble.connectionStream,
        initialData: ble.isConnected,
        builder: (context, snapshot) {
          final connected = snapshot.data ?? false;

          return Padding(
            padding: const EdgeInsets.all(24.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [

                // ===== CURRENT ACTIVITY =====
                if (connected)
                  StreamBuilder<ActivityRecord>(
                    stream: ActivityDatabase.instance.liveLastRecordStream,
                    builder: (context, snap) {
                      if (!snap.hasData) {
                        return const Padding(
                          padding: EdgeInsets.all(16),
                          child: Text(
                            "Waiting for activity data...",
                            textAlign: TextAlign.center,
                            style: TextStyle(color: Colors.grey),
                          ),
                        );
                      }
                      return _currentActivityCard(
                        snap.data!.activityClass,
                      );
                    },
                  ),

                if (connected) const SizedBox(height: 20),

                // ===== SCAN BUTTON =====
                MenuCard(
                  title: "Scan & Connect",
                  subtitle: "Find STM32 device and start reading data",
                  icon: Icons.bluetooth_searching,
                  color: Colors.blueAccent,
                  onTap: () => Navigator.push(
                    context,
                    MaterialPageRoute(
                      builder: (_) => ScanScreen(vm: vm),
                    ),
                  ),
                ),

                const SizedBox(height: 20),

                // ===== ANALYTICS BUTTON =====
                if (connected)
                  MenuCard(
                    title: "Analytics",
                    subtitle: "View activity graphs and statistics",
                    icon: Icons.bar_chart,
                    color: Colors.green,
                    onTap: () => Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (_) => const StatisticsTabsScreen(),
                      ),
                    ),
                  ),
              ],
            ),
          );
        },
      ),
    );
  }
}
