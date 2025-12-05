/*
 * prediction_hysteresis_update.h
 *
 *  Created on: Dec 5, 2025
 *      Author: bohdan
 */

#ifndef INC_UTILS_PREDICTION_HYSTERESIS_UPDATE_H_
#define INC_UTILS_PREDICTION_HYSTERESIS_UPDATE_H_


#include <stdint.h>
#include "prev_predictions_buffer.h"


uint8_t updatePredictionHysteresis(prevPredictionsBuffer* buffer,
									const uint8_t curPrediction,
									const uint8_t prevPrediction,
									const float curPredictionConfidence);

#endif /* INC_UTILS_PREDICTION_HYSTERESIS_UPDATE_H_ */
