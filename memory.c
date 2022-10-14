/*
 * memory.c
 *
 *  Created on: Jun 22, 2022
 *      Author: Johnny Palumbo
 */
#include <student/memory.h>

/******************************************************************************
 * Student Defined Global Variables
 *****************************************************************************/
#define VOLT_0P66 ((int)(0.66/(3.3/4096)))
#define VOLT_2P64 ((int)(2.64/(3.3/4096)))

//creates 2 3 value arrays for columns and rows
volatile int x_pos[3] = { LEFT_COL, CENTER_COL, RIGHT_COL };
volatile int y_pos[3] = { UPPER_ROW, CENTER_ROW, LOWER_ROW };

//sets initial position to middle row middle column
volatile int x_current = 1;
volatile int y_current = 1;

//sets a counter of the amount of images inverted
//volatile int index[2][3];
volatile int image_flip_cnt = 0;
volatile int images_matched = 0;

volatile int megaman_cnt = 0;
volatile int monkey_cnt = 0;
volatile int smile_cnt = 0;

//enumerator to state if the picture is on the screen
bool board_displays_temp[3][3] = { { // Upper Row
        { false },   // Upper Left
        { false },     // Upper Center
        { false }      // Upper Right
        },
        { // Middle Row
        { false },     // Middle Left
        { false },  // Middle Center
        { false }      // Middle Right
        },
        { // Lower Row
        { false },      // Lower Left
        { false },   // Lower Center
        { false }       // Lower Right
        } };

bool board_displays_permanent[3][3] = { { // Upper Row
        { false },   // megaman
        { false },     // monkey
        { false }      // monkey
        },
        { // Middle Row
        { false },     // smile
        { false },  // megaman
        { false }      // monkey
        },
        { // Lower Row
        { false },      // smile
        { false },   // megaman
        { false }       // smile
        } };

/******************************************************************************
 * Student Defined Helper Functions
 *
 * Add any helper functions that you want in the space below.  You can add
 * as many or as few functions as you want.
 *****************************************************************************/

//bool ece353_MKII_S2(void)
//{
//    if((P3->IN &BIT5) == 0)
//    {
//        return true;
//    }
//    else{
//        return false;
//    }
//}
void turn_on()
{
    //changes the current positions background and foreground to be filled
    if ((board_displays_temp[y_current][x_current] == false)
            && (board_displays_permanent[y_current][x_current] == false))
    {
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_GREEN);
        //redraws question mark
        lcd_draw_image(x_pos[x_current], y_pos[y_current],
                       question_width_pixels, question_height_pixels,
                       question_bitmaps,
                       LCD_COLOR_BLACK, //foreground
                       LCD_COLOR_GREEN //background
                       );
    }
    else
    {

        //checks what image is on what square and then draws corresponding image to screen
        // depending on where the joystick presses
        IMAGE_TYPE_t image = Game_Board[y_current][x_current];

        if (image == MEGA_MAN)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_RED);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           mega_man_width_pixels, mega_man_height_pixels,
                           mega_man_bitmaps,
                           LCD_COLOR_BLACK,
                           LCD_COLOR_RED);
        }
        else if (image == MONKEY)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_RED);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           monkey_width_pixels, monkey_height_pixels,
                           monkey_bitmaps,
                           LCD_COLOR_BLACK,
                           LCD_COLOR_RED);
        }
        else if (image == SMILE)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_RED);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           smile_width_pixels, smile_height_pixels,
                           smile_bitmaps,
                           LCD_COLOR_BLACK,
                           LCD_COLOR_RED);
        }
    }
}

