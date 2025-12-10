import argparse
import os
from quantization.quantize_model import quantize_model
from quantization.extract_quantization_params import extract_quantization_params


def main():
    parser = argparse.ArgumentParser(description='Quantize a Keras model to INT8 TFLite format')
    parser.add_argument('model_path', help='Path to the .h5 model file')
    parser.add_argument('dataset_path', help='Path to the numpy dataset directory')
    parser.add_argument('output_path', help='Path to save the quantized .tflite model')
    
    args = parser.parse_args()
    
    quantize_model(args.model_path, args.output_path, args.dataset_path)
    
    output_dir = os.path.dirname(args.output_path)
    params_path = os.path.join(output_dir, 'quantization_data.yaml')
    extract_quantization_params(args.output_path, params_path)


if __name__ == '__main__':
    main()
