/*
 * LCD.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Mohamed Abdel Mageed
 */

#ifndef LCD_H_
#define LCD_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/***************************************************************************************************
 *                                      Preprocessor Macros
 ***************************************************************************************************/

/* LCD data bits mode congiguration */
#define DATA_BITS_MODE 8

/* use upper data bits in the data pins */
#if DATA_BITS_MODE == 4
#define UPPER_PORT_PIN
#endif


/* LCD HW Pins */
#define RS PD4
#define RW PD5
#define E  PD6

#define LCD_CTRL_PORT      PORTD
#define LCD_CTRL_PORT_DIR  DDRD

#define LCD_DATA_PORT      PORTC
#define LCD_DATA_PORT_DIR  DDRC

/* LCD Commands */
#define CLEAR_COMMAND                0x01  /* clear display */
#define FOUR_BITS_DATA_MODE          0x02  /* four data bits */
#define TWO_LINE_LCD_Four_BIT_MODE   0x28  /* 4-Bits, 2Line mode */
#define TWO_LINE_LCD_EIGHT_BIT_MODE  0x38  /* 2 line , 8-bits mode */
#define CURSOR_OFF 0x0C                    /* display off , cursor off */
#define CURSOR_ON  0x0E                    /* dispaly on  , cursor on  */
#define SET_CURSOR_LOCATION 0x80           /* force cursor to start from 1st line */

/**************************************************************************************************
 *                                      Functions Prototypes
 **************************************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharcter(uint8 character);
void LCD_displayString(const char* Str);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(const char* Str, uint8 row,uint8 col);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);



#endif /* LCD_H_ */
