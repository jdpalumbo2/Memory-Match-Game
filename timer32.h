/*
 * timer32.h
 *
 *  Created on: Sep 28, 2022
 *      Author: Johnny Palumbo
 */

#ifndef TIMER32_H_
#define TIMER32_H_

#include <stdint.h>
#include <stdbool.h>
#include <msp.h>

/******************************************************************************
 * Student Defined Timer32 Macros
 *****************************************************************************/

/******************************************************************************
 * Student Defined Timer32 Extern Global Variables
 *****************************************************************************/
extern volatile bool ALERT_S2;
extern volatile bool ALERT_T2;
/******************************************************************************
 * Student Defined T32_1 Initialization Function
 *
 * Define a function that will be called to initialize the T32_1 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void TIMER32_1_init();
/******************************************************************************
 * Student Defined T32_2 Initialization Function
 *
 * Define a function that will be called to initialize the T32_2 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void TIMER32_2_init();
//bool ece353_ MKII_S2();

void T32_INT1_IRQHandler();
void T32_INT2_IRQHandler();




#endif /* TIMER32_H_ */
