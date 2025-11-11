import pandas as pd
import scipy as sp
from numpy.typing import NDArray

def _resample_series(col: pd.Series, initial_sampling_rate: float, target_sampling_rate: float) -> pd.Series:
    n_old = len(col)
    duration = n_old / initial_sampling_rate
    n_new = int(round(duration * target_sampling_rate))
    arr = col.to_numpy(dtype=float)
    arr_resampled = sp.signal.resample(arr, n_new)
    return pd.Series(arr_resampled, name=col.name)

def resample_dataframe(df: pd.DataFrame, initial_sampling_rate: int, target_sampling_rate: int) -> pd.DataFrame:
    df_resampled = pd.concat(
        [_resample_series(df[col], initial_sampling_rate, target_sampling_rate) for col in df.columns],
        axis = 1
    )
    return df_resampled

def split_to_windows(df: pd.DataFrame, window_length: int) -> NDArray:
    n_samples = len(df)
    n_windows = n_samples // window_length
    trimmed = df.to_numpy()[:window_length*n_windows]
    windows = trimmed.reshape(n_windows, window_length, 3) # 3 is number of axes of accelerometer
    return windows

def normalize_to_wisdm(val: float) -> float:
    return  val / sp.constants.g * 10
