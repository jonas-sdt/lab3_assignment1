#include "uart.h"
#include "uartstdio.h"

void ConfigureUART(void) {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
  UARTStdioConfig(0, 9600, 16000000);
}

void printTimeUART(uint32_t hours, uint32_t minutes, uint32_t seconds) {
  int hours0 = hours % 10;
  int hours1 = (hours - hours0) / 10;
  int minutes0 = minutes % 10;
  int minutes1 = (minutes - minutes0) / 10;
  int seconds0 = seconds % 10;
  int seconds1 = (seconds - seconds0) / 10;
  UARTprintf("%c%c:%c%c:%c%c", hours1 + '0', hours0 + '0', minutes1 + '0',
             minutes0 + '0', seconds1 + '0', seconds0 + '0');
}

void clearLine() { UARTprintf("\r"); }

void getTimeInputUART(uint32_t *hours, uint32_t *minutes, uint32_t *seconds) {
  char input[9];
  UARTgets(input, 9);
  // hh:mm:ss
  // 01:34:67
  *hours = (input[0] - '0') * 10 + input[1] - '0';
  *minutes = (input[3] - '0') * 10 + input[4] - '0';
  *seconds = (input[6] - '0') * 10 + input[7] - '0';
}

bool isStopReceived() {
  char input[5];
  UARTgets(input, 5);
  if (input[0] == 's' && input[1] == 't' && input[2] == 'o' &&
      input[3] == 'p') {
    return true;
  }
  return false;
}
