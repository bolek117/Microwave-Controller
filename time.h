/*
 * time.h
 *
 *  Author: Micha³ Witas
 */ 


#ifndef TIME_H_
#define TIME_H_

typedef struct TTime
{
	unsigned char t00_0x;
	unsigned char t00_x0;
	unsigned char t0x_00;
	unsigned char tx0_00;
	unsigned char ticks;

	unsigned char stoped:1;
	unsigned char timeToChange:1;
	unsigned char halfTick:1;
	unsigned char end:1;
	unsigned char foo:4;
	
} TTime;

void initTime(TTime *time);
void timeReset(TTime *time);
void timeProcess(TTime *time);
void timeIncrement(TTime *time);
void timeDecrement(TTime *time);
void timeToString(TTime *time, unsigned char *res);
void timeFromString(TTime *time, unsigned char *res);
void timeStart(TTime *time);
void timeStop(TTime *time);
void timePlus(TTime *time, unsigned char position);
void timeResetControl(TTime *time);
/*void Str2TTime(unsigned char *str, volatile TTime *time);
void TTime2Str(volatile TTime *time, unsigned char *str);*/

#endif /* TIME_H_ */