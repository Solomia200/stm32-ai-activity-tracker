import tensorflow as tf
from tensorflow.keras.models import load_model, Model
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import train_test_split
import os
import numpy as np
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
from datasets.strength_sence_dataset.processing.numpy_array_processor import NumpyArrayProcessor
from evaluate_model import evaluate_model
# from models.gmp_wl_24.gmp import get_gmp
from models.our_model.gmp_our import get_gmp


def get_model(path_to_model: str):
    # pretrained_model = load_model(path_to_model)
    # pretrained_model.summary()

    # print(len(pretrained_model.layers))
    # for layer in pretrained_model.layers:
    #     layer.trainable = False

    # x = pretrained_model.layers[-2].output
    # new_output = Dense(13, activation="softmax", name="output_13_classes")(x)
    # new_model = Model(inputs=pretrained_model.input, outputs=new_output)
    # new_model.summary()

    new_model = get_gmp(input_shape=(48, 3, 1), num_classes=13)
    optimizer = Adam(learning_rate=1e-4)
    new_model.compile(
        optimizer=optimizer,
        loss="categorical_crossentropy",
        metrics=["accuracy"]
    )

    X, y = NumpyArrayProcessor.load_dataset("datasets/strength_sence_dataset/dataset-np-array-no-resampling")
    y -= 1

    # counts = np.bincount(y)
    # plt.bar(np.arange(len(counts)), counts)
    # plt.show()

    X_train, X_test, y_train, y_test = train_test_split(
        X,
        y,
        test_size=0.4,
        random_state=42,
        shuffle=True
    )
    X_train, X_val, y_train, y_val = train_test_split(
        X_train,
        y_train,
        test_size=0.5,
        random_state=42,
        shuffle=True
    )

    y_train = to_categorical(y_train, num_classes=13)
    y_val = to_categorical(y_val, num_classes=13)
    y_test = to_categorical(y_test, num_classes=13)

    history = new_model.fit(
        X_train, y_train,
        validation_data=(X_val, y_val),
        epochs=300,
        batch_size=32,
        shuffle=True
    )

    save_training_plots(history, "models/our_model/our_model_training_history")
    new_model.save("models/our_model/our_model.h5")
    evaluate_model(new_model, X_test, y_test, "models/our_model/our_model_metrics")


def save_training_plots(history, save_dir):
    """
    Save training and validation loss and accuracy plots from Keras History object.

    Parameters
    ----------
    history : keras.callbacks.History
        The History object returned by model.fit().
    save_dir : str
        Path to directory where plots will be saved. Will be created if it does not exist.
    """
    # Ensure directory exists
    os.makedirs(save_dir, exist_ok=True)
    
    # Plot Loss
    plt.figure()
    plt.plot(history.history['loss'], label='train_loss')
    if 'val_loss' in history.history:
        plt.plot(history.history['val_loss'], label='val_loss')
    plt.title('Model Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.grid(True)
    loss_path = os.path.join(save_dir, 'loss.png')
    plt.savefig(loss_path)
    plt.close()
    
    # Plot Accuracy
    plt.figure()
    if 'accuracy' in history.history:
        plt.plot(history.history['accuracy'], label='train_accuracy')
    if 'val_accuracy' in history.history:
        plt.plot(history.history['val_accuracy'], label='val_accuracy')
    plt.title('Model Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.grid(True)
    acc_path = os.path.join(save_dir, 'accuracy.png')
    plt.savefig(acc_path)
    plt.close()
    
    print(f"Plots saved in directory: {save_dir}")


if __name__ == "__main__":
    path_to_model = "models/gmp_wl_24/recompiled_gmp_wl_24.h5"
    get_model(path_to_model)
