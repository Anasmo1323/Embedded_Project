#include "Pwm.h"
#include "Gpio.h"
#include "Timer.h"
#include "Rcc.h"

void PWM_Init(void)
{
    Rcc_Init();
    // Enable TIM2 clock
    Rcc_Enable(RCC_TIM3);
    // Enable GPIOA clock
    Rcc_Enable(RCC_GPIOC);

    // Set PA5 as AF (Alternate Function) mode
    GPIO_SetAlternateFunction(GPIO_C, 6, 2);    // Set AF1 for PA5 (TIM2_CH1)

    // Get pointer to TIM2 registers using our TimerReg abstraction
    TimerReg* timer3 = (TimerReg*)TIM3_BASE;

    // Configure timer:
    timer3->PSC = 83;    // Set prescaler. (PSC value is prescaler - 1) Prescaler 40 (assuming 84MHz clock => 1MHz timer clock)
    timer3->ARR = 999;   // Auto-reload value for PWM period (1 kHz)

    timer3->CCR1 = 500;

    timer3->CCMR1 &= ~(0x7 << 4);           // Clear OC1M bits (bits 6:4)
    timer3->CCMR1 |= (6 << 4);              // Set OC1M to 110: PWM mode 1.
    timer3->CCMR1 |= (0x1 << 3);            // Enable preload for CCR1.

    /* Enable TIM2 Channel 1 output */
    timer3->CCER |= (0x1 << 0);

    /* Enable auto-reload preload */
    timer3->CR1 |= (0x1 << 7);

    /* Force an update event to load the registers */
    timer3->EGR |= (0x1 << 0);

    // Start the timer (set CEN in CR1)
    timer3->CR1 |= (0x1 << 0);
}
void PWM_SetDutyCycle(uint8 duty)
{
    if (duty > 100) duty = 100;
    // Update the compare register to adjust the PWM duty cycle:
    TimerReg* timer3 = (TimerReg*)TIM3_BASE;
    uint32 period = timer3->ARR;
    uint32 pulse = ((period + 1) * duty) / 100;
    timer3->CCR1 = pulse;
}
void PWM_Stop(void)
{
    // To stop PWM, simply set the compare value to 0.
    TimerReg* timer3 = (TimerReg*)TIM3_BASE;
    timer3->CCR1 = 0;
}