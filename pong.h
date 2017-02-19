/**
 * @file pong.h
 * @author Rhys Thomas
 * @created 2015-12-10
 * @brief PWM and scoreboard functions.
 *
 * PD0 = move ( red ) paddle 1 right (white)
 * PD1 = move ( red ) paddle 1 left
 * PD2 = move (green) paddle 2 right (white)
 * PD3 = move (green) paddle 2 left
 * PD5 = speaker
 */

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // used for sprintf

#define SIZE 5
#define BEEP 880
#define BOOP 294

// global scoreboard variables
int greenscore = 0, redscore = 0;
char scorestring[50]; // pre defined

/**
 * @brief Setup PWM timers.
 */
void init_tone();

/**
 * @brief Defines OCR1A tone based on input frequency.
 * @param frequency Frequency of PWM tone to play.
 */
void tone(uint16_t frequency);

/**
 * @brief Short tone for collitions.
 */
void play_short();

/**
 * @brief Long tone for when the ball leaves the screen.
 */
void play_long();

/**
 * @brief Update scoreboard on the side of the display.
 */
void update_scoreboard();
