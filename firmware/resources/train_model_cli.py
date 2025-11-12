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
import sys

import numpy as np
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import train_test_split

from datasets.strength_sence_dataset.processing.numpy_array_processor import NumpyArrayProcessor
from model_evaluation.plot_training import save_training_plots
from model_evaluation.evaluate_model import evaluate_model


def load_get_model(path: str):
    """Load a callable get_model (or get_gmp) from a Python file path.

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
    if hasattr(module, "get_gmp"):
        return getattr(module, "get_gmp")
    raise AttributeError("Provided module does not define get_model() or get_gmp()")


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

    # Load dataset
    print(f"Loading dataset from: {dataset_path}")
    X, y = NumpyArrayProcessor.load_dataset(dataset_path)

    # If labels start at 1, shift to 0-based
    if y.min() == 1:
        y = y - 1

    num_classes = int(np.unique(y).size)
    input_shape = (*(X.shape[1:]), 1)
    print(input_shape, num_classes)
    print(f"Dataset samples: {X.shape}, labels: {y.shape}, classes: {num_classes}")

    # Load get_model function
    print(f"Loading get_model from: {get_model_path}")
    get_model = load_get_model(get_model_path)

    # Build model
    model = get_model(input_shape=input_shape, num_classes=num_classes)
    optimizer = Adam(learning_rate=args.lr)
    model.compile(optimizer=optimizer, loss="categorical_crossentropy", metrics=["accuracy"]) 

    # Split dataset: first separate test set, then validation from remaining
    if not (0.0 <= args.test_size < 1.0 and 0.0 <= args.val_size < 1.0):
        print("val-size and test-size must be between 0 and 1")
        return 2

    X_trainval, X_test, y_trainval, y_test = train_test_split(
        X, y, test_size=args.test_size, random_state=42, shuffle=True
    )

    # compute relative validation size w.r.t remaining data
    remaining = 1.0 - args.test_size
    if remaining <= 0:
        print("test-size too large")
        return 2
    val_relative = args.val_size / remaining

    X_train, X_val, y_train, y_val = train_test_split(
        X_trainval, y_trainval, test_size=val_relative, random_state=42, shuffle=True
    )

    # One-hot encode
    y_train_o = to_categorical(y_train, num_classes=num_classes)
    y_val_o = to_categorical(y_val, num_classes=num_classes)
    y_test_o = to_categorical(y_test, num_classes=num_classes)

    # Prepare output folders
    out_root = Path(args.output_root)
    out_dir = out_root / f"train-{name}"
    training_plots_dir = out_dir / "training-path"
    evaluation_dir = out_dir / "evaluation"

    out_dir.mkdir(parents=True, exist_ok=True)
    training_plots_dir.mkdir(parents=True, exist_ok=True)
    evaluation_dir.mkdir(parents=True, exist_ok=True)

    # Train
    print(f"Training model, epochs={args.epochs}, batch_size={args.batch_size}")
    history = model.fit(
        X_train, y_train_o,
        validation_data=(X_val, y_val_o),
        epochs=args.epochs,
        batch_size=args.batch_size,
        shuffle=True,
    )

    # Save model as .h5
    h5_path = out_dir / f"{name}.h5"
    print(f"Saving model to {h5_path}")
    model.save(str(h5_path))


    # Save training plots
    print(f"Saving training plots to {training_plots_dir}")
    save_training_plots(history, str(training_plots_dir))

    # Evaluate on test set and save results
    print(f"Evaluating model on test set and saving to {evaluation_dir}")
    evaluate_model(model, X_test, y_test_o, str(evaluation_dir))

    print(f"Training complete. Outputs in: {out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
