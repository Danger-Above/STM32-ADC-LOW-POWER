/*
 * app.c
 *
 *  Created on: Feb 8, 2026
 *      Author: Adam
 */
#include "stdio.h"
#include "logger.h"
#include "app.h"


#define APP_ENABLE_LOG 1

static adc_results_t results = {0, 0, 0};
static adc_filter_ma_t filter = {{0}, 0, 0, 0};

void app_init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart)
{
	logger_init(huart);
	adc_init(hadc);
}

void app_restore_init_state(void)
{
	results.raw = 0;
	results.filtered = 0;
	results.percent = 0;
	filter.filled = 0;
	filter.index = 0;
	filter.sum = 0;
	for (uint16_t i = 0; i < (sizeof(filter.window)/sizeof(filter.window[0])); ++i)
	{
		filter.window[i] = 0;
	}
}

adc_results_t app_run(void)
{
	adc_read_raw_blocking(&results);
	adc_filter_ma(&filter, &results);

	results.percent = adc_result_to_percent(results.filtered);

	return results;
}
