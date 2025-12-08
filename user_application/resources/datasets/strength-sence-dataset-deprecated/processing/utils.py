import pandas as pd
import scipy as sp
import numpy as np
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


# def split_to_windows(df: pd.DataFrame, window_length: int) -> NDArray:
#     n_samples = len(df)
#     n_windows = n_samples // window_length

#     if n_windows == 0:
#         n_axes = df.shape[1] if getattr(df, "shape", None) and df.shape[1] is not None else 3
#         return np.empty((0, window_length, n_axes))

#     trimmed = df.to_numpy()[: window_length * n_windows]
#     n_axes = trimmed.shape[1]
#     windows = trimmed.reshape(n_windows, window_length, n_axes)  # axes last
#     return windows


def split_to_windows(df: pd.DataFrame, window_length: int, overlap_ratio: float=0) -> NDArray:
    """
    Convert a dataframe of shape (n_samples, n_axes) into overlapping windows.

    Args:
      df: pandas.DataFrame with columns = axes (e.g. 3) and rows = samples.
      window_length: length of each window in samples (W).
      overlap: fraction [0..1) of overlap between windows. Used only when step is None (default 0.0).

    Returns:
      ndarray of shape (n_windows, window_length, n_axes).
    """
    n_samples = len(df)
    if n_samples < window_length:
        n_axes = df.shape[1] if getattr(df, "shape", None) and df.shape[1] is not None else 3
        return np.empty((0, window_length, n_axes))
    
    if not (0 <= overlap_ratio < 1):
        raise ValueError("overlap must be in [0, 1)")
    
    step = max(1, round(window_length * (1-overlap_ratio)))

    n_windows = 1 + (n_samples - window_length) // step

    arr = df.to_numpy(dtype=float)
    n_axes = arr.shape[1]
    windows = np.empty((n_windows, window_length, n_axes), dtype=arr.dtype)

    idx = 0
    for start in range(0, n_samples-window_length+1, step):
        windows[idx] = arr[start : start + window_length]
        idx += 1

    return windows


def normalize_to_wisdm(val: float) -> float:
    return  val / sp.constants.g * 10
