"""
Inspect quantization parameters of a TFLite model.
Usage: python inspect_quantization.py path/to/model_quantized.tflite
"""

import tensorflow as tf
import sys

def inspect_model(model_path):
    # Load the quantized model
    interpreter = tf.lite.Interpreter(model_path=model_path)
    interpreter.allocate_tensors()
    
    # Get input details
    input_details = interpreter.get_input_details()[0]
    print("=" * 60)
    print("INPUT TENSOR")
    print("=" * 60)
    print(f"Name: {input_details['name']}")
    print(f"Shape: {input_details['shape']}")
    print(f"Data Type: {input_details['dtype']}")
    
    # Get quantization parameters
    quant_params = input_details['quantization_parameters']
    scales = quant_params['scales']
    zero_points = quant_params['zero_points']
    
    if len(scales) == 1:
        print("\nQuantization Type: Per-Tensor (global)")
        print(f"Scale: {scales[0]:.10f}")
        print(f"Zero Point: {zero_points[0]}")
        
        # Calculate the float range this represents
        min_float = ((-128) - zero_points[0]) * scales[0]
        max_float = (127 - zero_points[0]) * scales[0]
        print(f"\nFloat Range Mapped: [{min_float:.6f}, {max_float:.6f}]")
        
        # Generate C code
        print("\n" + "=" * 60)
        print("C CODE FOR STM32")
        print("=" * 60)
        print(f"const float INPUT_SCALE = {scales[0]:.10f}f;")
        print(f"const int INPUT_ZERO_POINT = {zero_points[0]};")
        
    else:
        print(f"\nQuantization Type: Per-Channel ({len(scales)} channels)")
        for i, (scale, zp) in enumerate(zip(scales, zero_points)):
            print(f"  Channel {i}: scale={scale:.10f}, zero_point={zp}")
        
        # Generate C code for per-channel
        print("\n" + "=" * 60)
        print("C CODE FOR STM32")
        print("=" * 60)
        print(f"const float INPUT_SCALE[{len(scales)}] = {{")
        for i, scale in enumerate(scales):
            print(f"    {scale:.10f}f{',' if i < len(scales)-1 else ''}")
        print("};")
        print(f"const int INPUT_ZERO_POINT[{len(zero_points)}] = {{")
        for i, zp in enumerate(zero_points):
            print(f"    {zp}{',' if i < len(zero_points)-1 else ''}")
        print("};")
    
    # Get output details
    output_details = interpreter.get_output_details()[0]
    print("\n" + "=" * 60)
    print("OUTPUT TENSOR")
    print("=" * 60)
    print(f"Name: {output_details['name']}")
    print(f"Shape: {output_details['shape']}")
    print(f"Data Type: {output_details['dtype']}")
    
    # Get output quantization parameters
    out_quant_params = output_details['quantization_parameters']
    out_scales = out_quant_params['scales']
    out_zero_points = out_quant_params['zero_points']
    
    if len(out_scales) == 1:
        print(f"\nScale: {out_scales[0]:.10f}")
        print(f"Zero Point: {out_zero_points[0]}")
        
        print("\n" + "=" * 60)
        print("C CODE FOR OUTPUT DEQUANTIZATION")
        print("=" * 60)
        print(f"const float OUTPUT_SCALE = {out_scales[0]:.10f}f;")
        print(f"const int OUTPUT_ZERO_POINT = {out_zero_points[0]};")
        print("\n// Dequantize output:")
        print("// float probability = (int8_output - OUTPUT_ZERO_POINT) * OUTPUT_SCALE;")
    
    print("\n" + "=" * 60)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python inspect_quantization.py path/to/model_quantized.tflite")
        sys.exit(1)
    
    model_path = sys.argv[1]
    inspect_model(model_path)
