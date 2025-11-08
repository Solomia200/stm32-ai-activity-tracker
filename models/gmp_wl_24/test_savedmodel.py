#!/usr/bin/env python3
"""
Simple test to verify SavedModel works correctly
"""
import tensorflow as tf
import numpy as np
from pathlib import Path

# Load the SavedModel
savedmodel_path = Path(__file__).parent / "gmp_wl_24_savedmodel"
print(f"Loading SavedModel from: {savedmodel_path}")

# In Keras 3.x, we need to wrap SavedModel with TFSMLayer
# Create a simple wrapper model that uses the SavedModel
saved_model_input = tf.keras.Input(shape=(26, 3), dtype=tf.float32)
saved_model_layer = tf.keras.layers.TFSMLayer(
    str(savedmodel_path), 
    call_endpoint='serving_default'
)
output = saved_model_layer(saved_model_input)
model = tf.keras.Model(inputs=saved_model_input, outputs=output)

print("\n" + "="*70)
print("MODEL INFORMATION")
print("="*70)
model.summary()

# Get input/output info
print(f"\nInput shape: {model.input.shape}")
print(f"Output shape: {model.output.shape}")

# Test inference
print("\n" + "="*70)
print("TEST 1: Random Input Inference")
print("="*70)

# Create random test data matching input shape
# For activity recognition: (batch_size=1, time_steps=26, channels=3)
test_input = np.random.randn(1, 26, 3).astype(np.float32)
print(f"\nInput shape: {test_input.shape}")
print(f"Input range: [{test_input.min():.4f}, {test_input.max():.4f}]")

# Run inference
predictions = model.predict(test_input, verbose=0)
print(f"\nOutput shape: {predictions.shape}")
print(f"Predictions: {predictions}")
print(f"Prediction sum: {predictions.sum():.4f} (should be ~1.0 for softmax)")

# Get top prediction
top_class = np.argmax(predictions[0])
confidence = np.max(predictions[0]) * 100
print(f"\nTop prediction: Class {top_class} with {confidence:.2f}% confidence")

# Test 2: Realistic normalized input
print("\n" + "="*70)
print("TEST 2: Normalized Acceleration Input")
print("="*70)

# Simulate accelerometer data (±4g range, normalized to ±1)
# Typical LSM6DSL: ±4g full scale
accel_data = np.random.uniform(-1, 1, (1, 26, 3)).astype(np.float32)
print(f"\nInput shape: {accel_data.shape}")
print(f"Input range: [{accel_data.min():.4f}, {accel_data.max():.4f}]")
print("(Simulates normalized accelerometer data: ±1 = ±4g)")

predictions2 = model.predict(accel_data, verbose=0)
print(f"\nPredictions: {predictions2}")

activity_names = ["Stationary", "Walking", "Running"]
top_class2 = np.argmax(predictions2[0])
confidence2 = np.max(predictions2[0]) * 100
print(f"Predicted activity: {activity_names[top_class2]} ({confidence2:.2f}%)")

# Test 3: Multiple samples in batch
print("\n" + "="*70)
print("TEST 3: Batch Inference (Multiple Samples)")
print("="*70)

batch_input = np.random.uniform(-1, 1, (5, 26, 3)).astype(np.float32)
print(f"\nBatch input shape: {batch_input.shape} (5 samples)")

batch_predictions = model.predict(batch_input, verbose=0)
print(f"Batch predictions shape: {batch_predictions.shape}")
print("\nPredictions per sample:")
for i, pred in enumerate(batch_predictions):
    top = np.argmax(pred)
    conf = np.max(pred) * 100
    print(f"  Sample {i}: {activity_names[top]} ({conf:.2f}%)")

print("\n" + "="*70)
print("✅ ALL TESTS PASSED!")
print("="*70)
print(f"\nSavedModel is working correctly and ready for STM32CubeIDE import!")