void turn_off()
{
    if ((board_displays_temp[y_current][x_current] == false)
            && (board_displays_permanent[y_current][x_current] == false))
    {
        //changes the current positions background and foreground to be filled
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_BLACK);
        //redraws question mark
        lcd_draw_image(x_pos[x_current], y_pos[y_current],
                       question_width_pixels, question_height_pixels,
                       question_bitmaps,
                       LCD_COLOR_GREEN, //foreground
                       LCD_COLOR_BLACK //background
                       );
    }
    else
    {

        // checks to see if the image is currently on screen
        IMAGE_TYPE_t image = Game_Board[y_current][x_current];

        if (image == MEGA_MAN)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_BLACK);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           mega_man_width_pixels, mega_man_height_pixels,
                           mega_man_bitmaps,
                           LCD_COLOR_RED,
                           LCD_COLOR_BLACK);
        }
        else if (image == MONKEY)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_BLACK);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           monkey_width_pixels, monkey_height_pixels,
                           monkey_bitmaps,
                           LCD_COLOR_RED,
                           LCD_COLOR_BLACK);
        }
        else if (image == SMILE)
        {
            lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
            SQUARE_SIZE,
                               SQUARE_SIZE,
                               LCD_COLOR_BLACK);
            lcd_draw_image(x_pos[x_current], y_pos[y_current],
                           smile_width_pixels, smile_height_pixels,
                           smile_bitmaps,
                           LCD_COLOR_RED,
                           LCD_COLOR_BLACK);
        }
    }
}

void mv_right()
{

    if (x_current == 2)
    {
        //dont do anything
    }
    else
    {

        turn_off(); //change background and foreground colors for current square
        x_current = x_current + 1;  // increment
        turn_on();    // change background and foreground colors for next square

    }

}

void mv_left()
{

    if (x_current == 0)
    {
        //dont do anything
    }
    else
    {

        turn_off(); //change background and foreground colors for current square
        x_current = x_current - 1; // decrement
        turn_on();    // change background and foreground colors for next square

    }

}

void mv_up()
{

    if (y_current == 0)
    {
        //dont do anything
    }
    else
    {

        turn_off(); //change background and foreground colors for current square
        y_current = y_current - 1; // decrement
        turn_on();    // change background and foreground colors for next square

    }

}

void mv_down()
{

    if (y_current == 2)
    {
        //dont do anything
    }
    else
    {

        turn_off(); //change background and foreground colors for current square
        y_current = y_current + 1; // increment
        turn_on(); // change background and foreground colors for next square

    }

}

void revealImage()
{
    IMAGE_TYPE_t image = Game_Board[y_current][x_current]; // check which image should be displayed at current location

    //if the selected square corresponds to any of the 3 images, place correct image in square
    if (image == MEGA_MAN)
    {
        megaman_cnt = megaman_cnt + 1;
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_RED);
        lcd_draw_image(x_pos[x_current], y_pos[y_current],
                       mega_man_width_pixels, mega_man_height_pixels,
                       mega_man_bitmaps,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_RED);
    }
    else if (image == MONKEY)
    {
        monkey_cnt = monkey_cnt + 1;
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_RED);
        lcd_draw_image(x_pos[x_current], y_pos[y_current], monkey_width_pixels,
                       monkey_height_pixels, monkey_bitmaps,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_RED);
    }
    else if (image == SMILE)
    {
        smile_cnt = smile_cnt + 1;
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_RED);
        lcd_draw_image(x_pos[x_current], y_pos[y_current], smile_width_pixels,
                       smile_height_pixels, smile_bitmaps,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_RED);
    }
    board_displays_temp[y_current][x_current] = true;
    image_flip_cnt = image_flip_cnt + 1;
}

