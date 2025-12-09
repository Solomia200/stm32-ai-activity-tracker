/*
 * imu_data_normalization.c
 *
 *  Created on: Nov 26, 2025
 *      Author: bohdan
 */

#include "utils/imu_data_normalization.h"


#define GRAVITATIONAL_ACCELERATION  9.80665f
#define PI 3.14159f


float convertMiliGToAcceleration(int valueMiliG) {
	return valueMiliG*GRAVITATIONAL_ACCELERATION / 1000;
}


float normalizeAccelerometerOutput(int accValue, float mean, float sd) {
	return (convertMiliGToAcceleration(accValue) - mean) / sd;
}


float convertMilidegreesToRadians(int valueMilidegrees) {
	return (valueMilidegrees) * (PI / 180000);
}


float normalizeGyroscopeOutput(int gyroValue, float mean, float sd) {
	return (convertMilidegreesToRadians(gyroValue) - mean) / sd;
}
