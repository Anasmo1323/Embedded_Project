#include "IR.h"


uint8 static pin_state = HIGH;
uint8 static last_pin_state = HIGH;
uint16 static object_count = 0;
static char count_str[4] = {0};

void IR_Init(void) {
    Rcc_Enable(RCC_GPIOB);
    GPIO_Init(IR_PORT, IR_PIN, GPIO_INPUT, GPIO_PULL_DOWN);
}

void IR_ObjectCounter(void) {
    pin_state = GPIO_ReadPin(IR_PORT, IR_PIN);

    if (last_pin_state == HIGH && pin_state == LOW && object_count < MAX_COUNT) {
                object_count++;
                uint16_to_string(object_count, count_str);
                LCD_Update(OBJECT_COUNT, count_str);

        }
    last_pin_state = pin_state;
}