void reset()
{
    int i;
    int j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            //changes the current positions background and foreground to be filled
            if ((board_displays_permanent[i][j] == false))
            {
                lcd_draw_rectangle(x_pos[j], y_pos[i],
                SQUARE_SIZE,
                                   SQUARE_SIZE,
                                   LCD_COLOR_BLACK);
                //redraws question mark
                lcd_draw_image(x_pos[j], y_pos[i], question_width_pixels,
                               question_height_pixels, question_bitmaps,
                               LCD_COLOR_GREEN, //foreground
                               LCD_COLOR_BLACK //background
                               );
            }
            else
            {

                //checks what image is on what square and then draws corresponding image to screen
                // depending on where the joystick presses
                IMAGE_TYPE_t image = Game_Board[i][j];

                if (image == MEGA_MAN)
                {
                    lcd_draw_rectangle(x_pos[j], y_pos[i],
                    SQUARE_SIZE,
                                       SQUARE_SIZE,
                                       LCD_COLOR_BLACK);
                    lcd_draw_image(x_pos[j], y_pos[i], mega_man_width_pixels,
                                   mega_man_height_pixels, mega_man_bitmaps,
                                   LCD_COLOR_RED,
                                   LCD_COLOR_BLACK);
                }
                else if (image == MONKEY)
                {
                    lcd_draw_rectangle(x_pos[j], y_pos[i],
                    SQUARE_SIZE,
                                       SQUARE_SIZE,
                                       LCD_COLOR_BLACK);
                    lcd_draw_image(x_pos[j], y_pos[i], monkey_width_pixels,
                                   monkey_height_pixels, monkey_bitmaps,
                                   LCD_COLOR_RED,
                                   LCD_COLOR_BLACK);
                }
                else if (image == SMILE)
                {
                    lcd_draw_rectangle(x_pos[j], y_pos[i],
                    SQUARE_SIZE,
                                       SQUARE_SIZE,
                                       LCD_COLOR_BLACK);
                    lcd_draw_image(x_pos[j], y_pos[i], smile_width_pixels,
                                   smile_height_pixels, smile_bitmaps,
                                   LCD_COLOR_RED,
                                   LCD_COLOR_BLACK);
                }
            }
        }
    }
    {
        lcd_draw_rectangle(x_pos[x_current], y_pos[y_current],
        SQUARE_SIZE,
                           SQUARE_SIZE,
                           LCD_COLOR_GREEN);
        //redraws question mark
        lcd_draw_image(x_pos[x_current], y_pos[y_current],
                       question_width_pixels, question_height_pixels,
                       question_bitmaps,
                       LCD_COLOR_BLACK, //foreground
                       LCD_COLOR_GREEN //background
                       );
    }
}

/*******************************************************************************
 * Function Name: memory_game()
 ********************************************************************************
 * Summary: Implements the Memory game described in the HW01 Requirements Doc.
 *
 *          main.c calls memory_init() followed by memory_game().  memory_init()
 *          initializes the LCD and draws the starting game board.
 *******************************************************************************/
