#ifndef HD44780_H
#define HD44780_H

#include "stm32l0xx_it.h" // Change this to your STM32 series
#include <stdint.h>

// Define LCD GPIO pins


/*
#define LCD_RS_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_EN_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_1
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_2
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_3
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_4
#define LCD_D7_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_5
*/

/*
// LCD Commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_DISPLAY_OFF 0x08
#define LCD_FUNCTION_SET 0x28 // 4-bit mode, 2 lines, 5x8 dots
*/



// Function Prototypes
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_Write4Bits(uint8_t value);
void LCD_PulseEnable();
void LCD_WriteChar(char data);

#endif