/*
 * app.c
 *
 *  Created on: Feb 8, 2026
 *      Author: Adam
 */
#include "stdio.h"
#include "logger.h"
#include "adc.h"


#define APP_ENABLE_LOG 1


static adc_results_t results = {0, 0, 0};
static adc_filter_ma_t filter = {{0}, 0, 0, 0};

static char string_buff[32];

void app_init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart)
{
	logger_init(huart);
	adc_init(hadc);
}

void app_run(uint16_t measure_period, uint32_t number)
{
	static uint32_t time = 0;

	adc_read_raw_blocking(&results);
	adc_filter_ma(&filter, &results);

	results.percent = adc_result_to_percent(results.filtered);

	if (APP_ENABLE_LOG)
	{
		time += measure_period;
		snprintf(string_buff, sizeof(string_buff), "%ld %04d %04d %u",
				time, results.raw, results.filtered, results.percent);

		logger_sendln(string_buff);
	}
}
