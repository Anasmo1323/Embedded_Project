#include "Std_Types.h"
#include "Utils.h"


#ifndef STM32_TEMPLATE_LAB3_GPIO_H
#define STM32_TEMPLATE_LAB3_GPIO_H

/*PortName*/
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'
#define GPIO_E 'E'

//GPIOA
#define GPIOA_BASE_ADDRESS 0x40020000
#define GPIOA_MODER        REG32(GPIOA_BASE_ADDRESS + 0x00)
#define GPIOA_OTYPER       REG32(GPIOA_BASE_ADDRESS + 0x04)
#define GPIOA_OSPEEDR      REG32(GPIOA_BASE_ADDRESS + 0x08)
#define GPIOA_PUPDR        REG32(GPIOA_BASE_ADDRESS + 0x0C)
#define GPIOA_IDR          REG32(GPIOA_BASE_ADDRESS + 0x10)
#define GPIOA_ODR          REG32(GPIOA_BASE_ADDRESS + 0x14)
#define GPIOA_BSRR         REG32(GPIOA_BASE_ADDRESS + 0x18)
#define GPIOA_LCKR         REG32(GPIOA_BASE_ADDRESS + 0x1C)
#define GPIOA_AFRL         REG32(GPIOA_BASE_ADDRESS + 0x20)
#define GPIOA_AFRH         REG32(GPIOA_BASE_ADDRESS + 0x24)

//GPIOB
#define GPIOB_BASE_ADDRESS 0x40020400
#define GPIOB_MODER        REG32(GPIOB_BASE_ADDRESS + 0x00)
#define GPIOB_OTYPER       REG32(GPIOB_BASE_ADDRESS + 0x04)
#define GPIOB_OSPEEDR      REG32(GPIOB_BASE_ADDRESS + 0x08)
#define GPIOB_PUPDR        REG32(GPIOB_BASE_ADDRESS + 0x0C)
#define GPIOB_IDR          REG32(GPIOB_BASE_ADDRESS + 0x10)
#define GPIOB_ODR          REG32(GPIOB_BASE_ADDRESS + 0x14)
#define GPIOB_BSRR         REG32(GPIOB_BASE_ADDRESS + 0x18)
#define GPIOB_LCKR         REG32(GPIOB_BASE_ADDRESS + 0x1C)
#define GPIOB_AFRL         REG32(GPIOB_BASE_ADDRESS + 0x20)
#define GPIOB_AFRH         REG32(GPIOB_BASE_ADDRESS + 0x24)
//GPIOE
#define GPIOE_BASE_ADDRESS 0x40021000
#define GPIOE_MODER        REG32(GPIOE_BASE_ADDRESS + 0x00)
#define GPIOE_OTYPER       REG32(GPIOE_BASE_ADDRESS + 0x04)
#define GPIOE_OSPEEDR      REG32(GPIOE_BASE_ADDRESS + 0x08)
#define GPIOE_PUPDR        REG32(GPIOE_BASE_ADDRESS + 0x0C)
#define GPIOE_IDR          REG32(GPIOE_BASE_ADDRESS + 0x10)
#define GPIOE_ODR          REG32(GPIOE_BASE_ADDRESS + 0x14)
#define GPIOE_BSRR         REG32(GPIOE_BASE_ADDRESS + 0x18)
#define GPIOE_LCKR         REG32(GPIOE_BASE_ADDRESS + 0x1C)

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
