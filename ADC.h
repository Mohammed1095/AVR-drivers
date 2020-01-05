/*
 * ADC.h
 *
 *  Created on: Nov 17, 2019
 *      Author: Mohamed Abdel Mageed
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/***************************************************************************************************
 *                                      Function prototypes
 **************************************************************************************************/

/* Description: Function responsible for initialize the ADC driver.
 * */
void ADC_init(void);

/* Description:Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 * */
void ADC_readChannel(uint8 channel);


#endif /* ADC_H_ */
