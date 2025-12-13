"""Simple script to monitor and print predictions from BLE device."""

import asyncio
from bleak import BleakScanner, BleakClient


DEVICE_NAME = "BlueNRG"

ID_TO_CLASS_MAPPING: dict[int: str] = {
    0: "walking",
    1: "running",
    2: "climbingdown",
    3: "climbingup",
    4: "resting"
}


def parse_prediction_from_ble_data(data: bytearray) -> int:
    """
    Extract predicted activity class from BLE data packet.
    
    Args:
        data: Raw BLE data packet
        
    Returns:
        Predicted activity class (integer)
    """
    if len(data) > 4:
        # print(data)
        return int(data[6])
    else:
        raise ValueError(f"Invalid data length: {len(data)}, expected > 4")


async def monitor_predictions():
    """
    Connect to BLE device and continuously print received predictions.
    """
    print(f"\n{'='*60}")
    print("BLE Prediction Monitor")
    print(f"{'='*60}\n")
    
    # Scan for device
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover()
    
    stm32_device = None
    for d in devices:
        print(f"  Found: {d.name} [{d.address}]")
        if d.name == DEVICE_NAME:
            stm32_device = d
    
    if not stm32_device:
        print(f"\nError: Device '{DEVICE_NAME}' not found.")
        return
    
    address = stm32_device.address
    print(f"\nConnecting to '{DEVICE_NAME}' at {address}...")
    
    async with BleakClient(address) as client:
        if not client.is_connected:
            print("Failed to connect!")
            return
        
        print(f"Connected successfully!\n")
        
        # Get services
        services = client.services
        if services is None:
            await client.get_services()
            services = client.services
        
        prediction_count = 0
        
        def notification_handler(sender, data):
            """Handle incoming BLE notifications and print predictions."""
            nonlocal prediction_count
            try:
                predicted_class = ID_TO_CLASS_MAPPING[parse_prediction_from_ble_data(data)]
                prediction_count += 1
                print(f"[{prediction_count:4d}] Prediction: {predicted_class}")
                
            except Exception as e:
                print(f"Error parsing data: {e}")
        
        # Subscribe to notifications
        notify_chars = []
        for service in services:
            for char in service.characteristics:
                if "notify" in char.properties:
                    print(f"Subscribing to characteristic: {char.uuid}")
                    await client.start_notify(char.uuid, notification_handler)
                    notify_chars.append(char.uuid)
        
        if not notify_chars:
            print("No notify characteristics found!")
            return
        
        print(f"\n{'='*60}")
        print("Monitoring predictions... Press Ctrl+C to stop.")
        print(f"{'='*60}\n")
        
        try:
            # Keep listening until interrupted
            while True:
                await asyncio.sleep(1)
                
        except KeyboardInterrupt:
            print(f"\n\n{'='*60}")
            print(f"Stopped. Total predictions received: {prediction_count}")
            print(f"{'='*60}\n")
        
        finally:
            # Stop notifications
            for char_uuid in notify_chars:
                await client.stop_notify(char_uuid)


if __name__ == "__main__":
    asyncio.run(monitor_predictions())
