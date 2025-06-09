#ifndef TIMER_H
#define TIMER_H

#include "Std_Types.h"
#include "Rcc.h"
#include "Utils.h"

// Timer base addresses
#define TIM2_BASE 0x40000000
#define TIM3_BASE 0x40000400
#define TIM4_BASE 0x40000800
#define TIM5_BASE 0x40000C00

// Timer register structure
typedef struct {
    volatile uint32 CR1;        // Control register 1
    volatile uint32 CR2;        // Control register 2
    volatile uint32 SMCR;       // Slave mode control register
    volatile uint32 DIER;       // DMA/Interrupt enable register
    volatile uint32 SR;         // Status register
    volatile uint32 EGR;        // Event generation register
    volatile uint32 CCMR1;      // Capture/compare mode register 1
    volatile uint32 CCMR2;      // Capture/compare mode register 2
    volatile uint32 CCER;       // Capture/compare enable register
    volatile uint32 CNT;        // Counter
    volatile uint32 PSC;        // Prescaler
    volatile uint32 ARR;        // Auto-reload register
    volatile uint32 reserved1;   // Reserved
    volatile uint32 CCR1;       // Capture/compare register 1
    volatile uint32 CCR2;       // Capture/compare register 2
    volatile uint32 CCR3;       // Capture/compare register 3
    volatile uint32 CCR4;       // Capture/compare register 4
} TimerReg;

// Timer modes
#define TIMER_INPUT_CAPTURE 0x01

// Capture edge
#define TIMER_RISING_EDGE 0x00
#define TIMER_FALLING_EDGE 0x01

// Function prototypes
void Timer_Init(uint32 TimerBase, uint8 Channel, uint8 Mode, uint32 Prescaler, uint8 Edge);
uint8 Timer_CheckCapture(uint32 TimerBase, uint8 Channel, uint16* CaptureValue);
uint32 Timer_GetCounter(uint32 timer_base);

#endif /* TIMER_H */