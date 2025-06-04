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


uint8 emergency_flag = 0;
int main(void) {

    Rcc_Init();
    LCD_Init();
    IR_Init();

//    Delay_ms(3000);
//    LCD_Update(CONVEYOR_SPEED, "450");
//    Delay_ms(1000);
//    LCD_Update(MOTOR_SPEED, "45");
//    Delay_ms(1000);
//    LCD_Update(OBJECT_COUNT, "12");
//    Delay_ms(1000);
//    LCD_Update(EMERGENCY_STATUS, "ON");
//
//    Delay_ms(3000);
//    LCD_Update(CONVEYOR_SPEED, "33");
//    Delay_ms(1000);
//    LCD_Update(MOTOR_SPEED, "2");
//    Delay_ms(1000);
//    LCD_Update(OBJECT_COUNT, "100");
//    Delay_ms(1000);
//    LCD_Update(EMERGENCY_STATUS, "OFF");

//____________________________________
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_SYSCFG);

    EXTI_Init( EXTI_PORT_A, 4, EXTI_FALLING);
    EXTI_Init(EXTI_PORT_B, 10, EXTI_FALLING);
    EXTI_Enable(4);
    EXTI_Enable(10);
    //____________________________________


while (1) {
    if(!emergency_flag) {
            IR_ObjectCounter();
    }else{
        // do nothing => emergency 
    }
}
}

void EXTI_Callout(void) {
    emergency_flag = 1;
    LCD_Write(0x01, 0); // Clear display
    Delay_ms(2); 
    LCD_Write(0x80, 0); // line 1 
    LCD_Print("EMERGENCY STOP");
    LCD_Write(0xC0, 0); // line 2
    LCD_Print("Press to reset");
}

void EXTI_reset(void) {
    NVIC_SystemReset();
}
    