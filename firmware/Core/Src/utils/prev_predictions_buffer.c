/*
 * prev_predictions_buffer.c
 *
 *  Created on: Dec 5, 2025
 *      Author: bohdan
 */


#include "prev_predictions_buffer.h"



void initPrevPredictionBuffer(prevPredictionsBuffer* buffer) {
    memset(buffer->arr, 0, sizeof(buffer->arr));
    memset(buffer->freqClassCount, 0, sizeof(buffer->freqClassCount));
    buffer->freqClassCount[0] = 6;
    buffer->index = 0;
}


void pushPrediction(prevPredictionsBuffer* buffer, const uint8_t prediction) {
	uint8_t curIndex = buffer->index;

	--buffer->freqClassCount[buffer->arr[curIndex]];
	++buffer->freqClassCount[prediction];

	buffer->arr[buffer->index] = prediction;

	++buffer->index;
	if (buffer->index >= TRACKED_PREDICTIONS) {
		buffer->index = 0;
	}
}


uint8_t getClassFrequency(prevPredictionsBuffer* buffer, const uint8_t classIndex) {
	return buffer->freqClassCount[classIndex];
}
