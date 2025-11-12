"""Train a model from a provided get_model() implementation on a saved numpy dataset.

Usage example:
  python train_model_cli.py /path/to/get_model.py /path/to/dataset-dir model-name --lr 1e-4 --val-size 0.1 --test-size 0.2

The dataset-dir should contain `samples.npy` and `labels.npy` (as produced by the dataset processor).
This script will create `trains/train-<model-name>/` and inside it save:
 - <model-name>.h5 (Keras HDF5)
 - `keras_saved_model/` (SavedModel)
 - `training-path/` (training plots)
 - `evaluation/` (metrics + confusion matrix)
"""
from __future__ import annotations

import argparse
import importlib.util
from pathlib import Path

import numpy as np

from datasets.strength_sence_dataset.processing.numpy_array_processor import NumpyArrayProcessor
from training.train_model import train_model


def load_get_model(path: str):
    """Load a callable get_model from a Python file path.

    Returns the function object.
    """
    p = Path(path).expanduser().resolve()
    if not p.exists():
        raise FileNotFoundError(f"get_model file not found: {p}")

    spec = importlib.util.spec_from_file_location(p.stem, str(p))
    if spec is None or spec.loader is None:
        raise ImportError(f"Cannot import module from path: {p}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    if hasattr(module, "get_model"):
        return getattr(module, "get_model")
    raise AttributeError("Provided module does not define get_model()")


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Train a model using a provided get_model() implementation")
    p.add_argument("get_model_path", help="Path to a .py file that defines get_model(input_shape, num_classes)")
    p.add_argument("dataset_path", help="Path to dataset directory containing samples.npy and labels.npy")
    p.add_argument("name", help="Name for the trained model (used to create trains/train-<name>)")

    p.add_argument("--lr", type=float, default=1e-4, help="Learning rate (default: 1e-4)")
    p.add_argument("--val-size", type=float, default=0.1, help="Validation set fraction (default: 0.1)")
    p.add_argument("--test-size", type=float, default=0.2, help="Test set fraction (default: 0.2)")
    p.add_argument("--epochs", type=int, default=100, help="Number of epochs (default: 100)")
    p.add_argument("--batch-size", type=int, default=32, help="Batch size (default: 32)")
    p.add_argument("--output-root", default="trains", help="Root folder to store training outputs (default: ./trains)")

    return p.parse_args()


def main() -> int:
    args = parse_args()

    get_model_path = args.get_model_path
    dataset_path = args.dataset_path
    name = args.name

    print(f"Loading dataset from: {dataset_path}")
    X, y = NumpyArrayProcessor.load_dataset(dataset_path)

    num_classes = int(np.unique(y).size)
    input_shape = (*(X.shape[1:]), 1)
    print(f"Dataset samples: {X.shape}, labels: {y.shape}, classes: {num_classes}")
    print(f"Input shape: {input_shape}")

    print(f"Loading get_model from: {get_model_path}")
    get_model = load_get_model(get_model_path)

    train_model(
        get_model_func=get_model,
        X=X,
        y=y,
        name=name,
        out_root=args.output_root,
        lr=args.lr,
        val_size=args.val_size,
        test_size=args.test_size,
        epochs=args.epochs,
        batch_size=args.batch_size,
    )

    return 0



if __name__ == "__main__":
    raise SystemExit(main())
