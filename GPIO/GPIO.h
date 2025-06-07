#ifndef GPIO_H
#define GPIO_H

#include "Std_Types.h"

// define ports base addresses
#define GPIO_A 0x40020000
#define GPIO_B 0x40020400
#define GPIO_C 0x40020800
#define GPIO_D 0x40020C00

typedef struct
{
    /* data */
    volatile uint32 GPIOx_MODER;
    volatile uint32 GPIOx_OTYPER;
    volatile uint32 GPIOx_OSPEEDR;
    volatile uint32 GPIOx_PUPDR;
    volatile uint32 GPIOx_IDR;
    volatile uint32 GPIOx_ODR;
    volatile uint32 GPIOx_BSRR;
    volatile uint32 GPIOx_LCKR;
    volatile uint32 GPIOx_AFRL;
    volatile uint32 GPIOx_AFRH;
} GpioReg;

//PinMode
#define GPIO_INPUT  0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF     0x02
#define GPIO_ANALOG 0x03

// DefaultState
#define GPIO_PUSH_PULL  0x00
#define GPIO_OPEN_DRAIN 0x01

#define GPIO_NO_PULL_DOWN 0x00
#define GPIO_PULL_UP      0x01
#define GPIO_PULL_DOWN    0x02

// Data
#define LOW      0x0
#define HIGH     0x1


#define OK  0x0
#define NOK 0x1


void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState);

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data);

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber);

void GPIO_SetAlternateFunction(uint32 PortName, uint8 PinNumber, uint8 AF);

#endif //GPIO_H
