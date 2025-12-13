import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import '../../viewmodels/scan_view_model.dart';

class ScanScreen extends StatelessWidget {
  final ScanViewModel vm;

  const ScanScreen({super.key, required this.vm});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Scan Devices"),
        elevation: 0,
      ),
      body: Column(
        children: [

          // --- SCAN BUTTON ---
          Padding(
            padding: const EdgeInsets.symmetric(vertical: 20),
            child: Center(
              child: ElevatedButton.icon(
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.symmetric(horizontal: 24, vertical: 14),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(14),
                  ),
                  textStyle: const TextStyle(fontSize: 18, fontWeight: FontWeight.w600),
                ),
                onPressed: () async {
                  try {
                    await vm.startScan();
                  } catch (e) {
                    debugPrint("Scan error: $e");

                    ScaffoldMessenger.of(context).showSnackBar(
                      const SnackBar(content: Text("Увімкніть Bluetooth")),
                    );
                  }
                },
                icon: const Icon(Icons.search, size: 24),
                label: const Text("Scan for Devices"),
              ),
            ),
          ),

          // --- LOADING INDICATOR ---
          StreamBuilder(
            stream: FlutterBluePlus.isScanning,
            builder: (context, snapshot) {
              final scanning = snapshot.data ?? false;

              return scanning
                  ? const Padding(
                padding: EdgeInsets.only(bottom: 12),
                child: CircularProgressIndicator(),
              )
                  : const SizedBox.shrink();
            },
          ),

          const SizedBox(height: 10),

          // --- LIST OF DEVICES ---
          Expanded(
            child: StreamBuilder<List<ScanResult>>(
              stream: vm.scanResults,
              builder: (context, snapshot) {
                final results = snapshot.data ?? [];

                if (results.isEmpty) {
                  return const Center(
                    child: Text(
                      "No devices found",
                      style: TextStyle(color: Colors.black54, fontSize: 16),
                    ),
                  );
                }

                return ListView.builder(
                  itemCount: results.length,
                  itemBuilder: (context, index) {
                    final r = results[index];

                    return Padding(
                      padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                      child: GestureDetector(
                        onTap: () async {
                          await vm.connect(r.device);
                          Navigator.pop(context);
                        },
                        child: Container(
                          padding: const EdgeInsets.all(16),
                          decoration: BoxDecoration(
                            color: Colors.white,
                            borderRadius: BorderRadius.circular(14),
                            boxShadow: [
                              BoxShadow(
                                color: Colors.black12.withOpacity(0.08),
                                blurRadius: 10,
                                offset: const Offset(0, 4),
                              )
                            ],
                          ),
                          child: Row(
                            children: [
                              const Icon(Icons.bluetooth, size: 30, color: Colors.blueAccent),
                              const SizedBox(width: 16),

                              Expanded(
                                child: Column(
                                  crossAxisAlignment: CrossAxisAlignment.start,
                                  children: [
                                    Text(
                                      r.device.platformName.isNotEmpty
                                          ? r.device.platformName
                                          : "Unknown device",
                                      style: const TextStyle(
                                        fontSize: 18,
                                        fontWeight: FontWeight.w600,
                                      ),
                                    ),
                                    const SizedBox(height: 4),
                                    Text(
                                      r.device.remoteId.toString(),
                                      style: const TextStyle(
                                        color: Colors.black45,
                                        fontSize: 13,
                                      ),
                                    ),
                                  ],
                                ),
                              ),

                              const Icon(Icons.chevron_right, color: Colors.black38),
                            ],
                          ),
                        ),
                      ),
                    );
                  },
                );
              },
            ),
          ),

        ],
      ),
    );
  }
}
