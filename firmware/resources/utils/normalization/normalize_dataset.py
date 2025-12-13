from numpy.typing import NDArray


def normalize_dataset(X: NDArray, mean: NDArray, sd: NDArray) -> NDArray:
    """
    Function normalizes values in the one dimentional np array using passed mean and standart deviation
    return: normalized np array
    """
    X = (X - mean) / sd

    return X