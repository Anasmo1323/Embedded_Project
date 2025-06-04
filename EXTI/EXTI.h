#ifndef EXTI_H
#define EXTI_H
#include "Std_Types.h"
#include "RCC.h"
#include "stm32f4xx.h"
#include "GPIO.h"

typedef struct {
    uint32 IMR;
    uint32 EMR;
    uint32 RTSR;
    uint32 FTSR;
    uint32 SWIER;
    uint32 PR;
} EXTI_Type;

#define EXTI_b         ((EXTI_Type*)0x40013C00)

// GPIO ports
#define EXTI_PORT_A 0
#define EXTI_PORT_B 1
#define EXTI_PORT_C 2
#define EXTI_PORT_D 3
#define EXTI_PORT_E 4
#define EXTI_PORT_H 7

// edge trigger types
#define EXTI_RISING  0
#define EXTI_FALLING 1
#define EXTI_BOTH    2
//======================== NVIC ==========================

typedef struct {
    uint32  NVIC_ISER[8]; // 0x100 - 0x11C 
    uint32 RESERVED0[24];  // start at 0x11C + 0x04 = 0x120 , 0x180 - 0x 120 = 0x60==> dec(96 /  4 )
    uint32  NVIC_ICER[8]; // 0x180 - 0x19C

} NVIC_Type_;

#define NVIC_b          ((NVIC_Type_*)0xE000E100)


void EXTI_Init(uint8 port, uint8 line , uint8 trigger);
void EXTI_Enable(uint8 line);
void EXTI_Disable(uint8 line);
uint8 getVTPosition(uint8 line);
void EXTI_ClearPending(uint8 line);
void EXTI_Callout(void);
void EXTI_reset(void);

#endif /* EXTI_H */