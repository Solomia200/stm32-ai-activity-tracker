from pathlib import Path
import numpy as np
from tensorflow.keras.callbacks import EarlyStopping
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import train_test_split

from model_evaluation.plot_training import save_training_plots
from model_evaluation.evaluate_model import evaluate_model

from utils.normalization.normalize_dataset import normalize_dataset
from utils.normalization.calculate_normalization_statistics import calculate_normalization_statistics
from utils.normalization.save_normalization_statistics import save_normalization_statistics


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
    """
    Train model given data and a get_model function.

    This function builds, trains, saves and evaluates the model. It mirrors the
    previous logic in main() but is factored for reuse and testing.
    """
    if y.min() == 1:
        y = y - 1

    num_classes = int(np.unique(y).size)

    X = np.asarray(X)

    input_shape = tuple(X.shape[1:])

    print(f"Training: input_shape={input_shape}, classes={num_classes}")

    model = get_model_func(input_shape=input_shape, num_classes=num_classes)
    optimizer = Adam(learning_rate=lr)
    model.compile(
        optimizer=optimizer,
        loss="categorical_crossentropy",
        metrics=["accuracy"]
    )

    if not (0.0 <= test_size < 1.0 and 0.0 <= val_size < 1.0):
        raise ValueError("val_size and test_size must be between 0 and 1")

    X_trainval, X_test, y_trainval, y_test = train_test_split(
        X, y, test_size=test_size, random_state=42, shuffle=True
    )

    remaining = 1.0 - test_size
    if remaining <= 0:
        raise ValueError("test_size too large")
    val_relative = val_size / remaining

    X_train, X_val, y_train, y_val = train_test_split(
        X_trainval, y_trainval, test_size=val_relative, random_state=42, shuffle=True
    )

    mean, sd = calculate_normalization_statistics(X_train)

    X_train = normalize_dataset(X_train, mean, sd)
    X_val = normalize_dataset(X_val, mean, sd)
    X_test = normalize_dataset(X_test, mean, sd)
    
    out_root_path = Path(out_root)
    out_dir = out_root_path / name
    training_plots_dir = out_dir / "training-path"
    evaluation_dir = out_dir / "evaluation"

    out_dir.mkdir(parents=True, exist_ok=True)
    training_plots_dir.mkdir(parents=True, exist_ok=True)
    evaluation_dir.mkdir(parents=True, exist_ok=True)

    path_to_save_statistics = out_dir / "normalization_statistics.yaml"
    save_normalization_statistics(path_to_save_statistics, mean, sd)

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
        baseline=None,
        restore_best_weights=True,
        start_from_epoch=5
    )

    history = model.fit(
        X_train,
        y_train_o,
        validation_data=(X_val, y_val_o),
        epochs=epochs,
        batch_size=batch_size,
        shuffle=True,
        callbacks=[early_stop]
    )

    h5_path = out_dir / f"{name}.h5"
    print(f"Saving model to {h5_path}")
    model.save(str(h5_path))

    print(f"Saving training plots to {training_plots_dir}")
    save_training_plots(history, str(training_plots_dir))

    print(f"Evaluating model on test set and saving to {evaluation_dir}")
    evaluate_model(model, X_test, y_test_o, str(evaluation_dir))

    print(f"Training complete. Outputs in: {out_dir}")
    return model, history
