/*
 * rotaryEncoder.h
 *
 *  Author: Micha³ Witas
 */ 


#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_

#include "common.h"

#define b1 !(ENC_PIN & 1<<ENC_L)
#define b0 !(ENC_PIN & 1<<ENC_R)

#define ENC_PORT PORTC
#define ENC_PIN	PINC
#define ENC_DDR	DDRC

#define ENC_L	4
#define ENC_R	5

enum {
	enc_idle = 0,
	enc_l0,
	enc_l1,
	enc_l2,
	enc_r0,
	enc_r1,
	enc_r2
};

typedef union TEncState
{
	struct 
	{
		unsigned char r:1;
		unsigned char l:1;
	};
} TEncState;

TEncState encoderState;

void initEncoder();
void encProcess();

#endif /* ROTARYENCODER_H_ */