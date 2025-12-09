import numpy as np
from numpy.typing import NDArray


def calculate_normalization_statistics(X: NDArray) -> tuple[NDArray, NDArray]:
    """
    Function calculates sample mean and sample standard deviation of given sample.
    Statistics are calculated separately for each sensor axis.
    
    Args:
        X: Array of shape (N, window_length, n_channels) where n_channels is 3 for single sensor or 6 for dual sensors
    
    Returns:
        tuple: (mean, sd) where each is np array of size n_channels
    """
    mean = X.mean(axis=(0, 1))
    sd = X.std(axis=(0, 1), ddof=1)

    return mean, sd