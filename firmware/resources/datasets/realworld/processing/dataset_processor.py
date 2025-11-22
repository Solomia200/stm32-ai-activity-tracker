import re
import os
import pandas as pd
from pandas import DataFrame
import numpy as np
from numpy.typing import NDArray

import pathlib
from pathlib import Path

import utils


class DatasetProcessor:
    CLASS_TO_ID_MAPPING: dict[str: int] = {
        "walking": 0,
        "running": 1,
        "climbingdown": 2,
        "climbingup": 3,
        "jumping": 4,
        "lying": 5,
        "sitting": 6,
        "standing": 7
    }

    @staticmethod
    def __read_file(path_to_file: Path) -> DataFrame:
        pattern = re.compile(fr"^attr_[xyz]$")
        df = pd.read_csv(path_to_file)
        cols = [col for col in df.columns if pattern.match(col)]
        df = df[cols]
        df.astype(dtype=float, copy=False)
        return df
    
    @staticmethod
    def __interpolate_dataframe(df: DataFrame) -> None:
        "Interpolates dataframe in place using linear interpolation"
        df.interpolate(method="linear", limit_direction="both", inplace=True)

    @classmethod
    def __process_file(cls, path_to_file: Path) -> DataFrame:
        df = cls.__read_file(path_to_file)
        cls.__interpolate_dataframe(df)
        return df
    
    @classmethod
    def __process_directory(cls, path_to_dir: Path, sensor_location: str) -> DataFrame:
        file = next(path_to_dir.glob(f"*{sensor_location}*.csv"))
        df = cls.__process_file(file)
        return df
    
    @classmethod
    def __process_subject(cls, path_to_subject: Path, sensor_location: str, sensor: str, window_length: int, overlap_ratio: float=0) -> tuple[list, list]:
        directories: list[Path] = list(path_to_subject.glob(f"data/{sensor}*"))

        activity_match_pattern = re.compile(r"^.+_([a-z]+)_.+$")
        samples = []
        labels = []
        for dir in directories:
            df = cls.__process_directory(dir, sensor_location)

            windows = cls.__get_windows(df, window_length, overlap_ratio)

            samples.extend(windows)
            # print(dir.name)
            activity_name = activity_match_pattern.match(dir.name).group(1)
            activity_id = cls.CLASS_TO_ID_MAPPING[activity_name]
            window_labels = [activity_id] * len(windows)
            labels.extend(window_labels)
        
        return samples, labels

    @staticmethod
    def __get_windows(df: DataFrame, window_length: int, overlap_ratio: float=0) -> NDArray:
        windows = utils.split_to_windows(df=df, window_length=window_length, overlap_ratio=overlap_ratio)
        return windows

    @classmethod
    def process_dataset(cls,
                    path_to_dataset: str,
                    sensor_location: str,
                    sensor: str,
                    window_length: int=48,
                    overlap_ratio: float=0
                ) -> tuple[NDArray, NDArray]:

        base_path = Path(path_to_dataset)
        subjects: list[Path] = list(base_path.glob(f"proband*"))

        samples = []
        labels = []
        for subject in subjects:
            print(subject)
            if subject.name in ("proband4", "proband7", "proband14"):
                continue

            subject_samples, subject_labels = cls.__process_subject(subject, sensor_location, sensor, window_length, overlap_ratio)

            samples.extend(subject_samples)
            labels.extend(subject_labels)

        return np.array(samples), np.array(labels)


if __name__ == "__main__":
    path_to_dataset = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/realworld/dataset-csv"
    samples, labels = DatasetProcessor.process_dataset(path_to_dataset, sensor="acc", sensor_location="upperarm", window_length=96, overlap_ratio=0)
    print(len(samples), len(labels))

    import matplotlib.pyplot as plt
    values, counts = np.unique(labels, return_counts=True)
    plt.bar(values, counts, edgecolor='black')
    plt.xlabel('Value')
    plt.ylabel('Count')
    plt.title('Histogram of counts')
    plt.show()