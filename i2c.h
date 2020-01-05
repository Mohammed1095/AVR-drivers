/*
 * i2c.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Mohamed Abdel Mageed
 */

#ifndef I2C_H_
#define I2C_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // 0000 1000 start has been sent
#define TW_REP_START     0x10 // 0001 0000 repeated start
#define TW_MT_SLA_W_ACK  0x18 // 0001 1000 Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // 0000 0100 Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // 0010 1000 Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // 0101 0000 Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // 0101 1000 Master received data but doesn't send ACK to slave




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init (void);

void TWI_start (void);

void TWI_stop (void);

void TWI_write (uint8 data);

uint8 TWI_readWithACK(void);

uint8 TWI_readWithNACK(void);

uint8 TWI_getStatus (void);





#endif /* I2C_H_ */
