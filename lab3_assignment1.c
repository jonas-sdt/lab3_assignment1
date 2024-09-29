#include "projects/lab3_assignment1/include/stopwatch.h"
#include "projects/lab3_assignment1/include/uart.h"
#define DEBUG_PRINTS

//*****************************************************************************
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "stopwatch.h"
#include "utils/uartstdio.h"

// #include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "driverlib/timer.h"

#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

// #include "driverlib/interrupt.h"
// #include "driverlib/pin_map.h"
// #include "inc/tm4c129encpdt.h"

//***********************************************************************
//                       Configurations
//***********************************************************************
// Configure the UART.

//*****************************************************************************
//                      Main
//*****************************************************************************
int main(void) {
  uint32_t systemClock;
  systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                    SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                   16000);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  // SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
  // SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM0);
  // SysCtlPeripheralReset(SYSCTL_PERIPH_PWM0);
  // SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

  GPIOPinConfigure(GPIO_PF2_M0PWM2);

  /* --------------------
   * Stopwatch Setup
   * -------------------- */

  stopwatch_init();

#ifdef DEBUG_PRINTS
  UARTprintf("Entering Main");
#endif

  while (1) {
    uint32_t hours = 0;
    uint32_t minutes = 0;
    uint32_t seconds = 0;

    // while nothing received wait
    while (true) {
      // break if start time is received
      if (ROM_UARTCharsAvail(UART0_BASE)) {
        getTimeInputUART(&hours, &minutes, &seconds);
        UARTprintf("Received Start\n");

        // TODO: check if time is valid

        break;
      }
    }

    // start stopwatch
    stopwatch_start(hours, minutes, seconds);

    while (true) {
      // break if "stop" is received
      if (ROM_UARTCharsAvail(UART0_BASE) && isStopReceived()) {
        UARTprintf("Stop\n");
        break;
      }
    }
  }
}
