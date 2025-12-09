from numpy.typing import NDArray
import yaml


def save_normalization_statistics(path_to_save: str, mean: NDArray, sd: NDArray):
    n_channels = len(mean)
    
    if n_channels == 3:
        yaml_dict = {
            "acc": {
                "mean": {
                    "axis_1": float(mean[0]),
                    "axis_2": float(mean[1]),
                    "axis_3": float(mean[2])
                },
                "sd": {
                    "axis_1": float(sd[0]),
                    "axis_2": float(sd[1]),
                    "axis_3": float(sd[2])
                }
            }
        }
    elif n_channels == 6:
        yaml_dict = {
            "acc": {
                "mean": {
                    "axis_1": float(mean[0]),
                    "axis_2": float(mean[1]),
                    "axis_3": float(mean[2])
                },
                "sd": {
                    "axis_1": float(sd[0]),
                    "axis_2": float(sd[1]),
                    "axis_3": float(sd[2])
                }
            },
            "gyr": {
                "mean": {
                    "axis_1": float(mean[3]),
                    "axis_2": float(mean[4]),
                    "axis_3": float(mean[5])
                },
                "sd": {
                    "axis_1": float(sd[3]),
                    "axis_2": float(sd[4]),
                    "axis_3": float(sd[5])
                }
            }
        }
    else:
        raise ValueError(f"Expected 3 or 6 channels, got {n_channels}")

    with open(path_to_save, "w", encoding="utf-8") as file:
        yaml.dump(yaml_dict, file)