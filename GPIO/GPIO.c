#include <Std_Types.h>
#include "Gpio.h"

 #define GPIO_REG(PORT_ID, REG_ID)       ((volatile uint32 *) ((PORT_ID) + (REG_ID)))

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState) {
    GpioReg* gpioReg = (GpioReg*) PortName;
    // ensure a valid pin number
    if (PinNumber > 15) return;
    // set pin mode
    gpioReg->GPIOx_MODER &= ~(0x03 << PinNumber * 2);
    gpioReg->GPIOx_MODER |= (PinMode << PinNumber * 2);
    // set pin type
    if (PinMode == GPIO_OUTPUT)
    {
        gpioReg->GPIOx_OTYPER &= ~(0x01 << PinNumber);
        gpioReg->GPIOx_OTYPER |= (DefaultState << PinNumber);
    }
    else if (PinMode == GPIO_INPUT)
    {
        gpioReg->GPIOx_PUPDR &= ~(0x03 << PinNumber * 2);
        gpioReg->GPIOx_PUPDR |= (DefaultState << PinNumber * 2);
    }

}

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data) {
    GpioReg* gpioReg = (GpioReg*) PortName;

    if (PinNumber > 15) return 0;
    // check if the pin is an output pin
    uint8 is_output = (gpioReg->GPIOx_MODER >> (PinNumber * 2)) & 0x03;
    if (is_output == 1){
        gpioReg->GPIOx_ODR &= ~(0x01 << PinNumber);
        gpioReg->GPIOx_ODR |= ((Data & 0x01) << PinNumber);
        return 1;
    }
    else return 0;
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber) {
    GpioReg* gpioReg = (GpioReg*) PortName;

    if (PinNumber > 15) return 0;
    // check if the pin is an input pin
    uint8 is_input = (gpioReg->GPIOx_MODER >> (PinNumber * 2)) & 0x03;
    if (is_input == 0){
        return (gpioReg->GPIOx_IDR >> PinNumber) & 0x01;
    }
    else return 0;
}

void GPIO_SetAlternateFunction(uint32 PortName, uint8 PinNumber, uint8 AF) {
    GpioReg* gpioReg = (GpioReg*)PortName;
    gpioReg->GPIOx_MODER &= ~(0x03 << PinNumber * 2);
    gpioReg->GPIOx_MODER |= (GPIO_AF << PinNumber * 2);
    if (PinNumber < 8) {
        gpioReg->GPIOx_AFRL &= ~(0xF << (PinNumber * 4));
        gpioReg->GPIOx_AFRL |= (AF << (PinNumber * 4));
    } else {
        gpioReg->GPIOx_AFRH &= ~(0xF << ((PinNumber - 8) * 4));
        gpioReg->GPIOx_AFRH |= (AF << ((PinNumber - 8) * 4));
    }
}
