#ifndef LAB§_ASSIGNMENT1_UART_H
#define LAB§_ASSIGNMENT1_UART_H

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"
#include <stdint.h>

void ConfigureUART(void);
void printTimeUART(uint32_t hours, uint32_t minutes, uint32_t seconds);
void clearLine();
void getTimeInputUART(uint32_t *hours, uint32_t *minutes, uint32_t *seconds);
bool isStopReceived();

#endif
