import tensorflow as tf
import numpy as np
from sklearn.model_selection import train_test_split
from utils.numpy_array_processor import NumpyArrayProcessor


def quantize_model(model_path, output_path, dataset_path):
    """
    Quantize a Keras model to INT8 TFLite format.
    
    Args:
        model_path: Path to the .h5 model file
        output_path: Path to save the quantized .tflite model
        dataset_path: Path to the numpy dataset directory for representative data
    """
    model = tf.keras.models.load_model(model_path)
    
    X, y = NumpyArrayProcessor.load_dataset(dataset_path)
    X_train, _, _, _ = train_test_split(X, y, test_size=0.2, random_state=42)
    
    def representative_dataset():
        for i in range(min(1000, len(X_train))):
            yield [np.expand_dims(X_train[i], axis=0).astype('float32')]
    
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    converter.representative_dataset = representative_dataset
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
    converter.inference_input_type = tf.int8
    converter.inference_output_type = tf.int8
    
    tflite_model = converter.convert()
    
    with open(output_path, 'wb') as f:
        f.write(tflite_model)
