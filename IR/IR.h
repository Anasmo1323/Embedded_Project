#ifndef STM32_TEMPLATE_LAB3_IR_H
#define STM32_TEMPLATE_LAB3_IR_H

#include "Std_Types.h"
#include "GPIO.h"
#include "LCD.h"

#define IR_PORT GPIO_B
#define IR_PIN 0
#define MAX_COUNT 999

void IR_Init(void);
void IR_ObjectCounter(void);


#endif
