/*
 * quantization.c
 *
 *  Created on: Dec 10, 2025
 *      Author: bohdan
 */


#include "quantization.h"
#include <math.h>


int8_t quantize_float_to_int8(float value, float scale, int32_t zero_point) {
    int32_t quantized = (int32_t)roundf(value / scale) + zero_point;

    if (quantized < -128) {quantized = -128;}
    else if (quantized > 127) {quantized = 127;}

    return (int8_t)quantized;
}


float dequantize_int8_to_float(int8_t value, float scale, int32_t zero_point) {
    return ((float)value - (float)zero_point) * scale;
}
