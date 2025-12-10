/*
 * ring_imu_buffer.c
 *
 *  Created on: Dec 4, 2025
 *      Author: bohdan
 */


#include <imu_buffer.h>


void pushSample(ringBufferIMU* buffer, const int8_t x, const int8_t y, const int8_t z) {
	buffer->axis_1[buffer->index] = x;
	buffer->axis_2[buffer->index] = y;
	buffer->axis_3[buffer->index] = z;

	buffer->index++;
	if (buffer->index >= WINDOW_SIZE) {
		buffer->index = 0;
	}
}


void getWindow(ringBufferIMU* buffer, int8_t outBuffer[WINDOW_SIZE*3]) {
	uint8_t ringBufferPos = buffer->index;

	for (uint8_t i=0; i<WINDOW_SIZE; ++i) {
		outBuffer[3*i] = buffer->axis_1[ringBufferPos];
		outBuffer[3*i + 1] = buffer->axis_2[ringBufferPos];
		outBuffer[3*i + 2] = buffer->axis_3[ringBufferPos];

		ringBufferPos = (ringBufferPos + 1) % WINDOW_SIZE;
	}
}
