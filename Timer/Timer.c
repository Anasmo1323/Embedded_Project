#include "Timer.h"
#include "Rcc.h"
#include "Utils.h"

void Timer_Init(uint32 TimerBase, uint8 Channel, uint8 Mode, uint32 Prescaler, uint8 Edge) {
    TimerReg* timer = (TimerReg*)TimerBase;

    // Enable timer clock using RCC driver
    if (TimerBase == TIM2_BASE) Rcc_Enable(RCC_TIM2);
    else if (TimerBase == TIM3_BASE) Rcc_Enable(RCC_TIM3);
    else if (TimerBase == TIM4_BASE) Rcc_Enable(RCC_TIM4);
    else if (TimerBase == TIM5_BASE) Rcc_Enable(RCC_TIM5);
    else return; // Invalid timer

    // Validate channel (1–4)
    if (Channel < 1 || Channel > 4) return;

    // Set prescaler
    timer->PSC = Prescaler - 1; // Prescaler is 0-based

    // Configure input capture for the specified channel
    if (Mode == TIMER_INPUT_CAPTURE) {
        if (Channel == 1 || Channel == 2) {
            // CCMR1 handles channels 1 and 2
            uint8 shift = (Channel == 1) ? 0 : 8; // CC1S or CC2S
            timer->CCMR1 &= ~(0x03 << shift); // Clear CCxS
            timer->CCMR1 |= (0x01 << shift); // CCxS = 01 (map TIx)
        } else {
            // CCMR2 handles channels 3 and 4
            uint8 shift = (Channel == 3) ? 0 : 8; // CC3S or CC4S
            timer->CCMR2 &= ~(0x03 << shift);
            timer->CCMR2 |= (0x01 << shift);
        }

        // Set edge (rising or falling)
        uint8 shift = (Channel - 1) * 4; // CCxP bit position
        timer->CCER &= ~(1 << (shift + 1)); // Clear CCxP
        if (Edge == TIMER_FALLING_EDGE) {
            timer->CCER |= (1 << (shift + 1)); // CCxP = 1
        }

        // Enable capture
        timer->CCER |= (1 << shift); // CCxE = 1
    }

    // Enable timer
    timer->CR1 |= (1 << 0); // CEN = 1
}

uint8 Timer_CheckCapture(uint32 TimerBase, uint8 Channel, uint32* CaptureValue) {
    TimerReg* timer = (TimerReg*)TimerBase;

    // Validate channel
    if (Channel < 1 || Channel > 4) return 0;

    // Check capture flag
    uint8 flag_bit = Channel; // CCxIF (e.g., bit 1 for channel 1)
    if (timer->SR & (1 << flag_bit)) {
        // Read capture value
        switch (Channel) {
            case 1: *CaptureValue = timer->CCR1; break;
            case 2: *CaptureValue = timer->CCR2; break;
            case 3: *CaptureValue = timer->CCR3; break;
            case 4: *CaptureValue = timer->CCR4; break;
        }
        // Clear capture flag
        timer->SR &= ~(1 << flag_bit);
        return 1; // Capture occurred
    }
    return 0; // No capture
}