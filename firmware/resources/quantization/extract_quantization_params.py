import tensorflow as tf
import yaml


def extract_quantization_params(model_path, output_path):
    """
    Extract quantization parameters from a TFLite model and save to YAML.
    
    Args:
        model_path: Path to the quantized .tflite model
        output_path: Path to save the YAML file with quantization parameters
    """
    interpreter = tf.lite.Interpreter(model_path=model_path)
    interpreter.allocate_tensors()
    
    input_details = interpreter.get_input_details()[0]
    output_details = interpreter.get_output_details()[0]
    
    input_quant = input_details['quantization_parameters']
    output_quant = output_details['quantization_parameters']
    
    params = {
        'input': {
            'scale': float(input_quant['scales'][0]),
            'zero_point': int(input_quant['zero_points'][0])
        },
        'output': {
            'scale': float(output_quant['scales'][0]),
            'zero_point': int(output_quant['zero_points'][0])
        }
    }
    
    with open(output_path, 'w') as f:
        yaml.dump(params, f, default_flow_style=False)
