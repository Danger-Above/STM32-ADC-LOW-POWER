/*
 * adc.c
 *
 *  Created on: Jan 31, 2026
 *      Author: Adam
 */

#include "adc.h"

static ADC_HandleTypeDef *adc_handle = NULL;

void adc_init(ADC_HandleTypeDef *adc)
{
	adc_handle = adc;
}

void adc_read_raw_blocking(adc_results_t *results)
{
	if (adc_handle == NULL) return;

	  HAL_ADC_Start(adc_handle);
	  HAL_ADC_PollForConversion(adc_handle, HAL_MAX_DELAY);
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


