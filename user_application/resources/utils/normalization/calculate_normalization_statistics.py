import numpy as np
from numpy.typing import NDArray


def calculate_normalization_statistics(X: NDArray) -> tuple[NDArray, NDArray]:
    """
    Function calculates sample mean and sample standart deviation of given sample.
    Statistics are calculated separately for each axis of accelerometer.
    
    return: tuple, first element is np array of size 3 where each element is mean of corresponding axis sample,
    second element is np array of size 3 where each element is standart deviation of corresponding axis sample
    """
    mean = X.mean(axis=(0, 1))
    sd = X.std(axis=(0, 1), ddof=1)

    return mean, sd