/*
 * rotaryEncoder.c
 *
 *  Author: Micha³ Witas
 */ 

#include "rotaryEncoder.h"

void initEncoder()
{
	ENC_DDR &= ~((1<<ENC_L)|(1<<ENC_R));	// Set encoder pins as input
	ENC_PORT |= ((1<<ENC_L)|(1<<ENC_R));	// pull up to logic one
}

void encProcess()
{	
	static unsigned char state = enc_idle;
	
	switch (state)
	{
		case enc_idle:
		{
			if (b1 & !b0) {state = enc_r0; return;}
			if (!b1 & b0) {state = enc_l0; return;}
		}
		break;
		case enc_r0:
		{
			if (!b1) {state = enc_idle; return;}
			if (b1 & b0) {state = enc_r1; return;}
		}
		break;
		case enc_r1:
		{
			if (!b0) {state = enc_r0; return;}
			if (!b1 & b0) {state = enc_r2; return;}
		}
		break;
		case enc_r2:
		{
			if (b1) {state = enc_r1; return;}
			if (!b1 & !b0) {
				state = enc_idle;
				encoderState.r = 1;
				return;
			}
		}
		break;
		case enc_l0:
		{
			if (!b0) {state = enc_idle; return;}
			if (b1 & b0) {state = enc_l1; return;}
		}
		break;
		case enc_l1:
		{
			if (!b1) {state = enc_l0; return;}
			if (b1 & !b0) {state = enc_l2; return;}
		}
		break;
		case enc_l2:
		{
			if (b0) {state = enc_l1; return;}
			if (!b1 & !b0) {
				state = enc_idle;
				encoderState.l = 1;
				return;
			}
		}
		break;
	}
}