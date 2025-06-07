#include "LCD.h"


void LCD_Init(void) {
    Rcc_Enable(RCC_GPIOE);
    for (uint8 i = 0; i <= 9; i++) {
        Gpio_Init(GPIO_E, i, GPIO_OUTPUT, GPIO_PUSH_PULL);
    }

    LCD_Write(0x38, 0); // 8-bit, 2 lines, 5x8 font
    LCD_Write(0x0C, 0); // Display on, cursor off
    LCD_Write(0x06, 0); // Entry mode: increment cursor
    LCD_Write(0x01, 0); // Clear display
    Delay_ms(2);
    // This delay is necessary to give more time for the LCD to process the clear command
    //When I didn't use delay the first character got ignored because the clear wasn't done yet
    LCD_Write(0x80, LOW); // Set cursor to Line 1, position 1
    LCD_Print("CS: 0   MS: 0  %");
    LCD_Write(0xC0, LOW); // Set cursor to Line 2, position 1
    LCD_Print("OC: 0   ES: 0  ");
}

void LCD_Write(uint8 data, uint8 rs) {

    Gpio_WritePin(LCD_PORT, LCD_RS, rs);
    for (uint8 i = 0; i < 8; i++) {
        Gpio_WritePin(LCD_PORT, i, (data >> i) & 1);
    }

    // Pulse Enable (PE8)
    Gpio_WritePin(LCD_PORT, LCD_E, HIGH);
    Gpio_WritePin(LCD_PORT, LCD_E, LOW);
}

void LCD_Print(const char* str) {
    while (*str) { // Stops at the null terminator
        LCD_Write(*str, 1); //str here points to the first character in the string when we dereference it,
                                     // it gives the value in ASCII code, e.g. 'A' = 0x41
        str++;                       //Then we increment the pointer to point to the next character
    }
}


void LCD_Update(uint8 to_be_updated, char* update) {
    switch (to_be_updated) {
        case CONVEYOR_SPEED:
            LCD_Write(CONVEYOR_SPEED, 0);
            break;
        case MOTOR_SPEED:
            LCD_Write(MOTOR_SPEED, 0);
            break;
        case OBJECT_COUNT:
            LCD_Write(OBJECT_COUNT, 0);
            break;
        case EMERGENCY_STATUS:
            LCD_Write(EMERGENCY_STATUS, 0);
            break;
        default:
            return;

    }
    LCD_Print(update);
    for (int i = 0; i < 3 - strlen(update); i++) {
        LCD_Print(" ");
    }
}
void Delay_ms(int i) {
    for (int j = 0; j < 1200 * i; ++j) {
    }
}
void uint16_to_string(uint16 value, char *buffer) {
    snprintf(buffer, 4, "%u", value); // %u for unsigned int
}