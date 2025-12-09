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
#define AXES_NUMBER 6


typedef struct {
	float acc_axis_1[WINDOW_SIZE];
	float acc_axis_2[WINDOW_SIZE];
	float acc_axis_3[WINDOW_SIZE];

	float gyro_axis_1[WINDOW_SIZE];
	float gyro_axis_2[WINDOW_SIZE];
	float gyro_axis_3[WINDOW_SIZE];

	uint8_t index;
} ringBufferIMU;


void pushSample(ringBufferIMU* buffer,
				const float acc_axis_1, const float acc_axis_2, const float acc_axis_3,
				const float gyro_axis_1, const float gyro_axis_2, const float gyro_axis_3
		);

void getWindow(ringBufferIMU* buffer, float outBuffer[WINDOW_SIZE*AXES_NUMBER]);



#endif /* INC_UTILS_IMU_BUFFER_H_ */
