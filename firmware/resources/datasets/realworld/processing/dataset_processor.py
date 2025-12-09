import re
import os
import pandas as pd
from pandas import DataFrame
import numpy as np
from numpy.typing import NDArray

from pathlib import Path

from . import utils


class DatasetProcessor:
    CLASS_TO_ID_MAPPING: dict[str: int] = {
        "walking": 0,
        "running": 1,
        "climbingdown": 2,
        "climbingup": 3,
        "jumping": None,
        "lying": 4,
        "sitting": 5,
        "standing": 6
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
    def __process_file(cls, path_to_file: Path, window_length: int, overlap_ratio: float=0) -> NDArray:
        df = cls.__read_file(path_to_file)
        cls.__interpolate_dataframe(df)
        windows = cls.__get_windows(df, window_length, overlap_ratio)
        return windows
    
    @classmethod
    def __process_files(cls, files: list[Path], window_length: int, overlap_ratio: float=0) -> NDArray:
        dfs = [cls.__read_file(f) for f in files]
        for df in dfs:
            cls.__interpolate_dataframe(df)
        if len(dfs) > 1:
            dfs[0], dfs[1] = utils.align_dataframes(dfs[0], dfs[1])
        combined_df = pd.concat(dfs, axis=1)
        windows = cls.__get_windows(combined_df, window_length, overlap_ratio)
        return windows
    
    @classmethod
    def __process_directory(cls, path_to_dir: Path, sensor_location: str, window_length: int, overlap_ratio: float=0) -> NDArray:
        print(path_to_dir)
        file = next(path_to_dir.glob(f"*{sensor_location}*.csv"))
        windows = cls.__process_file(file, window_length, overlap_ratio)
        return windows
    
    @classmethod
    def __process_directories(cls, dirs: list[Path], sensor_location: str, window_length: int, overlap_ratio: float=0) -> NDArray:
        files = [next(d.glob(f"*{sensor_location}*.csv")) for d in dirs]
        windows = cls.__process_files(files, window_length, overlap_ratio)
        return windows
    
    @classmethod
    def __process_subject(cls, path_to_subject: Path, sensor_location: str, sensors: list[str], window_length: int, overlap_ratio: float=0) -> tuple[list, list]:
        all_dirs = {sensor: list(path_to_subject.glob(f"data/{sensor}*")) for sensor in sensors}
        
        activity_match_pattern = re.compile(r"^.+_([a-z]+)_.+$")
        activity_dirs = {}
        for sensor in sensors:
            for dir in all_dirs[sensor]:
                activity_name = activity_match_pattern.match(dir.name).group(1)
                if activity_name not in activity_dirs:
                    activity_dirs[activity_name] = {}
                activity_dirs[activity_name][sensor] = dir
        
        samples = []
        labels = []
        for activity_name, sensor_dirs in activity_dirs.items():
            activity_id = cls.CLASS_TO_ID_MAPPING.get(activity_name)
            if activity_id is None:
                continue
            if len(sensor_dirs) != len(sensors):
                continue
            
            dirs = [sensor_dirs[s] for s in sensors]
            windows = cls.__process_directories(dirs, sensor_location, window_length, overlap_ratio)
            window_labels = [activity_id] * len(windows)
            samples.extend(windows)
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
                    sensors: list[str],
                    window_length: int,
                    overlap_ratio: float=0
                ) -> tuple[NDArray, NDArray]:

        base_path = Path(path_to_dataset)
        subjects = list(base_path.glob(f"proband*"))

        samples = []
        labels = []
        for subject in subjects:
            print(subject)

            subject_samples, subject_labels = cls.__process_subject(subject, sensor_location, sensors, window_length, overlap_ratio)

            samples.extend(subject_samples)
            labels.extend(subject_labels)

        return np.array(samples), np.array(labels)
