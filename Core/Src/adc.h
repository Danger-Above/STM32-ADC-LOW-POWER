/*
 * adc.h
 *
 *  Created on: Jan 31, 2026
 *      Author: Adam
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"

#define ADC_FILTER_MA_WINDOW_SIZE 8

typedef struct {
	uint16_t raw;
	uint16_t filtered;
	uint8_t percent;
} adc_results_t;

typedef struct {
	uint16_t window[ADC_FILTER_MA_WINDOW_SIZE];
	uint32_t sum;
	uint16_t index;
	uint16_t filled;
} adc_filter_ma_t;

void adc_init(ADC_HandleTypeDef *handle);
void adc_read_raw_blocking(adc_results_t *results);
void adc_filter_ma(adc_filter_ma_t *filter, adc_results_t *results);
uint8_t adc_result_to_percent(uint16_t value);

#endif /* SRC_ADC_H_ */
