from numpy.typing import NDArray
import yaml


def save_normalization_statistics(path_to_save: str, mean: NDArray, sd: NDArray):
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


    with open(path_to_save, "w", encoding="utf-8") as file:
        yaml.dump(yaml_dict, file)