#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Utils.h"
#include "Rcc.h"
#include "Rcc_Private.h"
#include "GPIO.h"
#include "LCD.h"

int main(void) {

    Rcc_Init();
    Rcc_Enable(RCC_GPIOE);
    for (uint8 i = 0; i <= 9; i++) {
        GPIO_Init(GPIO_E, i, GPIO_OUTPUT, GPIO_PUSH_PULL);
    }

    LCD_Init();

    Delay_ms(3000);
    LCD_Update(CONVEYOR_SPEED, "450");
    Delay_ms(1000);
    LCD_Update(MOTOR_SPEED, "45");
    Delay_ms(1000);
    LCD_Update(OBJECT_COUNT, "12");
    Delay_ms(1000);
    LCD_Update(EMERGENCY_STATUS, "ON");

    Delay_ms(3000);
    LCD_Update(CONVEYOR_SPEED, "33");
    Delay_ms(1000);
    LCD_Update(MOTOR_SPEED, "2");
    Delay_ms(1000);
    LCD_Update(OBJECT_COUNT, "100");
    Delay_ms(1000);
    LCD_Update(EMERGENCY_STATUS, "OFF");



    while (1) {
        return 0;
    }
}