/*
 * prev_predictions_buffer.h
 *
 *  Created on: Dec 5, 2025
 *      Author: bohdan
 */

#ifndef INC_UTILS_PREV_PREDICTIONS_BUFFER_H_
#define INC_UTILS_PREV_PREDICTIONS_BUFFER_H_


#include <stdint.h>


#define NUMBER_OF_CLASSES 7
#define TRACKED_PREDICTIONS 6


typedef struct {
	uint8_t arr[TRACKED_PREDICTIONS];
	uint8_t freqClassCount[NUMBER_OF_CLASSES];
	uint8_t index;
} prevPredictionsBuffer;


void initPrevPredictionBuffer(prevPredictionsBuffer* buffer);
void pushPrediction(prevPredictionsBuffer* buffer, const uint8_t prediction);
uint8_t getClassFrequency(prevPredictionsBuffer* buffer, const uint8_t classIndex);


#endif /* INC_UTILS_PREV_PREDICTIONS_BUFFER_H_ */
