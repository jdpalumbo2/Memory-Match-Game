/*
 * timer32.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Johnny Palumbo
 */

#include <student/timer32.h>

/******************************************************************************
 * Student Defined Timer32 Global Variables
 *****************************************************************************/
volatile bool ALERT_S2 = false; // checks if button is pressed
volatile bool ALERT_T2 = false; // checks if screen needs updating

/******************************************************************************
 * T32_1 Initialization Function
 *
 * Write a function that will be called to initialize the T32_1 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void TIMER32_1_init(){

    //interrupt every 50ms
    uint32_t ticks = ((SystemCoreClock * 50) / 1000) - 1;

    //STOP TIMER
    TIMER32_1 -> CONTROL = 0;

    //SET TIMER TO BE A 32 BIT periodic
    //TIMER32_1 -> CONTROL = TIMER32_CONTROL_MODE | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_1;

    //SET THE LOAD REGISTER
    TIMER32_1 -> LOAD = ticks;

    //enable timer32 interrupt in NVIC
    __enable_irq();
    NVIC_EnableIRQ(T32_INT1_IRQn);
    //NVIC_SetPriority(T32_INT1_IRQn, 0);

    //Start timer and enable interrupts
    TIMER32_1 -> CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_IE | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_MODE;
}

/******************************************************************************
 * T32_2 Initialization Function
 *
 * Write a function that will be called to initialize the T32_2 based on the
 * HW01 Requirements Doc.
 *****************************************************************************/
void TIMER32_2_init(){

    //interrupt every second
    //uint32_t ticks = ((SystemCoreClock * 1000) / 1000) - 1;

    //STOP TIMER
    TIMER32_2 -> CONTROL = 0;

    //SET TIMER TO BE A 32 BIT ONE SHOT
    TIMER32_2 -> CONTROL = TIMER32_CONTROL_ONESHOT | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_2;

    //SET THE LOAD REGISTER
    //FIX
    TIMER32_2 -> LOAD = 93750;

    //enable timer32 interrupt in NVIC
    __enable_irq();
    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_SetPriority(T32_INT2_IRQn, 0);

    //Start timer and enable interrupts
    TIMER32_2 -> CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ONESHOT | TIMER32_CONTROL_SIZE;
}

//*****************************************************************************
//                         Interrupt Service Routines
//*****************************************************************************
bool ece353_MKII_S2(void){
    if((P3->IN & BIT5) == 0){
        return true;
    }
    return false;
}
void T32_INT1_IRQHandler(void)
{
    //keeps track of debounce
    static uint8_t button_state = 0x00;

    bool button_pressed = true;

    if(!button_pressed)
    {
        if(!ece353_MKII_S2()){
            button_pressed = true;
        }

    }

    if(button_pressed)
    {
        //debounce button
        button_state = button_state << 1;

        if(ece353_MKII_S2()){
            button_state |= 0x01;
        }

        if(button_state == 0x07){
            ALERT_S2 = true;
            button_pressed = false;
        }
    }


    //start adc14 conversions
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    //writing anything to reg will clear interrupt
    TIMER32_1->INTCLR = 0;
}

void T32_INT2_IRQHandler(void)
{
    ALERT_T2 = true;

    TIMER32_2->INTCLR = 0; //writing anything to reg will clear interrupt
}


