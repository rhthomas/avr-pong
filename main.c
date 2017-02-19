/**
 * @file main.c
 * @author Rhys Thomas
 * @created 2015-12-10
 * @brief Pong implemented on atmega644p.
 */

#include "pong.h"

int main()
{
	init_lcd();
	init_tone();

	// button inputs on PORTD
	DDRD  = 0x00;
	PORTD = 0xFF;
	DDRB  = 0xFF;

	////////////////////////
	// STARTUP SCREEN
	////////////////////////
	display.y = 240;
	display.x = 50;
	display_string("3...");
	play_short();
	_delay_ms(1000);
	display_string("2...");
	play_short();
	_delay_ms(1000);
	display_string("1...");
	play_short();
	_delay_ms(1000);
	clear_screen();
	display.y = 240;
	display.x = 50;
	display_string("GO!");
	play_long();
	clear_screen();

	////////////////////////
	// INITIALISE SCOREBOARD
	////////////////////////
	update_scoreboard();

	rectangle wall = {231,231,0,319};
	fill_rectangle(wall, WHITE);

	////////////////////////
	// (RED) PADDLE 1 DIMENSIONS
	////////////////////////
	int pad_a_x = 95, pad_a_y = 0;
	rectangle paddle1 = {pad_a_x, pad_a_x + 50, pad_a_y, pad_a_y + 4};
	fill_rectangle(paddle1,RED);

	////////////////////////
	// (GREEN) PADDLE 2 DIMENSIONS
	////////////////////////
	int pad_b_x = 95, pad_b_y = 319;
	rectangle paddle2 = {pad_b_x, pad_b_x + 50, pad_b_y - 4, pad_b_y};
	fill_rectangle(paddle2,GREEN);

	////////////////////////
	// BALL DIMENSIONS
	////////////////////////
	int ball_x = 120, ball_y = 160;
	rectangle ball = {ball_x, ball_x + SIZE, ball_y, ball_y + SIZE};
	int dir_x = 1, dir_y = 1;
	fill_rectangle(ball,WHITE);
	_delay_ms(500);

	for(;;)
	{
		// draw ball
		fill_rectangle(ball,WHITE);

		////////////////////////
		// PADDLE 1 MOVE CONTROLS
		////////////////////////
		if(PIND & _BV(PD0)) { // move RIGHT
			if(paddle1.right == 230) {
				paddle1.right = 230;
				paddle1.left = 182; // 239 - width of paddle
				// no need to redraw
			} else {
				// clear paddle
				fill_rectangle(paddle1,BLACK);

				// relocate
				paddle1.left += 1;
				paddle1.right += 1;

				// redraw
				fill_rectangle(paddle1,RED);
			}
		}
		if(PIND & _BV(PD1)) { // move LEFT
			if(paddle1.left == 0) {
				paddle1.left = 0;
				paddle1.right = 50;
				// no need to redraw
			} else {
				// clear paddle
				fill_rectangle(paddle1,BLACK);

				// relocate
				paddle1.left -= 1;
				paddle1.right -= 1;

				// redraw
				fill_rectangle(paddle1,RED);
			}
		}

		////////////////////////
		// PADDLE 2 MOVE CONTROLS
		////////////////////////
		if(PIND & _BV(PD2)) { // move RIGHT
			if(paddle2.right == 230) {
				paddle2.right = 230;
				paddle2.left = 182; // 239 - width of paddle
				// no need to redraw
			} else {
				// clear paddle
				fill_rectangle(paddle2,BLACK);

				// relocate
				paddle2.left += 1;
				paddle2.right += 1;

				// redraw
				fill_rectangle(paddle2,GREEN);
			}
		}
		if(PIND & _BV(PD3)) { // move LEFT
			if(paddle2.left == 0) {
				paddle2.left = 0;
				paddle2.right = 50;
				// no need to redraw
			} else {
				// clear paddle
				fill_rectangle(paddle2,BLACK);

				// relocate
				paddle2.left -= 1;
				paddle2.right -= 1;

				// redraw
				fill_rectangle(paddle2,GREEN);
			}
		}

		// hold ball
		_delay_ms(7);

		// clear ball
		fill_rectangle(ball,BLACK);

		////////////////////////
		// BALL GOES OFF SCREEN
		////////////////////////
		if(ball.bottom == 0 || ball.top == 319) {
			play_long();
			////////////////////////
			// WHERE DID IT GO?
			////////////////////////
			if(ball.bottom == 0) { // green wins
				greenscore++;
			}
			if(ball.top == 319) { // red wins
				redscore++;
			}
			update_scoreboard();

			// put ball back in center
			ball.left = 120;
			ball.right = ball.left + SIZE;
			ball.top = 160;
			ball.bottom = ball.top + SIZE;
			dir_y = -dir_y; // swap direction of x (go toward winner)
			fill_rectangle(ball,WHITE);
			_delay_ms(500);
			fill_rectangle(ball,BLACK);
		}

		////////////////////////
		// IF BALL HITS WALLS
		////////////////////////
		if(ball.right == 230) {
			dir_x = -1;
			play_short();
		}
		if(ball.left == 0) {
			dir_x = 1;
			play_short();
		}

		////////////////////////
		// BALL HITS EITHER PADDLE
		////////////////////////
		if(
		(ball.top == paddle1.bottom + 1 &&
		  (ball.right > paddle1.left && ball.left < paddle1.right)) ||
		(ball.bottom == paddle2.top - 1 &&
		  (ball.right > paddle2.left && ball.left < paddle2.right)))
		{
			dir_x = dir_x;
			dir_y *= -1; // change y direction (reflect)
			play_short();
		}

		////////////////////////
		// RELOCATE BALL
		////////////////////////
		ball.left += dir_x;
		ball.right += dir_x;
		ball.top += dir_y;
		ball.bottom += dir_y;
	}
}
