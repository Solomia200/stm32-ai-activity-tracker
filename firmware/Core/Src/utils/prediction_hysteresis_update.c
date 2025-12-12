/*
 * prediction_hysteresis_update.c
 *
 *  Created on: Dec 5, 2025
 *      Author: bohdan
 */


#define PREVIOUS_PREDICTIONS_COUNT_TRESHOLD 4
#define CONFIDENCE_TRESHOLD 0.75


#include "prediction_hysteresis_update.h"


uint8_t updatePredictionHysteresis(prevPredictionsBuffer* buffer,
									const uint8_t curPrediction,
									const uint8_t prevPrediction,
									const float curPredictionConfidence) {

	if (curPredictionConfidence >= CONFIDENCE_TRESHOLD) {
		return curPrediction;
	}

	uint8_t classFreq = getClassFrequency(buffer, curPrediction);

	if (classFreq >= PREVIOUS_PREDICTIONS_COUNT_TRESHOLD) {
		return curPrediction;
	}

	return prevPrediction;
}
