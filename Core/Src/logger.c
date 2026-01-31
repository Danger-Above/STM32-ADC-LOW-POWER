/*
 * cli.c
 *
 *  Created on: Nov 27, 2025
 *      Author: Adam
 */

#include "string.h"

#include "logger.h"

static UART_HandleTypeDef *logger_huart = NULL;

static void logger_send(const char *s)
{
	if (logger_huart == NULL) return;

	HAL_UART_Transmit(logger_huart, (uint8_t *)s, strlen(s), 100);
}

void logger_sendln(const char *s)
{
	logger_send(s);
	logger_send("\r\n");
}

void logger_init(UART_HandleTypeDef *huart)
{
    logger_huart = huart;

    logger_sendln("");
    logger_sendln("=== Logger for ADC ===");
    logger_sendln("");
}

void logger_csv_init(const char *s)
{
	logger_sendln("");
}

void logger_csv_send(uint32_t time, uint16_t val)
{

}
