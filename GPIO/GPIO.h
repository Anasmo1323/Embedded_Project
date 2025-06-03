#include "Std_Types.h"
#ifndef STM32_TEMPLATE_LAB3_GPIO_H
#define STM32_TEMPLATE_LAB3_GPIO_H

/*PortName*/
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'
#define GPIO_E 'E'

/*PinMode*/
#define GPIO_INPUT 0x00
#define GPIO_OUTPUT 0x01
#define GPIO_ALTERNATE 0x02
#define GPIO_ANALOG 0x03

/*DefaultState*/ // Output Type
#define GPIO_PUSH_PULL 0x00
#define GPIO_OPEN_DRAIN 0x01

/*DefaultState*/ // Input Type
#define GPIO_NO_PULL 0x00
#define GPIO_PULL_UP 0x01
#define GPIO_PULL_DOWN 0x02

/*PinState*/
#define LOW 0x00
#define HIGH 0x01

void GPIO_Init(uint8 PortName , uint8 PinNumber, uint8 PinMode, uint8 DefaultState);
void GPIO_WritePin(uint8 PortName , uint8 PinNumber, uint8 Data);
uint8 GPIO_ReadPin(uint8 PortName , uint8 PinNumber);

#endif //STM32_TEMPLATE_LAB3_GPIO_H
