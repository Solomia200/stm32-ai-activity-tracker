/*
 * utils.c
 *
 *  Created on: Dec 2, 2025
 *      Author: bohdan
 */


#include "utils/utils.h"


uint32_t argmax(const float * values, uint32_t len) {
  float max_value = values[0];

  uint32_t max_index = 0;

  for (uint32_t i = 1; i < len; i++) {
    if (values[i] > max_value) {
      max_value = values[i];
      max_index = i;
    }
  }

  return max_index;
}
