/*
 * app.h
 *
 *  Created on: Feb 8, 2026
 *      Author: Adam
 */

#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"
#include "adc.h"

void app_init(ADC_HandleTypeDef *handle, UART_HandleTypeDef *huart);
void app_restore_init_state(void);
adc_results_t app_run(void);


#endif /* SRC_APP_H_ */
