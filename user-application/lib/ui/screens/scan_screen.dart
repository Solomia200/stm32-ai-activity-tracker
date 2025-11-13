import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import '../../viewmodels/scan_view_model.dart';
import '../widgets/activity_badge.dart';

class ScanScreen extends StatelessWidget {
  final ScanViewModel vm;
  const ScanScreen({super.key, required this.vm});

  @override
  Widget build(BuildContext context) {
    return AnimatedBuilder(
      animation: vm,
      builder: (_, __) {
        return Scaffold(
          appBar: AppBar(title: const Text('Activity Tracker (STM32 BLE)')),
          body: Column(
            children: [
              ActivityBadge(activity: vm.currentActivity),
              const Divider(height: 32),
              Expanded(
                child: ListView.separated(
                  itemCount: vm.results.length,
                  separatorBuilder: (_, __) => const Divider(height: 1),
                  itemBuilder: (_, i) {
                    final r = vm.results[i];
                    final name = r.device.platformName.isEmpty
                        ? '(unknown)'
                        : r.device.platformName;
                    return ListTile(
                      title: Text(name),
                      subtitle: Text('${r.device.remoteId.str} • RSSI ${r.rssi}'),
                      trailing: const Icon(Icons.bluetooth),
                      onTap: () => vm.connect(r.device),
                    );
                  },
                ),
              ),
            ],
          ),
          floatingActionButton: FloatingActionButton(
            onPressed: vm.startScan,
            child: Icon(vm.scanning ? Icons.hourglass_bottom : Icons.refresh),
          ),
        );
      },
    );
  }
}
