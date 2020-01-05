/*
 * i2c.c
 *
 *  Created on: Dec 29, 2019
 *      Author: Mohamed Abdel Mageed
 */
#include "i2c.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
void TWI_init (void)
{
	/*
	 * General Call Recognition: Off
	 * if any master device want to call me: 0x1 (used in case this MC is a slave device)
	 */
	TWCR = (1<<TWEN);    /* to enable the TWI */
	TWAR = 0b00000010;   /* slave address */

	/*
	 * Bit Rate: 400.000 kbps
	 * zero pre-scaler TWPS=00
	 * F_CPU=8Mhz
	 * TWPS(0:1)=00 (prescaler value=1) "no prescaling"
	 */
	TWBR = 0x02;
	TWSR = 0x00;
}

void TWI_start (void)
{
	/* Description:
	 * clear TWINT interrupt flag bit before sending the start bit
	 * send the start bit
	 * enable the TWI module
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (TWEN);

	/*
	 * wait until TWINT is set "start bit is sent successfully"
	 */
	while(BIT_IS_CLEAR(TWCR,TWINT))
	{

	}

}

void TWI_stop (void)
{
	/* Description:
	 * clear TWINT interrupt flag bit before sending the start bit TWINT=1
	 * send the stop bit TWSTO=1
	 * enable the TWI module TWEN=1
	 */
		TWCR = (1<<TWINT) | (1<<TWSTO) | (TWEN);
}

void TWI_write (uint8 data)
{
	/* put data in TWDR register */
	TWDR = data;

	/*
	 * clear TWINT interrupt flag bit before sending the data TWINT=1
	 * enable the TWI module TWEN=1
	 */
	TWCR = (1<<TWINT) | (TWEN);

	/*
	 * wait until data is sent successfully
	 */
	while(BIT_IS_CLEAR(TWCR,TWINT))
	{

	}
}

uint8 TWI_readWithACK (void)
{
	/*
		 * Clear the TWINT flag before reading the data TWINT=1
		 * Enable sending ACK after reading or receiving data TWEA=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	    while(BIT_IS_CLEAR(TWCR,TWINT));
	    /* Read Data */
	    return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
