/*
 * adc.c
 *
 *  Created on: Jan 31, 2026
 *      Author: Adam
 */

#define ADC_CALIB_MAX_VAL 3960
#define ADC_CALIB_MIN_VAL 0

#include "adc.h"

static ADC_HandleTypeDef *adc_handle = NULL;

static uint8_t adc_clamp_percent(uint32_t value)
{
	if (value > 100)
	{
		value = 100;
	}
	else if (value < 0)
	{
		value = 0;
	}
	return value;
}

void adc_init(ADC_HandleTypeDef *adc)
{
	adc_handle = adc;
}

void adc_read_raw_blocking(adc_results_t *results)
{
	if (adc_handle == NULL) return;

	if (HAL_ADC_Start(adc_handle) != HAL_OK) return;

	if (HAL_ADC_PollForConversion(adc_handle, 10) != HAL_OK)
	{
			HAL_ADC_Stop(adc_handle);
			return;
	}

	results->raw = HAL_ADC_GetValue(adc_handle);
	HAL_ADC_Stop(adc_handle);
}

void adc_filter_ma(adc_filter_ma_t *filter, adc_results_t *results)
{
    if (filter->index >= ADC_FILTER_MA_WINDOW_SIZE)
    {
    	filter->index = 0;
    }

    if (filter->filled == ADC_FILTER_MA_WINDOW_SIZE)
    {
        filter->sum -= filter->window[filter->index];
    }

    filter->window[filter->index] = results->raw;
    filter->sum += results->raw;
    filter->index++;

    if (filter->filled < ADC_FILTER_MA_WINDOW_SIZE)
    {
    	filter->filled++;
    }

    results->filtered = (uint16_t)(filter->sum / filter->filled);
}

uint8_t adc_result_to_percent(uint16_t value)
{
	if ((ADC_CALIB_MAX_VAL - ADC_CALIB_MIN_VAL) == 0)
	{
		return 0;
	}

	uint32_t result = ((value - ADC_CALIB_MIN_VAL) * 100)/(ADC_CALIB_MAX_VAL - ADC_CALIB_MIN_VAL);

	return adc_clamp_percent(result);
}

