#include "stopwatch.h"
#include "projects/lab3_assignment1/include/uart.h"

void stopwatch_start(uint32_t hour, uint32_t minute, uint32_t sec) {

  TIME = stopwatch_calculate_time(hour, minute, sec);
  INIT_TIME = TIME;

  uint32_t hours = 0;
  uint32_t minutes = 0;
  uint32_t seconds = 0;
  stopwatch_get_time(&hours, &minutes, &seconds);
  UARTprintf("Stopwatch initialized to: ");
  printTimeUART(hours, minutes, seconds);
  STOPWATCH_RUNNING = true;
}

void stopwatch_init() {

  ConfigureUART();

  // Enable the Timer0 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  // Wait for the Timer0 module to be ready.
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {
  }

  // Configure TimerA as a half-width one-shot timer, and TimerB as a half-width
  // edge capture counter.
  TimerConfigure(TIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT |
                               TIMER_CFG_B_CAP_COUNT));

  // Set the count time for the the one-shot timer (TimerA).
  TimerLoadSet(TIMER0_BASE, TIMER_A, 3000);

  // Configure the counter (TimerB) to count both edges.
  TimerControlEvent(TIMER0_BASE, TIMER_B, TIMER_EVENT_BOTH_EDGES);

  // Enable the timers.
  TimerEnable(TIMER0_BASE, TIMER_B);

  // Enable Timer interrupts.
  IntRegister(INT_TIMER0B_TM4C129, Timer0IntHandler);
  TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

uint32_t stopwatch_calculate_time(uint32_t hour, uint32_t minute,
                                  uint32_t sec) {
  return sec + 60 * (minute + (60 * hour));
}

void stopwatch_get_time(uint32_t *hour, uint32_t *minute, uint32_t *sec) {
  *sec = TIME % 60;
  uint32_t minutes = (TIME - *sec) / 60;
  *minute = minutes % 60;
  *hour = (minutes - *minute) / 60;
}

void stopwatch_reset() { TIME = INIT_TIME; }
void stopwatch_stop() { STOPWATCH_RUNNING = false; }

void Timer0IntHandler(void) {
  UARTprintf("Timer0IntHandler\n");
  if (!STOPWATCH_RUNNING) {
    return;
  }

  TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
  TIME++;
  uint32_t hours = 0;
  uint32_t minutes = 0;
  uint32_t seconds = 0;
  stopwatch_get_time(&hours, &minutes, &seconds);
  clearLine();
  printTimeUART(hours, minutes, seconds);
}
