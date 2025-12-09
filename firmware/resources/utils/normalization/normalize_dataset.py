from numpy.typing import NDArray


def normalize_dataset(X: NDArray, mean: NDArray, sd: NDArray) -> NDArray:
    """
    Function normalizes values using passed mean and standard deviation.
    Broadcasting handles 3 channels (single sensor) or 6 channels (dual sensors) automatically.
    
    Args:
        X: Array of shape (N, window_length, n_channels)
        mean: Array of shape (n_channels,)
        sd: Array of shape (n_channels,)
    
    Returns:
        Normalized array of same shape as X
    """
    X = (X - mean) / sd

    return X