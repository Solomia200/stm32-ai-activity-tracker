/*
 * ring_imu_buffer.c
 *
 *  Created on: Dec 4, 2025
 *      Author: bohdan
 */


#include <imu_buffer.h>


void pushSample(ringBufferIMU* buffer,
				const float acc_axis_1, const float acc_axis_2, const float acc_axis_3,
				const float gyro_axis_1, const float gyro_axis_2, const float gyro_axis_3
		) {
	buffer->acc_axis_1[buffer->index] = acc_axis_1;
	buffer->acc_axis_2[buffer->index] = acc_axis_2;
	buffer->acc_axis_3[buffer->index] = acc_axis_3;

	buffer->gyro_axis_1[buffer->index] = gyro_axis_1;
	buffer->gyro_axis_2[buffer->index] = gyro_axis_2;
	buffer->gyro_axis_3[buffer->index] = gyro_axis_3;

	buffer->index++;
	if (buffer->index >= WINDOW_SIZE) {
		buffer->index = 0;
	}
}


void getWindow(ringBufferIMU* buffer, float outBuffer[WINDOW_SIZE*AXES_NUMBER]) {
	uint8_t ringBufferPos = buffer->index;

	for (uint8_t i=0; i<WINDOW_SIZE; ++i) {
		outBuffer[AXES_NUMBER*i] = buffer->acc_axis_1[ringBufferPos];
		outBuffer[AXES_NUMBER*i + 1] = buffer->acc_axis_2[ringBufferPos];
		outBuffer[AXES_NUMBER*i + 2] = buffer->acc_axis_3[ringBufferPos];

		outBuffer[AXES_NUMBER*i + 3] = buffer->gyro_axis_1[ringBufferPos];
		outBuffer[AXES_NUMBER*i + 4] = buffer->gyro_axis_2[ringBufferPos];
		outBuffer[AXES_NUMBER*i + 5] = buffer->gyro_axis_3[ringBufferPos];

		ringBufferPos = (ringBufferPos + 1) % WINDOW_SIZE;
	}
}
