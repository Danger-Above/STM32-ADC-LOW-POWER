/*
 * cli.h
 *
 *  Created on: Nov 27, 2025
 *      Author: Adam
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"

void logger_sendln(const char *s);

void logger_init(UART_HandleTypeDef *huart);

#endif /* SRC_LOGGER_H_ */
