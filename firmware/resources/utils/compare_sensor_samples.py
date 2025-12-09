import os
from pathlib import Path
import yaml
import pandas as pd
from typing import Dict, List, Tuple


def compare_sensor_samples(dataset_csv_path: str, output_yaml_path: str, sensor_location: str = "upperarm") -> None:
    """
    Compare number of samples between accelerometer and gyroscope for each proband and activity.
    
    Args:
        dataset_csv_path: Path to the dataset-csv directory
        output_yaml_path: Path where to save the YAML result file
        sensor_location: Fixed sensor location to analyze (default: "upperarm")
    """
    dataset_path = Path(dataset_csv_path)
    
    if not dataset_path.exists():
        raise ValueError(f"Dataset path does not exist: {dataset_csv_path}")
    
    # Get all proband directories
    proband_dirs = sorted([d for d in dataset_path.iterdir() if d.is_dir() and d.name.startswith("proband")])
    
    # Activities to check (based on the structure)
    activities = [
        "climbingdown",
        "climbingup", 
        "jumping",
        "lying",
        "running",
        "sitting",
        "standing",
        "walking"
    ]
    
    results = {}
    
    for proband_dir in proband_dirs:
        proband_name = proband_dir.name
        data_dir = proband_dir / "data"
        
        if not data_dir.exists():
            continue
        
        proband_results = {}
        
        for activity in activities:
            # Find accelerometer and gyroscope directories for this activity
            acc_dirs = sorted(data_dir.glob(f"acc_{activity}*_csv"))
            gyr_dirs = sorted(data_dir.glob(f"gyr_{activity}*_csv"))
            
            # Handle case where there might be multiple recordings
            for acc_dir in acc_dirs:
                # Extract variant (e.g., "", "_2", "_3")
                acc_variant = acc_dir.name.replace(f"acc_{activity}", "").replace("_csv", "")
                
                # Find corresponding gyroscope file
                gyr_variant_name = f"gyr_{activity}{acc_variant}_csv"
                gyr_dir = data_dir / gyr_variant_name
                
                # Construct file names
                acc_filename = f"acc_{activity}{acc_variant}_{sensor_location}.csv"
                
                # Gyroscope files have different naming convention
                if acc_variant:
                    gyr_filename = f"Gyroscope_{activity}{acc_variant}_{sensor_location}.csv"
                else:
                    gyr_filename = f"Gyroscope_{activity}_{sensor_location}.csv"
                
                acc_file = acc_dir / acc_filename
                gyr_file = gyr_dir / gyr_filename
                
                # Count samples
                acc_samples = 0
                gyr_samples = 0
                
                if acc_file.exists():
                    try:
                        df_acc = pd.read_csv(acc_file)
                        acc_samples = len(df_acc)
                    except Exception as e:
                        print(f"Error reading {acc_file}: {e}")
                
                if gyr_file.exists():
                    try:
                        df_gyr = pd.read_csv(gyr_file)
                        gyr_samples = len(df_gyr)
                    except Exception as e:
                        print(f"Error reading {gyr_file}: {e}")
                
                # Create activity key
                activity_key = f"{activity}{acc_variant}" if acc_variant else activity
                
                # Calculate difference
                difference = acc_samples - gyr_samples
                
                proband_results[activity_key] = {
                    "accelerometer_samples": acc_samples,
                    "gyroscope_samples": gyr_samples,
                    "difference": difference,
                    "acc_file": str(acc_file.relative_to(dataset_path)) if acc_file.exists() else "NOT FOUND",
                    "gyr_file": str(gyr_file.relative_to(dataset_path)) if gyr_file.exists() else "NOT FOUND"
                }
        
        if proband_results:
            results[proband_name] = proband_results
    
    # Prepare output data
    output_data = {
        "sensor_location": sensor_location,
        "comparison": results
    }
    
    # Save to YAML
    output_path = Path(output_yaml_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    with open(output_path, 'w') as f:
        yaml.dump(output_data, f, default_flow_style=False, sort_keys=False, allow_unicode=True)
    
    print(f"Results saved to: {output_yaml_path}")
    print(f"\nSummary:")
    print(f"  Analyzed {len(results)} probands")
    
    # Calculate statistics
    total_comparisons = sum(len(activities) for activities in results.values())
    mismatches = sum(
        1 for proband_data in results.values() 
        for activity_data in proband_data.values() 
        if activity_data['difference'] != 0
    )
    
    print(f"  Total comparisons: {total_comparisons}")
    print(f"  Mismatches (difference != 0): {mismatches}")
    
    if mismatches > 0:
        print(f"\n  Activities with sample count differences:")
        for proband, activities in results.items():
            for activity, data in activities.items():
                if data['difference'] != 0:
                    print(f"    {proband}/{activity}: acc={data['accelerometer_samples']}, "
                          f"gyr={data['gyroscope_samples']}, diff={data['difference']}")


if __name__ == "__main__":
    # Example usage
    dataset_csv_path = "datasets/realworld/dataset-csv"
    output_yaml_path = "datasets/realworld/sensor_comparison_upperarm.yaml"
    
    compare_sensor_samples(dataset_csv_path, output_yaml_path, sensor_location="upperarm")
