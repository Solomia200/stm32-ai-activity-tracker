/*
 * ring_imu_buffer.h
 *
 *  Created on: Dec 4, 2025
 *      Author: bohdan
 */

#ifndef INC_UTILS_RING_IMU_BUFFER_H_
#define INC_UTILS_RING_IMU_BUFFER_H_


#include <stdint.h>


#define WINDOW_SIZE 96
#define STRIDE 48


typedef struct {
	float axis_1[WINDOW_SIZE];
	float axis_2[WINDOW_SIZE];
	float axis_3[WINDOW_SIZE];
	uint8_t index;
} ringBufferIMU;


void pushSample(ringBufferIMU* buffer, const float x, const float y, const float z);
void getWindow(ringBufferIMU* buffer, float outBuffer[WINDOW_SIZE*3]);



#endif /* INC_UTILS_RING_IMU_BUFFER_H_ */
