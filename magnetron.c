/*
 * magnetron.c
 *
 *  Author: Micha³ Witas
 */ 

#include "common.h"

void initMagnetron(void)
{
	magnetron.percent = 50;
	magnetron.ticks = 0;
	magnetron.halfticks = 0;
	magnetron.on = 0;

	//MAGNETRON_DDR |= (1<<MAGNETRON_VEC|1<<MAGNETRON_LED0|1<<MAGNETRON_LED1|1<<MAGNETRON_LED2|1<<MAGNETRON_LED3|1<<MAGNETRON_LED4);
	MAGNETRON_DDR = 0xff;
	MAGNETRON_PORT = 0xff;
}

void magnetronPlus( void )
{
	if ((magnetron.percent += 5) > 100) magnetron.percent = 100;
	magnetronStop();
}

void magnetronMinus( void )
{
	if ((magnetron.percent -= 5) < 10) magnetron.percent = 10;
	magnetronStop();
}

void magnetronStop( void )
{
	magnetron.on = 0;
	MAGNETRON_PORT &= ~(1<<MAGNETRON_VEC);
	magnetron.ticks = 0;
}

void magnetronStart( void )
{
	magnetron.on = 1;
	MAGNETRON_PORT |= (1<<MAGNETRON_VEC);
	magnetron.ticks = 0;
}

void magnetronToString(unsigned char *str)
{
	itoa(magnetron.percent, str, 10);
	unsigned char
		a = str[0],
		b = str[1];

	if (magnetron.percent < 100)
	{
		str[0] = 'x';
		str[1] = 'x';
		str[2] = a;
		str[3] = b;
	}
	else
	{
		str[0] = 'x';
		str[1] = '1';
		str[2] = '0';
		str[3] = '0';
	}
}

void magnetronToLed( void )
{
	MAGNETRON_PORT |= (1<<MAGNETRON_LED0|1<<MAGNETRON_LED1|1<<MAGNETRON_LED2|1<<MAGNETRON_LED3);
	MAGNETRON_PORT &= ~(1<<MAGNETRON_LED4);
	if (magnetron.percent > 20) MAGNETRON_PORT &= ~(1<<MAGNETRON_LED3);
	if (magnetron.percent > 40) MAGNETRON_PORT &= ~(1<<MAGNETRON_LED2);
	if (magnetron.percent > 60) MAGNETRON_PORT &= ~(1<<MAGNETRON_LED1);
	if (magnetron.percent > 80) MAGNETRON_PORT &= ~(1<<MAGNETRON_LED0);
}

void magnetronProcess(void)
{
	if ((++magnetron.ticks) > 250)
	{
		magnetron.ticks = 0;

		if ((++magnetron.halfticks) > MAGNETRON_TIMEBASE-1)
		{
			magnetron.halfticks = 0;
		}

		unsigned int compareTick = MAGNETRON_TIMEBASE*magnetron.percent;

		if (magnetron.halfticks == 0 || magnetron.halfticks*100 == compareTick)
		{
			switch(magnetron.on)
			{
				case 1:
					magnetronStop();
				break;
				case 0:
					magnetronStart();
				break;
			}
		}
		
	}
}