void memory_game(void)
{

    int i = 0;
    int j = 0;
    /* Make sure that the MCU is running at 24MHz by changing __SYSTEM_CLOCK in
     * system_msp432p401r.c to be 24000000 */

    /* Add your code to initialize T32_1 */
    TIMER32_1_init();

    /* Add your code to initialize T32_2 */
    TIMER32_2_init();
    ALERT_T2 = false;

    /* Add your code to initialize ADC14 */
    ece353_ADC14_PS2_XY();

    /* Add your code for the memory game */

    while (1)
    {

        //adds delay to make movement smoother
        if (delay)
        {
            delay = false;

            //checks voltage for each direction to determine which direction function to call
            if (PS2_X_DIR > VOLT_2P64)
            {
                mv_right();
            }
            if (PS2_X_DIR < VOLT_0P66)
            {
                mv_left();
            }
            if (PS2_Y_DIR < VOLT_0P66)
            {
                mv_down();
            }
            if (PS2_Y_DIR > VOLT_2P64)
            {
                mv_up();
            }
        }

        //game logic
        if (ALERT_S2)
        {
            ALERT_S2 = false;
            revealImage();
        }

        if (images_matched == 3)
        {
            {

                //draws game over if all 3 sets of images are revealed
                lcd_draw_image(CENTER_ROW, CENTER_COL,
                               game_over_width_pixels, game_over_height_pixels,
                               game_over_bitmaps,
                               LCD_COLOR_WHITE, //foreground
                               LCD_COLOR_BLACK //background
                               );
            }
        }

        if (image_flip_cnt == 3)
        {
            if (megaman_cnt == 3) //// if 3 megamans are selected set permanent
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (Game_Board[i][j] == MEGA_MAN)
                            board_displays_permanent[i][j] = true;
                    }
                }
                images_matched = images_matched + 1; // increment images matched
            }
            else if (monkey_cnt == 3) // if 3 monkeys are selected set permanent
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (Game_Board[i][j] == MONKEY)
                            board_displays_permanent[i][j] = true;
                    }
                }
                images_matched = images_matched + 1; // increment images matched
            }
            else if (smile_cnt == 3) // if 3 smiles are selected set permanent
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (Game_Board[i][j] == SMILE)
                            board_displays_permanent[i][j] = true;
                    }
                }
                images_matched = images_matched + 1; // increment images matched
            }
            else
            {
                TIMER32_2_init(); // sets delay for after 3 incorrect images
                while (!ALERT_T2)
                {
                }
                reset();
                ALERT_T2 = false;

            }
            //sets counts for all images
            image_flip_cnt = 0;
            megaman_cnt = 0;
            monkey_cnt = 0;
            smile_cnt = 0;
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    board_displays_temp[i][j] = false;
                }
            }
        }

    }
}

/*******************************************************************************
 * Function Name: memory_init
 ********************************************************************************
 * Summary: Initializes the game board to all ? marks
 *******************************************************************************/
void memory_init(void)
{
    // MK2 SW2 configure as input
    P3->DIR &= ~BIT5;

    // Initialize LCD
    lcd_init();

    // Clear the LCD screen
    lcd_clear_screen();

    // Draw board lines
    // Horizontal Lines
    lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,
    LINE_WIDTH,
                       LCD_COLOR_BLUE);
    lcd_draw_rectangle(SCREEN_CENTER_COL, LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,
    LINE_WIDTH,
                       LCD_COLOR_BLUE);

    //Vertical Lines
    lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH,
    LINE_LENGTH,
                       LCD_COLOR_BLUE);
    lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH,
    LINE_LENGTH,
                       LCD_COLOR_BLUE);

    // Draw all of the question marks to start the game.

    // ********************* Upper Row, Left Col *****************************
    lcd_draw_image(
    LEFT_COL,
                   UPPER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Upper Row, Center Col *****************************
    lcd_draw_image(
    CENTER_COL,
                   UPPER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Upper Row, Right Col *****************************
    lcd_draw_image(
    RIGHT_COL,
                   UPPER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Center Row, Left Col *****************************
    lcd_draw_image(
    LEFT_COL,
                   CENTER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Center Row, Center Col *****************************
    // Invert the colors of the center square and draw a rectangle
    lcd_draw_rectangle(
    CENTER_COL,
                       CENTER_ROW,
                       SQUARE_SIZE,
                       SQUARE_SIZE,
                       LCD_COLOR_GREEN);

    /* Draw the inverted image over the rectangle to indicate the active square */
    lcd_draw_image(
    CENTER_COL,
                   CENTER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_BLACK,
                   LCD_COLOR_GREEN);

    // ********************* Center Row, Right Col *****************************
    lcd_draw_image(
    RIGHT_COL,
                   CENTER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Lower Row, Left Col *****************************
    lcd_draw_image(
    LEFT_COL,
                   LOWER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Lower Row, Center Col *****************************
    lcd_draw_image(
    CENTER_COL,
                   LOWER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

    // ********************* Lower Row, Right Col *****************************
    lcd_draw_image(
    RIGHT_COL,
                   LOWER_ROW, question_width_pixels, question_height_pixels,
                   question_bitmaps,
                   LCD_COLOR_GREEN,
                   LCD_COLOR_BLACK);

}

