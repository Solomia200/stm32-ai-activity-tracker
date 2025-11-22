import pandas as pd
import scipy as sp
import numpy as np
from numpy.typing import NDArray


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
