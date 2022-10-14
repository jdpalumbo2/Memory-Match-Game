/*
 * ps2.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Johnny Palumbo
 */

#include <student/adc.h>

/******************************************************************************
 * Student Defined ADC14 Global Variables
 *****************************************************************************/
volatile uint32_t PS2_X_DIR = 0;
volatile uint32_t PS2_Y_DIR = 0;

volatile bool delay = false;

/******************************************************************************
 * ADC14 Initialization Function
 *
 * Write a function that will be called to initialize the ADC14 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void ece353_ADC14_PS2_XY(void)
{

    // Configured the X direction as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;

    // Configured the Y direction as an analog input pin.
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;

    // Configured CTL0 to sample 16-times in pulsed sample mode
    //  and made it a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
       ADC14->CTL1 = ADC14_CTL1_RES_2;

       // Associate the X direction analog signal with MEM[0]
       ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;

       // Associate the Y direction analog signal with MEM[1]
       ADC14->MCTL[1] = ADC14_MCTLN_INCH_9 | ADC14_MCTLN_EOS;

       // Enable interrupts in the ADC AFTER a value is written into MEM[1].
       ADC14->IER0 = ADC14_IER0_IE1;

       // Enable ADC Interrupt in the NVIC
       NVIC_EnableIRQ(ADC14_IRQn);

       // Turn ADC ON
       ADC14->CTL0 |= ADC14_CTL0_ON;

   }


//*****************************************************************************
//                         Interrupt Service Routines
//*****************************************************************************

void ADC14_IRQHandler(void)
{
    //read x val
    PS2_X_DIR = ADC14->MEM[0];
    //read y val
    PS2_Y_DIR = ADC14->MEM[1];

    delay = true;
}

