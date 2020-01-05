/*
 * LCD.c
 *
 *  Created on: Nov 14, 2019
 *      Author: Mohamed Abdel Mageed
 */
#include "LCD.h"

/**************************************************************************************************
 *                                       Functions Definitions
 **************************************************************************************************/
void LCD_init(void)
{
	/* set E,RW, RS as output pins */
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);

#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PIN
    LCD_DATA_PORT_DIR |= 0xF0;
#else
    LCD_DATA_PORT_DIR |= 0x0F;
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
#elif (DATA_BITS_MODE_8)
	LCD_DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

#if (DATA_BITS_MODE == 4)
  #ifdef UPPER_PORT_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
  #else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
  #endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);


#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F)<<4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

#elif(DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#endif
}

void LCD_displayCharacter(uint8 character)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

#if(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PIN
   LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character & 0xF0);
#else
   LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((character & 0xF0) >> 4);
#endif

    _delay_ms(1);
    CLEAR_BIT(LCD_CTRL_PORT,E);
    _delay_ms(1);
    SET_BIT(LCD_CTRL_PORT,E);
    _delay_ms(1);


#ifdef UPPER_PORT_PIN
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((character & 0x0F) <<4);
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (character & 0x0F);
#endif


                               /* LCD OFF */
            _delay_ms(1);
            CLEAR_BIT(LCD_CTRL_PORT,E);
            _delay_ms(1);


#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT = character;
    _delay_ms(1);
    CLEAR_BIT(LCD_CTRL_PORT,E);
    _delay_ms(1);
#endif
}

void LCD_displayString(const char* Str)
{
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
}

void LCD_goToRowColumn(uint8 row , uint8 col)
{
	uint8 Address;
	switch(row)
	{
	case 0:
		Address=col;
		break;
	case 1:
		Address=col+0x40;
		break;
	case 2:
		Address=col+0x50;
		break;
	case 3:
		Address=col+0x10;
		break;
	}
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(const char* Str, uint8 row, uint8 col)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}

void LCD_intgerToString(int data)
{
	char Str[16];
	itoa(data, Str, 10);
	LCD_displayString(Str);
}

void LCD_clearScreeen (void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}
