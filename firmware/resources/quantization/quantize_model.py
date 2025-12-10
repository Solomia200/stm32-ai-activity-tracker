import tensorflow as tf
import numpy as np
import yaml
import os
from pathlib import Path
from sklearn.model_selection import train_test_split
from tensorflow.keras.utils import to_categorical
from utils.numpy_array_processor import NumpyArrayProcessor
from model_evaluation.evaluate_model import evaluate_model


def quantize_model(model_path, output_path, dataset_path):
    """
    Quantize a Keras model to INT8 TFLite format with optimized calibration.
    
    Args:
        model_path: Path to the .h5 model file
        output_path: Path to save the quantized .tflite model
        dataset_path: Path to the numpy dataset directory for representative data
    """
    model = tf.keras.models.load_model(model_path)
    
    model_dir = os.path.dirname(model_path)
    norm_stats_path = os.path.join(model_dir, 'normalization_statistics.yaml')
    
    if not os.path.exists(norm_stats_path):
        raise FileNotFoundError(f"Normalization statistics not found at {norm_stats_path}")
    
    with open(norm_stats_path, 'r') as f:
        norm_stats = yaml.safe_load(f)
    
    mean = np.array([
        norm_stats['acc']['mean']['axis_1'],
        norm_stats['acc']['mean']['axis_2'],
        norm_stats['acc']['mean']['axis_3']
    ])
    std = np.array([
        norm_stats['acc']['sd']['axis_1'],
        norm_stats['acc']['sd']['axis_2'],
        norm_stats['acc']['sd']['axis_3']
    ])
    
    X, y = NumpyArrayProcessor.load_dataset(dataset_path)
    
    X = (X - mean) / std
    
    X_train, _, y_train, _ = train_test_split(X, y, test_size=0.2, random_state=42)
    
    data_min = np.min(X_train)
    data_max = np.max(X_train)
    optimal_scale = (data_max - data_min) / 255.0
    
    print(f"Data range: [{data_min:.3f}, {data_max:.3f}]")
    
    def representative_dataset():
        samples_per_class = 500
        indices = []
        
        for class_label in np.unique(y_train):
            class_indices = np.where(y_train == class_label)[0]
            n_samples = min(samples_per_class, len(class_indices))
            sampled = np.random.choice(class_indices, n_samples, replace=False)
            indices.extend(sampled)
        
        np.random.shuffle(indices)
        
        for i in indices:
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
    
    print(f"Quantized model saved to {output_path}")
    
    _, X_test, _, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    
    num_classes = int(np.unique(y_test).size)
    y_test_onehot = to_categorical(y_test, num_classes=num_classes)
    
    class TFLiteModelWrapper:
        def __init__(self, tflite_model_content):
            self.interpreter = tf.lite.Interpreter(model_content=tflite_model_content)
            self.interpreter.allocate_tensors()
            
            self.input_details = self.interpreter.get_input_details()
            self.output_details = self.interpreter.get_output_details()
            
            self.input_scale = self.input_details[0]['quantization'][0]
            self.input_zero_point = self.input_details[0]['quantization'][1]
            self.output_scale = self.output_details[0]['quantization'][0]
            self.output_zero_point = self.output_details[0]['quantization'][1]
        
        def predict(self, X):
            predictions = []
            for i in range(len(X)):
                input_data = X[i:i+1].astype(np.float32)
                input_quantized = (input_data / self.input_scale + self.input_zero_point).astype(np.int8)
                
                self.interpreter.set_tensor(self.input_details[0]['index'], input_quantized)
                self.interpreter.invoke()
                
                output_quantized = self.interpreter.get_tensor(self.output_details[0]['index'])
                output_float = (output_quantized.astype(np.float32) - self.output_zero_point) * self.output_scale
                
                predictions.append(output_float[0])
            
            return np.array(predictions)
    
    wrapped_model = TFLiteModelWrapper(tflite_model)
    
    print(f"Input quantization: scale={wrapped_model.input_scale:.6f}, zero_point={wrapped_model.input_zero_point}")
    print(f"Output quantization: scale={wrapped_model.output_scale:.6f}, zero_point={wrapped_model.output_zero_point}")
    
    model_dir = Path(os.path.dirname(model_path))
    eval_dir = model_dir / "evaluation" / "model-int8-quantized"
    eval_dir.mkdir(parents=True, exist_ok=True)
    
    evaluate_model(wrapped_model, X_test, y_test_onehot, str(eval_dir))
    print(f"Evaluated quantized model and saved results to {eval_dir}")
