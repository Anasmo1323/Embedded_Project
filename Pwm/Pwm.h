#ifndef PWM_H
#define PWM_H
#include "Std_Types.h"
#include "Gpio.h"
#include "Timer.h"
#include "Rcc.h"

void PWM_Init(void);
void PWM_SetDutyCycle(uint8 duty);
void PWM_Stop(void);

#endif //PWM_H
