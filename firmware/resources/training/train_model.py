from pathlib import Path
import numpy as np
import tensorflow as tf
from tensorflow.keras.callbacks import EarlyStopping, LearningRateScheduler
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import train_test_split
import tensorflow_model_optimization as tfmot
import importlib.util
import sys

from model_evaluation.plot_training import save_training_plots
from model_evaluation.evaluate_model import evaluate_model

from utils.normalization.normalize_dataset import normalize_dataset
from utils.normalization.calculate_normalization_statistics import calculate_normalization_statistics
from utils.normalization.save_normalization_statistics import save_normalization_statistics


def load_get_model_func(model_file_path: str):
    """Dynamically load get_model function from a file path."""
    model_file = Path(model_file_path)
    if not model_file.exists():
        raise FileNotFoundError(f"Model file not found: {model_file}")
    spec = importlib.util.spec_from_file_location("get_model_module", model_file)
    mod = importlib.util.module_from_spec(spec)
    sys.modules["get_model_module"] = mod
    spec.loader.exec_module(mod)
    if not hasattr(mod, "get_model"):
        raise AttributeError(f"File {model_file} does not contain `get_model` function")
    return mod.get_model


def train_model(
        get_model_func: callable,
        X: np.ndarray,
        y: np.ndarray,
        name: str,
        out_root: str = "trained-models",
        lr: float = 1e-4,
        val_size: float = 0.1,
        test_size: float = 0.2,
        epochs: int = 100,
        batch_size: int = 32,
        patience: int = 8,
        delta: float = 1e-3,
    ):

    # Ensure labels start at 0
    if y.min() == 1:
        y = y - 1

    num_classes = int(np.unique(y).size)
    X = np.asarray(X)
    input_shape = tuple(X.shape[1:])

    print(f"Training: input_shape={input_shape}, classes={num_classes}")

    # --- create float Functional model ---
    model_float = get_model_func(input_shape=input_shape, num_classes=num_classes)

    if not isinstance(model_float, tf.keras.Model):
        raise TypeError("Model returned by get_model_func must be a Keras Model.")

    # Check if Functional or Sequential by checking model class
    if not isinstance(model_float, (tf.keras.Sequential, tf.keras.Model)):
        raise TypeError("Model must be a Functional or Sequential model.")

    # Optional: further check if Functional by verifying inputs/outputs exist
    if model_float.inputs is None or model_float.outputs is None:
        raise TypeError("Model does not have defined inputs/outputs; must be Functional or Sequential.")


    # --- enable QAT ---
    model = tfmot.quantization.keras.quantize_model(model_float)
    print("QAT enabled model created.")

    optimizer = Adam(learning_rate=lr)
    model.compile(
        optimizer=optimizer,
        loss="categorical_crossentropy",
        metrics=["accuracy"]
    )

    # --- learning rate scheduler ---
    def lr_scheduler(epoch):
        if epoch < 5:
            return lr
        elif epoch < 15:
            return lr * 0.5
        else:
            return lr * 0.1

    lr_callback = LearningRateScheduler(lr_scheduler, verbose=1)

    # --- train/val/test split ---
    X_trainval, X_test, y_trainval, y_test = train_test_split(
        X, y, test_size=test_size, random_state=42, shuffle=True
    )
    remaining = 1.0 - test_size
    val_relative = val_size / remaining
    X_train, X_val, y_train, y_val = train_test_split(
        X_trainval, y_trainval, test_size=val_relative, random_state=42, shuffle=True
    )

    # --- normalization ---
    mean, sd = calculate_normalization_statistics(X_train)
    X_train = normalize_dataset(X_train, mean, sd)
    X_val = normalize_dataset(X_val, mean, sd)
    X_test = normalize_dataset(X_test, mean, sd)

    # --- output directories ---
    out_root_path = Path(out_root)
    out_dir = out_root_path / name
    training_plots_dir = out_dir / "training-plots"
    evaluation_dir = out_dir / "evaluation"

    out_dir.mkdir(parents=True, exist_ok=True)
    training_plots_dir.mkdir(parents=True, exist_ok=True)
    evaluation_dir.mkdir(parents=True, exist_ok=True)

    path_to_save_statistics = out_dir / "normalization_statistics.yaml"
    save_normalization_statistics(path_to_save_statistics, mean, sd)

    # --- one-hot encode labels ---
    y_train_o = to_categorical(y_train, num_classes=num_classes)
    y_val_o = to_categorical(y_val, num_classes=num_classes)
    y_test_o = to_categorical(y_test, num_classes=num_classes)

    print(f"Training model, epochs={epochs}, batch_size={batch_size}")

    early_stop = EarlyStopping(
        monitor='val_loss',
        min_delta=delta,
        patience=patience,
        verbose=1,
        mode='min',
        restore_best_weights=True,
        start_from_epoch=5
    )

    # --- train ---
    history = model.fit(
        X_train,
        y_train_o,
        validation_data=(X_val, y_val_o),
        epochs=epochs,
        batch_size=batch_size,
        shuffle=True,
        callbacks=[early_stop, lr_callback]
    )

    # --- save model ---
    h5_path = out_dir / f"{name}.h5"
    print(f"Saving model to {h5_path}")
    model.save(str(h5_path))

    # --- save plots ---
    print(f"Saving training plots to {training_plots_dir}")
    save_training_plots(history, str(training_plots_dir))

    # --- evaluate ---
    print(f"Evaluating model on test set and saving to {evaluation_dir}")
    evaluate_model(model, X_test, y_test_o, str(evaluation_dir))

    print(f"Training complete. Outputs in: {out_dir}")
    return model, history
