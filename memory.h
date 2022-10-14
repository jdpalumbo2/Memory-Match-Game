/*
 * memory.h
 *
 *  Created on: Jun 22, 2022
 *      Author: Johnny Palumbo
 */

#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <stdbool.h>
#include <staff/game_board.h>
#include <staff/lcd.h>
#include <staff/hw1_images.h>
#include <student/adc.h>
#include <student/timer32.h>



/*******************************************************************************
* Function Name: memory_game()
********************************************************************************
* Summary: Initializes all of the hardware resources for HW01
*******************************************************************************/
void memory_game(void);


/*******************************************************************************
* Function Name: memory_init
********************************************************************************
* Summary: Initializes the game board to all ? marks
*******************************************************************************/
void memory_init(void);

#endif /* __MEMORY_H_ */
