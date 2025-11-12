import re
import pandas as pd
from pandas import DataFrame
import numpy as np
from numpy.typing import NDArray
from . import utils
import pathlib


class DatasetProcessor:
    BODY_LOCATION_MAPPING: dict[str: int] = { # 1 for upper locations, 2 for lower 
        "CHS": 1, # Chest
        "LU": 1, # Left Upper-Arm
        "RU": 1, # Right Upper-Arm
        "LF": 1, # Left Forearm
        "RF": 1, # Right Forearm
        "WAS": 2, # Waist
        "LT": 2, # Left Thigh
        "RT": 2, # Right Thigh
        "LC": 2, # Left Shin
        "RC": 2 # Right Shin
    }

    # 1 - Walking
    # 2 - Transition between positions
    # 3 - Greet cammera with hands
    # 4 - Opening a bottle of water, pouring water into a glass, and drinking
    # 5 - Stairs
    # 6 - Push-ups
    # 7 - Sit-ups
    # 8 - Squats
    CLASSES_MAPPING = {
        1: 1, # Walking
        2: 2, # Transition between positions
        3: 1, # Walking
        4: 1, # Walking
        5: 2, # Transition between positions
        6: 2, # Transition between positions
        7: 2, # Transition between positions
        8: None, # Greet cammera with hands
        9: 3, # Opening a bottle of water, pouring water into a glass, and drinking
        10: 4, # Stairs
        11: 5, # Push-ups
        12: 6, # Sit-ups
        13: 7  # Squats
    }

    @staticmethod
    def __read_file(path_to_dataset: pathlib.Path, sensor_location: str, sensor: str) -> DataFrame:
        pattern = re.compile(fr"^{sensor_location}_IMU9_{sensor}_\w$")
        df = pd.read_csv(path_to_dataset)
        cols = [col for col in df.columns if pattern.match(col)]
        df = df[cols]
        df.astype(dtype=float, copy=False)
        return df
    
    @staticmethod
    def __interpolate_dataframe(df: DataFrame) -> None:
        "Interpolates dataframe in place using linear interpolation"
        df.interpolate(method="linear", limit_direction="both", inplace=True)

    @staticmethod
    def __normalize_dataframe(df: DataFrame) -> DataFrame:
        df = df.apply(lambda col: col.map(utils.normalize_to_wisdm))
        return df
    
    @staticmethod
    def __resample_dataframe(df: DataFrame, sampling_rate: float=52, target_sampling_rate: float=20):
        df = utils.resample_dataframe(df, sampling_rate, target_sampling_rate)
        return df

    @classmethod
    def process_file(cls, path_to_dataset: str, sensor_position: str, sensor: str, resample: bool=False, sampling_rate: float=52, target_sampling_rate: float=20) -> DataFrame:
        df = cls.__read_file(path_to_dataset, sensor_position, sensor)
        cls.__interpolate_dataframe(df)
        if resample:
            df = cls.__resample_dataframe(df, sampling_rate, target_sampling_rate)
        df = cls.__normalize_dataframe(df)
        return df

    @staticmethod
    def get_windows(df: DataFrame, window_length: int) -> NDArray:
        windows = utils.split_to_windows(df=df, window_length=window_length)
        return windows

    @classmethod
    def process_dataset(cls, path_to_dataset: str, sensor_location: str, sensor: str, window_length: int=48, resample: bool=False, sampling_rate: float=52, target_sampling_rate: float=20) -> tuple[NDArray, NDArray]:
        laptop_num: int = cls.BODY_LOCATION_MAPPING[sensor_location]

        base_path = pathlib.Path(path_to_dataset)
        files: list[pathlib.Path] = list(base_path.glob(f"subject*/laptop{laptop_num}/IMU9/*.csv"))

        activity_search_pattern = re.compile(r"^.+a(\d{1,2}).+$")
        samples = []
        labels = []
        for file in files:
            print(file)
            df = cls.process_file(file, sensor_location, sensor, resample, sampling_rate, target_sampling_rate)
            label = int(activity_search_pattern.search(file.stem).group(1))
            label = cls.CLASSES_MAPPING[label]
            if label is None:
                continue

            windows = cls.get_windows(df, window_length)
            samples.extend(windows)

            file_labels = np.full(shape=len(windows), fill_value=label)
            labels.extend(file_labels)
        
        return np.array(samples), np.array(labels)
