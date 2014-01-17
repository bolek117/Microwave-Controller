/*
 * time.c
 *
 *  Author: Micha³ Witas
 */ 

#include "common.h"

void initTime(TTime *time)
 {
	timeReset(time);
}

void timeReset(TTime *time)
 {
	time->t00_0x = 0;
	time->t00_x0 = 0;
	time->t0x_00 = 0;
	time->tx0_00 = 0;
	
	timeResetControl(time);
	timeStop(time);
}

void timeResetControl(TTime *time)
{
	time->ticks = 0;
	time->timeToChange = 0;
	time->halfTick = 0;
	time->end = 0;
}

void timeProcess(TTime *time)
{
	if (!time->stoped)
	{
		if (time->ticks > 250)
		{
			time->ticks = 0;
			time->timeToChange = 1;
			return;
		}
		
		time->ticks++;
	}
}
 
void timeIncrement(TTime *time)
 {
	
	if ((++time->t00_0x) < 10) return;
	time->t00_0x = 0;

	if ((++time->t00_x0) < 6) return;
	time->t00_x0 = 0;

	if ((++time->t0x_00) < 10) return;
	time->t0x_00 = 0;

	if ((++time->tx0_00) < 10) return;
	
	timeReset(time);
}

void timeDecrement(TTime *time)
{
	if ((--time->t00_0x) < 10) return;	// because of overflow (unsigned 0-1 = 255)
	time->t00_0x = 9;

	if ((--time->t00_x0) < 6) return;
	time->t00_x0 = 5;

	if ((--time->t0x_00) < 10) return;
	time->t0x_00 = 9;

	if ((--time->tx0_00) < 10) return;

	timeReset(time);
}
 
void timeToString(TTime *time, unsigned char *res)
{
	res[3] = time->t00_0x+'0';
	res[2] = time->t00_x0+'0';
	res[1] = time->t0x_00+'0';
	res[0] = time->tx0_00+'0';
}

void timeFromString(TTime *time, unsigned char *res)
{
	time->t00_0x = res[3]-'0';
	time->t00_x0 = res[2]-'0';
	time->t0x_00 = res[1]-'0';
	time->tx0_00 = res[0]-'0';
}

void timeStart(TTime *time)
{
	time->stoped = 0;
	timeResetControl(time);
}

void timeStop(TTime *time)
{
	time->stoped = 1;
	timeResetControl(time);
}

void timePlus(TTime *time, unsigned char position)
{
	switch(position)
	{
		case 0:
		if ((++time->t00_0x) > 9) time->t00_0x = 0;
		break;
		case 1:
		if ((++time->t00_x0) > 5) time->t00_x0 = 0;
		break;
		case 2:
		if ((++time->t0x_00) > 9) time->t0x_00 = 0;
		break;
		case 3:
		if ((++time->tx0_00) > 9) time->tx0_00 = 0;
		break;
	}
}
