/*
 * imu_data_normalization.h
 *
 *  Created on: Nov 26, 2025
 *      Author: bohdan
 */

#ifndef INC_IMU_DATA_NORMALIZATIO_H_
#define INC_IMU_DATA_NORMALIZATIO_H_


float convertMiliGToAcceleration(int valueMiliG);
float normalizeAccelerometerOutput(int accValue, float mean, float sd);

float convertMilidegreesToRadians(int valueMilidegrees);
float normalizeGyroscopeOutput(int gyroValue, float mean, float sd);


#endif /* INC_IMU_DATA_NORMALIZATIO_H_ */
