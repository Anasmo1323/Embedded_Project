#ifndef STM32_TEMPLATE_LAB3_LCD_H
#define STM32_TEMPLATE_LAB3_LCD_H

#include "Std_Types.h"
#include "string.h"
#include "GPIO.h"
#include "Rcc.h"
#include <stdio.h>
#include <stdint.h>

#define LCD_PORT GPIO_E
#define LCD_RS 9  // PE9
#define LCD_E  8  // PE8
#define  OBJECT_COUNT (0x80 | 0x04)
#define MOTOR_SPEED (0x80 | 0x0C)
#define CONVEYOR_SPEED (0x80 | 0x44)
// #define EMERGENCY_STATUS (0x80 | 0x4C)

void LCD_Write(uint8 data, uint8 rs);
void LCD_Init(void);
void LCD_Print(const char* str);
void LCD_Update(uint8 to_be_updated, char* update);
void Delay_ms(int i);
void uint16_to_string(uint16 value, char *buffer);

#endif //STM32_TEMPLATE_LAB3_LCD_H
