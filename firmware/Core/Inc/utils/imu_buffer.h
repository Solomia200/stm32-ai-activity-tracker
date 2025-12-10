/*
 * ring_imu_buffer.h
 *
 *  Created on: Dec 4, 2025
 *      Author: bohdan
 */

#ifndef INC_UTILS_IMU_BUFFER_H_
#define INC_UTILS_IMU_BUFFER_H_


#include <stdint.h>


#define WINDOW_SIZE 96
#define STRIDE 48


typedef struct {
	int8_t axis_1[WINDOW_SIZE];
	int8_t axis_2[WINDOW_SIZE];
	int8_t axis_3[WINDOW_SIZE];
	uint8_t index;
} ringBufferIMU;


void pushSample(ringBufferIMU* buffer, const int8_t x, const int8_t y, const int8_t z);
void getWindow(ringBufferIMU* buffer, int8_t outBuffer[WINDOW_SIZE*3]);



#endif /* INC_UTILS_IMU_BUFFER_H_ */
