/*
 * ps2.h
 *
 *  Created on: Jun 22, 2022
 *      Author: Johnny Palumbo
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <msp.h>

/******************************************************************************
 * Student Defined ADC14 Macros
 *****************************************************************************/

/******************************************************************************
 * Student Defined ADC14 Extern Global Variables
 *****************************************************************************/
extern volatile uint32_t PS2_X_DIR; //x direction
extern volatile uint32_t PS2_Y_DIR; // y direction
extern volatile bool delay;
/******************************************************************************
 * ADC14 Initialization Function
 *
 * Define a function that will be called to initialize the ADC14 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void ece353_ADC14_PS2_XY();

//handler for ADC14
void ADC14_IRQHandler();

#endif /* ADC_H_ */
