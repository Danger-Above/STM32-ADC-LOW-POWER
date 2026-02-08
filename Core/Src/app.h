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

void app_init(ADC_HandleTypeDef *handle, UART_HandleTypeDef *huart);
void app_run(uint16_t measure_period);


#endif /* SRC_APP_H_ */
