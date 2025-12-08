import pathlib
import pandas as pd
import matplotlib.pyplot as plt
from collections import defaultdict
import re

def plot_class_presence(dataset_path):
    class_counts = defaultdict(int)
    
    base_path = pathlib.Path(dataset_path)
    
    all_files = list(base_path.glob("subject*/laptop1/IMU9/*.csv"))
        
    activity_pattern = re.compile(r"_a(\d{1,2})")
    
    for file_path in all_files:
        match = activity_pattern.search(file_path.stem)
        if match:
            class_num = int(match.group(1))
            
            df = pd.read_csv(file_path)
            
            chs_acc_cols = [col for col in df.columns if 'CHS_IMU9_Acc' in col]
            
            if chs_acc_cols:
                class_counts[class_num] += len(df)
    
    classes = sorted(class_counts.keys())
    counts = [class_counts[c] for c in classes]
    
    plt.figure(figsize=(12, 6))
    plt.bar(classes, counts)
    plt.xlabel('Activity Class')
    plt.ylabel('Number of Entities (Rows)')
    plt.title('Class Presence in Dataset (CHS Accelerometer)')
    plt.xticks(classes)
    plt.grid(axis='y', alpha=0.3)
    plt.tight_layout()
    plt.savefig("class_presence.png")
    
    print(f"Total files processed: {len(all_files)}")
    print(f"Classes found: {classes}")
    print(f"Class counts: {dict(class_counts)}")
    
    return class_counts


if __name__ == "__main__":
    plot_class_presence("../dataset-csv")