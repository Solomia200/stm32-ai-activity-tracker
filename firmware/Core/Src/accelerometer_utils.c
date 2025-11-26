/*
 * accelerometer_utils.c
 *
 *  Created on: Nov 26, 2025
 *      Author: bohdan
 */

#include "accelerometer_utils.h"


#define GRAVITATIONAL_ACCELERATION  9.80665


float normalizeAccelerometerOutput(int accValue, float mean, float sd) {
	float accelerationNormalized = ((accValue*GRAVITATIONAL_ACCELERATION / 1000) - mean) / sd;
	return accelerationNormalized;
}
