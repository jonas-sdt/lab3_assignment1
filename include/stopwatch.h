#ifndef lab3_assignment1_stopwatch_h
#define lab3_assignment1_stopwatch_h

#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "inc/hw_ints.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

static uint32_t TIME = 0;
static uint32_t INIT_TIME = 0;
static bool STOPWATCH_RUNNING = false;

void stopwatch_start(uint32_t hour, uint32_t minute, uint32_t sec);
void stopwatch_init();
void stopwatch_reset();
uint32_t stopwatch_calculate_time(uint32_t hour, uint32_t minute, uint32_t sec);
void stopwatch_get_time(uint32_t *hour, uint32_t *minute, uint32_t *sec);
void Timer0IntHandler(void);

#endif
