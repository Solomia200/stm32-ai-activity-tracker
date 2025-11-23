import numpy as np
from numpy.typing import NDArray
from pathlib import Path


class NumpyArrayProcessor:
    @staticmethod
    def save_dataset(dir_to_save: str, samples_arr: NDArray, labels_arr: NDArray) -> None:
        dir_to_save = Path(dir_to_save)
        dir_to_save.mkdir(exist_ok=True)

        samples_file = dir_to_save / "samples"
        labels_file = dir_to_save / "labels"

        np.save(samples_file, samples_arr)
        np.save(labels_file, labels_arr)

    @staticmethod
    def load_dataset(path_to_dataset_dir: str) -> tuple[NDArray, NDArray]:
        path_to_dataset_dir = Path(path_to_dataset_dir)
        samples_arr = np.load(path_to_dataset_dir / "samples.npy")
        labels_arr = np.load(path_to_dataset_dir / "labels.npy")
        return samples_arr, labels_arr
