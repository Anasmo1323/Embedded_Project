#include "Pwm.h"
#include "stm32f4xx.h"
#include "Gpio.h"

void PWM_Init(void)
{
    // Set PA5 as AF (Alternate Function) mode
    Gpio_Init(GPIO_A, 5, GPIO_AF, GPIO_PUSH_PULL);

    // Set AF1 for PA5 (TIM2_CH1)
    GPIOA->AFR[0] &= ~(0xF << (5 * 4));
    GPIOA->AFR[0] |= (1 << (5 * 4));

    TIM2->PSC = 39;
    // Prescaler 40 (assuming 168MHz clock => 4.2MHz timer clock)
    TIM2->ARR = 100;   // PWM frequency (e.g., ~42kHz)
    TIM2->CCR1 = 0;
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
    TIM2->CCER |= TIM_CCER_CC1E;  // Enable output for channel 1
    TIM2->CR1 |= TIM_CR1_CEN; // Enable timer
}
void PWM_SetDutyCycle(uint8 duty)
{
    if (duty > 100) duty = 100;
    TIM2->CCR1 = duty;  // duty cycle 0-100%
}
void PWM_Stop(void)
{
    TIM2->CCR1 = 0;
}