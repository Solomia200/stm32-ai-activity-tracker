import tensorflow as tf
import numpy as np
from sklearn.model_selection import train_test_split
from utils.numpy_array_processor import NumpyArrayProcessor
from utils.normalization.normalize_dataset import normalize_dataset
from utils.normalization.calculate_normalization_statistics import calculate_normalization_statistics


def ptq_h5_to_tflite(h5_model_path: str, tflite_output_path: str, representative_data_gen=None):
    """
    Converts a Keras .h5 model to a fully INT8 quantized TFLite model using PTQ.

    Parameters:
    - h5_model_path: str
        Path to the input Keras .h5 model file.
    - tflite_output_path: str
        Path to save the quantized .tflite model.
    - representative_data_gen: callable, optional
        Function yielding batches of input data for calibration. Required for full INT8 quantization.
        Example:
            def representative_data_gen():
                for input_value in dataset.take(100):
                    yield [input_value]
    """
    # Load Keras model
    model = tf.keras.models.load_model(h5_model_path)

    # Create a TFLite converter
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    
    # Enable optimizations for PTQ
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    
    if representative_data_gen is not None:
        converter.representative_dataset = representative_data_gen
        # Enforce full integer quantization
        converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
        # Set input and output to INT8
        converter.inference_input_type = tf.int8
        converter.inference_output_type = tf.int8

    # Convert the model
    tflite_model = converter.convert()

    # Save the TFLite model
    with open(tflite_output_path, 'wb') as f:
        f.write(tflite_model)

    print(f"Quantized model saved to {tflite_output_path}")


if __name__ == "__main__":
    # Quantize model - update these paths to match your model
    h5_model_path = "trained-models/realworld-dataset/wl-96-overlap-50/wl-96-overlap-50.h5"
    tflite_output_path = "trained-models/realworld-dataset/wl-96-overlap-50/wl-96-overlap-50-quantized.tflite"
    
    # Load dataset - MUST match the dataset used to train the model
    # For wl-96-overlap-50: use wl-96-overlap-50 dataset (shape: N, 96, 3)
    dataset_path = "datasets/realworld/datasets-np/wl-96-overlap-50"
    X, y = NumpyArrayProcessor.load_dataset(dataset_path)
    
    print(f"Loaded dataset: X.shape={X.shape}, y.shape={y.shape}")
    
    # Adjust labels if needed
    if y.min() == 1:
        y = y - 1
    
    # Split dataset with same parameters as training
    test_size = 0.2
    val_size = 0.1
    
    X_trainval, X_test, y_trainval, y_test = train_test_split(
        X, y, test_size=test_size, random_state=42, shuffle=True
    )
    
    remaining = 1.0 - test_size
    val_relative = val_size / remaining
    
    X_train, X_val, y_train, y_val = train_test_split(
        X_trainval, y_trainval, test_size=val_relative, random_state=42, shuffle=True
    )
    
    print(f"Split sizes: train={len(X_train)}, val={len(X_val)}, test={len(X_test)}")
    
    # Calculate normalization statistics and normalize
    mean, sd = calculate_normalization_statistics(X_train)
    X_train_norm = normalize_dataset(X_train, mean, sd)
    
    print(f"Normalization: mean.shape={mean.shape}, sd.shape={sd.shape}")
    
    # Representative data generator
    def rep_data():
        for x in X_train_norm[:100]:
            # Add batch dimension: (96, 3) -> (1, 96, 3)
            yield [np.expand_dims(x, axis=0).astype('float32')]
    
    print(f"\nQuantizing model: {h5_model_path}")
    ptq_h5_to_tflite(h5_model_path, tflite_output_path, rep_data)
    print("Done!")