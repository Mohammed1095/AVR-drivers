/*
 * ADC.c
 *
 *  Created on: Nov 17, 2019
 *      Author: Mohamed Abdel Mageed
 */

#include "ADC.h"

/***************************************************************************************************
 *                                    Global variable
 **************************************************************************************************/

volatile uint16 g_adcResult = 0;


/**************************************************************************************************
 *                                    ISR's Definition
 **************************************************************************************************/
ISR(ADC_vect)
{
	g_adcResult = ADC;
}


/***************************************************************************************************
 *                                    Functions Definitions
 **************************************************************************************************/
void ADC_init(void)
{
	ADMUX = 0;
	/* ADMUX confguration
	 * 1. REFS0:1=0 to choose to connect external reference voltage by input this voltage
	 * through AREF pin & internal Vref is turned off.
	 * 2. ADLAR=0 to select result is right adjusted.
	 * 3. MUX4:0 = 00000 to choose ADC0.
	*/
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);
	/* ADCSRA configuration
	 * 1. ADEN=1 to enable the ADC.
	 * 2. ADPS0:1= 1 to choose ADC_Clock = F_CPU/8.
	 * 3. ADIE=1 to enable module interrupt.
	 */
}

void ADC_readChannel(uint8 channel)
{
	channel &= 0x07;      /* as channel number 000 to 111 */

	ADMUX &= 0xE0;        /* to clear MUX4:0 in the ADMUX to set the required channel */

	ADMUX |= channel;     /* choose the required channel */

	SET_BIT(ADCSRA,ADSC); /* set bit ADSC to start conversion */
}
