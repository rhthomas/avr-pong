/**
 * @file pong.c
 * @author Rhys Thomas
 * @created 2015-12-10
 * @brief PWM and scoreboard functions.
 */

void init_tone()
{
	TCCR1A = _BV(COM1A0) | _BV(WGM10);
	TCCR1B = _BV(WGM13) | _BV(CS11);
}

void tone(uint16_t frequency)
{
	OCR1A = (uint16_t) ((F_CPU) / (2*2*8*frequency));
}

void play_short()
{
	tone(BEEP);
	DDRD |= _BV(PD5); // set as output
	_delay_ms(5);
	DDRD &= ~_BV(PD5); // set as input when not on
}

void play_long()
{
	tone(BOOP);
	DDRD |= _BV(PD5); // set as output
	_delay_ms(400);
	DDRD &= ~_BV(PD5); // set as input when not on
}

void update_scoreboard()
{
	display.x = 100;
	display.y = 0;
	sprintf(scorestring, "score:  %d-%d", redscore, greenscore);
	set_orientation(East);
	display_string(scorestring);
	set_orientation(North);
}