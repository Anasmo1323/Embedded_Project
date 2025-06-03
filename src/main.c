#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Utils.h"
#include "Rcc.h"
#include "Rcc_Private.h"
#include "GPIO.h"
#include "LCD.h"
#include "IR.h"

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



while (1) {
IR_ObjectCounter();
}
}