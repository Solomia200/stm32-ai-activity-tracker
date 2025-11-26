import os
import matplotlib.pyplot as plt


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
