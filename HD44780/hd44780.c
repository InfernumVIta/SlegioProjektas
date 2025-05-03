#include "hd44780.h"
#include "stm32l0xx_it.h"  // Adjust this for your STM32 series
#include "main.h"

// Define LCD GPIO pins (adjust based on your connections)




void LCD_Init() {
    HAL_Delay(50);  // Wait for LCD to power up

    // Set to 4-bit mode
    LCD_Write4Bits(0x03);
    HAL_Delay(5);
    LCD_Write4Bits(0x03);
    HAL_Delay(1);
    LCD_Write4Bits(0x03);
    LCD_Write4Bits(0x02); // Set to 4-bit mode

    // Configure display
    LCD_Command(0x28); // 4-bit, 2 lines, 5x8 font
    LCD_Command(0x0C); // Display ON, cursor OFF
    LCD_Command(0x06); // Entry mode: move right
    LCD_Command(0x01); // Clear display
    HAL_Delay(2);
}

void LCD_Command(uint8_t cmd) {
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET); // RS = 0 for command
    LCD_Write4Bits(cmd >> 4);
    LCD_Write4Bits(cmd);
    HAL_Delay(2);
}

void LCD_WriteChar(char ch) {
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET); // RS = 1 for data
    LCD_Write4Bits(ch >> 4);
    LCD_Write4Bits(ch);
}

void LCD_Print(char *str) {
    while (*str) {
        LCD_WriteChar(*str++);
    }
}

void LCD_Clear() {
    LCD_Command(0x01); // Clear display
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;
    LCD_Command(address);
}

void LCD_Write4Bits(uint8_t value) {
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (value & 0x1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (value & 0x2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (value & 0x4) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (value & 0x8) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_PulseEnable();
}

void LCD_PulseEnable() {
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}
