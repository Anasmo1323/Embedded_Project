#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Utils.h"
#include "Rcc.h"
#include "Rcc_Private.h"
#include "GPIO.h"
#include "LCD.h"
#include "IR.h"
#include "EXTI.h"
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "Adc.h"
#include "Pwm.h"
#include "Timer.h"

#define MAX_TIMER_COUNT 0xFFFF

float measure_conveyor_speed(void);
float conveyor_speed;

volatile uint8 emergency_flag = 0;
int main(void)
{
    uint16 motor_percent = 0;
    uint16 adc_value = 0;

    Rcc_Init();
    LCD_Init();
    IR_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_SYSCFG);
    EXTI_Init(EXTI_PORT_A, 4, EXTI_FALLING);
    EXTI_Init(EXTI_PORT_B, 10, EXTI_FALLING);
    EXTI_Enable(4);
    EXTI_Enable(10);
    //____________________________________
    Rcc_Enable(RCC_ADC1);
    Rcc_Enable(RCC_TIM2);

    ADC_Init();
    PWM_Init();

    while (1)
    {
        if (!emergency_flag)
        {
            // IR
            IR_ObjectCounter();
            // ADC
            adc_value = ADC_Read();
            motor_percent = ((uint32)adc_value * 100) / 4095;
            PWM_SetDutyCycle(motor_percent);
            char motor_str[2];
            uint16_to_string(motor_percent, motor_str);
            __disable_irq(); // handlin race condition
            LCD_Update(MOTOR_SPEED, motor_str);
            __enable_irq();
        }
        else
        {
            // do nothing => emergency
        }
    }
}
// EXTI

void EXTI_Callout(void)
{
    // emergency
    emergency_flag = 1;
    PWM_SetDutyCycle(0); // Stop the motor
    LCD_Write(0x01, 0);  // Clear display
    Delay_ms(10);
    LCD_Write(0x80, 0); // line 1
    LCD_Print("EMERGENCY STOP");
    LCD_Write(0xC0, 0); // line 2
    LCD_Print("Press to reset");
}

void EXTI_reset(void)
{
    NVIC_SystemReset();
}

float measure_conveyor_speed(void)
{
    uint32 first_capture = 0;
    uint32 second_capture = 0;
    uint32 difference;
    float frequency;

    uint16 prev_cnt = 0;
    uint16 current_cnt = 0;
    uint32 overflow_count = 0;

    // Wait for first capture
    while (!Timer_CheckCapture(TIM2_BASE, 1, &first_capture))
    {
        // Do nothing
    }

    prev_cnt = Timer_GetCounter(TIM2_BASE); // You'll need to implement this wrapper

    // Wait for second capture
    while (!Timer_CheckCapture(TIM2_BASE, 1, &second_capture))
    {
        current_cnt = Timer_GetCounter(TIM2_BASE);
        if (current_cnt < prev_cnt)
        {
            overflow_count++;
        }
        prev_cnt = current_cnt;
    }

    // Total difference with overflows accounted
    if (second_capture >= first_capture)
    {
        difference = (overflow_count * (MAX_TIMER_COUNT + 1)) + (second_capture - first_capture);
    }
    else
    {
        difference = (overflow_count * (MAX_TIMER_COUNT + 1)) + ((MAX_TIMER_COUNT - first_capture + 1) + second_capture);
    }

    frequency = 1e6 / difference;

    return frequency;
}
