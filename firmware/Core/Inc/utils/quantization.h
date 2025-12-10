/*
 * quantization.h
 *
 *  Created on: Dec 10, 2025
 *      Author: bohdan
 */

#ifndef INC_UTILS_QUANTIZATION_H_
#define INC_UTILS_QUANTIZATION_H_


#include <stdint.h>


int8_t quantize_float_to_int8(float value, float scale, int32_t zero_point);
float dequantize_int8_to_float(int8_t value, float scale, int32_t zero_point);

#endif /* INC_UTILS_QUANTIZATION_H_ */
