import pandas as pd
import numpy as np

import pandas as pd
import numpy as np

def map_acc_to_gyro(acc_file, gyro_file):
    """
    Map accelerometer axes to gyroscope axes using correlation.
    
    Args:
        acc_file (str): path to accelerometer CSV file
        gyro_file (str): path to gyroscope CSV file
    
    Returns:
        mapping (dict): accelerometer axis -> gyroscope axis, e.g. {'attr_x': 'attr_y', ...}
        signs (dict): +1 if directions match, -1 if inverted
    """
    # Load datasets
    acc = pd.read_csv(acc_file)
    gyro = pd.read_csv(gyro_file)
    
    # Keep only x, y, z columns
    acc_axes = ['attr_x', 'attr_y', 'attr_z']
    gyro_axes = ['attr_x', 'attr_y', 'attr_z']
    
    acc_data = acc[acc_axes]
    gyro_data = gyro[gyro_axes]
    
    # Trim both to the shortest length
    min_len = min(len(acc_data), len(gyro_data))
    acc_data = acc_data.iloc[:min_len]
    gyro_data = gyro_data.iloc[:min_len]
    
    # Compute pairwise correlations
    correlations = pd.DataFrame(index=acc_axes, columns=gyro_axes, dtype=float)
    for a in acc_axes:
        for g in gyro_axes:
            correlations.loc[a, g] = np.corrcoef(acc_data[a], gyro_data[g])[0,1]
    
    # Map each accelerometer axis to the gyro axis with max absolute correlation
    mapping = {}
    signs = {}
    used_gyro_axes = set()
    
    for a in acc_axes:
        # Sort by absolute correlation
        sorted_axes = correlations.loc[a].abs().sort_values(ascending=False)
        for g in sorted_axes.index:
            if g not in used_gyro_axes:
                mapping[a] = g
                signs[a] = np.sign(correlations.loc[a, g])
                used_gyro_axes.add(g)
                break
    
    return mapping, signs


if __name__ == "__main__":
    mapping = map_acc_to_gyro("/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/realworld/dataset-csv/proband1/data/acc_walking_csv/acc_walking_upperarm.csv",
                              "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/realworld/dataset-csv/proband1/data/gyr_walking_csv/Gyroscope_walking_upperarm.csv"
                            )
    print(mapping)
