#include "GPIO.h"

    void GPIO_Init(uint8 PortName , uint8 PinNumber, uint8 PinMode, uint8 DefaultState)
    {
        switch (PortName) {
            case GPIO_A:
                // Initialize GPIOA
                GPIOA_MODER &= ~(0x03 << PinNumber * 2); // Clear the bits responsible for the mode of the PIN
                GPIOA_MODER |= (PinMode << PinNumber * 2); // Set the mode
                GPIOA_OTYPER &= ~(0x01 << PinNumber);
                // Clear the output type bit
                if (PinMode == GPIO_OUTPUT)
                {
                    GPIOA_OTYPER &= ~(0x01 << PinNumber); // Clear the output type bit
                    GPIOA_OTYPER |= (DefaultState << PinNumber); // Set the output type
                }
                else
                {
                    GPIOA_PUPDR &= ~(0x03 << PinNumber * 2);
                    GPIOA_PUPDR |= (DefaultState << PinNumber * 2);
                }
                break;
            case GPIO_B:
                GPIOB_MODER &= ~(0x03 << PinNumber * 2);
                GPIOB_MODER |= (PinMode << PinNumber * 2);
                GPIOB_OTYPER &= ~(0x01 << PinNumber);
                // Clear the output type bit
                if (PinMode == GPIO_OUTPUT)
                {
                GPIOB_OTYPER &= ~(0x01 << PinNumber);
                GPIOB_OTYPER |= (DefaultState << PinNumber);
                }
                else
                {
                GPIOB_PUPDR &= ~(0x03 << PinNumber * 2);
                GPIOB_PUPDR |= (DefaultState << PinNumber * 2);
                }

                break;
            case GPIO_C:
                break;
            case GPIO_D:
                break;
            case GPIO_E:
                GPIOE_MODER &= ~(0x03 << PinNumber * 2);
                GPIOE_MODER |= (PinMode << PinNumber * 2);
                GPIOE_OTYPER &= ~(0x01 << PinNumber);
                // Clear the output type bit
                if (PinMode == GPIO_OUTPUT)
                {
                    GPIOE_OTYPER &= ~(0x01 << PinNumber);
                    GPIOE_OTYPER |= (DefaultState << PinNumber);
                }
                else
                {
                    GPIOE_PUPDR &= ~(0x03 << PinNumber * 2);
                    GPIOE_PUPDR |= (DefaultState << PinNumber * 2);
                }
                break;
            default:
                break;
        }
    }

    void GPIO_WritePin(uint8 PortName , uint8 PinNumber, uint8 Data)
    {
        switch (PortName) {
            case GPIO_A:
                GPIOA_ODR &= ~(0x01 << PinNumber);
                GPIOA_ODR |= (Data << PinNumber);
                break;
            case GPIO_B:
                GPIOB_ODR &= ~(0x01 << PinNumber);
                GPIOB_ODR |= (Data << PinNumber);
                break;
            case GPIO_C:
                break;
            case GPIO_D:
                break;
            case GPIO_E:
                GPIOE_ODR &= ~(0x01 << PinNumber);
                GPIOE_ODR |= (Data << PinNumber);
                break;
            default:
                break;
        }
    }
    uint8 GPIO_ReadPin(uint8 PortName , uint8 PinNumber)
    {
        uint8 Data = 0;
        switch (PortName) {
            case GPIO_A:
                Data = (GPIOA_IDR >> PinNumber) & 0x01;
                break;
            case GPIO_B:
                Data = (GPIOB_IDR >> PinNumber) & 0x01;
                break;
            case GPIO_C:
                break;
            case GPIO_D:
                break;
            case GPIO_E:
                Data = (GPIOE_IDR >> PinNumber) & 0x01;
                break;
            default:
                break;
        }
        return Data;
    }
