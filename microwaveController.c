/*
 * microwaveController.c
 *
 *  Author: Micha³ Witas
 *	DDR = 1 - output (|=)
 *	DDR = 0 - input	(&=)
 */ 

#include "common.h"

unsigned char dig[4] = "0000";
unsigned char magStr[4] = "xx50";
TTime time;

int main(void)
{
	initDevice();
	initSafety();
	initEncoder();
	init7Segment();
	initKeyboard();
	initMagnetron();
	
	initTime(&time);
	timeFromString(&time, dig);

	DDRB |= ((1<<0) | (1<<1));
	DDRA |= ((1<<PA7) | (1<<PA6));
	PORTA |= ((1<<PA7)|(1<<PA6));

	sei();
	
    while(1)
    {
		if (encoderState.l)
		{
			encoderState.l = 0;
			magnetronMinus();
			config.powerDisplayed = 1;
			config.powerDispTicks = 0;
			config.powerDispTicks2 = 0;
			magnetronToString(magStr);
		}
		
		if (encoderState.r)
		{
			encoderState.r = 0;
			magnetronPlus();
			config.powerDisplayed = 1;
			config.powerDispTicks = 0;
			config.powerDispTicks2 = 0;
			magnetronToString(magStr);
		}

		if (keyboardCheckAnyPressed())
		{
			config.powerDisplayed = 0;
			config.powerDispTicks = 0;
		}

		if (keyboardHandle(&keyboard[K_START], &time))
		{
			if (time.stoped) 
			{
				timeStart(&time);
				
				if (!(time.t00_0x == 0 && time.t00_x0 == 0 && time.t00_x0 == 0 && time.t0x_00 == 0))
					magnetronStart();
			}
			else timePlus(&time, 2);
		}
		if (keyboardHandle(&keyboard[K_STOP], &time))
		{
			if (!time.stoped)
			{
				timeStop(&time);
				magnetronStop();
			}
			else timeReset(&time);
		}

		if (time.stoped)
		{
			magnetron.ticks = 0;
			magnetron.halfticks = 0;
			if (keyboardHandle(&keyboard[K_1s], &time)) timePlus(&time, 0);
			if (keyboardHandle(&keyboard[K_10s], &time)) timePlus(&time, 1);
			if (keyboardHandle(&keyboard[K_1m], &time)) timePlus(&time, 2);
			if (keyboardHandle(&keyboard[K_10m], &time)) timePlus(&time, 3);
		}
		else
		{
			keyboard[K_1s].pressed = 0;
			keyboard[K_10s].pressed = 0;
			keyboard[K_1m].pressed = 0;
			keyboard[K_10m].pressed = 0;
		}

		if (time.timeToChange)
		{
			if (config.powerDispTicks)
				config.powerDisplayed = 0;
			else
				config.powerDispTicks = 1;

			time.timeToChange = 0;
			timeDecrement(&time);
		}
    }
}

ISR(Timer250HzCompVect)
{
	safetyProcess(&time);
	encProcess();
	timeProcess(&time);

	timeToString(&time, dig);

	if (!config.powerDisplayed)
		sendTo7seg(dig);
	else
	{
		if ((++config.powerDispTicks2) > 250)
		{
			config.powerDisplayed = 0;
			config.powerDispTicks2 = 0;
		}
		else
			sendTo7seg(magStr);
	}

	keyboardProcess();
	
	magnetronToLed();

	if (!time.stoped)
		magnetronProcess();
	else
		magnetronStop();
}

void initDevice()
{
	Timer250Hz &= ~(1<<WGM01 | 1<<WGM00);	// reset counter mode
	Timer250Hz |= (1<<WGM01);	// CTC Mode
	Timer250Hz |= (1<<CS02) | (1<<CS00);	// set prescaller to 1024
	Timer250HzOComp = 62;	// 250Hz (16000000/1024/250)
	TIMSK |= (1<<Timer250HzOCIE);	// enable output compare interupts

	config.powerDisplayed = 0;
	config.powerDispTicks = 0;
}

void initSafety()
{
	SAFETY_DDR &= ~(1<<SAFETY_VEC);	// set as input
	PORTC |= (1<<SAFETY_VEC);		// pull up
}

void safetyProcess(TTime *time)
{
	if (!(SAFETY_PIN & 1<<(SAFETY_VEC)) && !time->stoped)
	{
		magnetronStop();
		timeStop(time);
		keyboardReset(keyboard);
	}	
}

unsigned char keyboardHandle(TKeyboard *keyboard, TTime *time)
{
	if (keyboard->pressed)
	{
		keyboard->pressed = 0;
		keyboard->blocked = 1;
		return 1;
	}
	else return 0;
}