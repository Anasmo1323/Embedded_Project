#include "EXTI.h"


void EXTI_Init(uint8 port,uint8 line,  uint8 trigger) {

    Gpio_Init(port, line, GPIO_INPUT, GPIO_PULL_UP);

    // Enable SYSCFG clock
    Rcc_Enable(RCC_SYSCFG);
    
    // SYSCFG_EXTICR1[0] controls  EXTI x configuration (x = 0 to 3)
    // SYSCFG_EXTICR2[1] controls  EXTI x configuration (x = 4 to 7)
    // SYSCFG_EXTICR3[2] controls  EXTI x configuration (x = 8 to 11)
    // SYSCFG_EXTICR4[3] controls  EXTI x configuration (x = 12 to 15)
    uint8 reg_index = line / 4;

    // lines 0,4,8,12   bit position 0
    // lines 1,5,9,13   bit position 4
    // lines 2,6,10,14  bit position 8
    // lines 3,7,11,15  bit position 12
    uint8 bitPos;
    bitPos = (line % 4) * 4;
    
    // Connect port to EXTI line
    SYSCFG->EXTICR[reg_index] &= ~(0xF << bitPos);
    SYSCFG->EXTICR[reg_index] |= (port << bitPos);

    // tigger type
    if (trigger == EXTI_RISING || trigger == EXTI_BOTH) {
        EXTI_b->RTSR |= (1 << line); // enable rising edge for input line
    } else {
        EXTI_b->RTSR &= ~(1 << line);
    }
    
    if (trigger == EXTI_FALLING || trigger == EXTI_BOTH) {
        EXTI_b->FTSR |= (1 << line);
    } else {
        EXTI_b->FTSR &= ~(1 << line);
    }

}

void EXTI_Enable(uint8 line) {
    // enable interupt in interupt mask register
    EXTI_b->IMR |= (1 << line); 
    //================================ enable from NVIC
    
    uint8 position = getVTPosition(line);
    NVIC_b->NVIC_ISER[position / 32] |= (1 << (position % 32)); 

}
void EXTI_Disable(uint8 line) {
    EXTI_b->IMR &= ~(1 << line); // disable interrupt for the line

    //================================ disable from NVIC
    // from vector table
    uint8 position = getVTPosition(line);

    NVIC_b->NVIC_ICER[position / 32] |= (1 << (position % 32));
}   

uint8 getVTPosition(uint8 line) {
    uint8 position;
    if (line <= 4) {
        position = 6 + line;  // EXTI0 => 6, EXTI1 => 7, ..., EXTI4 => 10
    } else if (line <= 9) {
        position = 23;        // EXTI 5-9 => 23
    } else if(line <= 15) {
        position = 40;        // EXTI 10-15 => 40
    }
    return position;
}
 void EXTI4_IRQHandler() {
    if (EXTI_b->PR & (1 << 4)) {   
        EXTI_Callout();
        EXTI_b->PR |= (1 << 4); 
    }
}

 void EXTI15_10_IRQHandler() {
    if (EXTI_b->PR & (1 << 10)) {  
        EXTI_reset();
        EXTI_b->PR |= (1 << 10);  
    }
}

