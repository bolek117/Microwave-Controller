/*
 * magnetron.h
 *
 *  Author: Micha³ Witas
 */ 


#ifndef MAGNETRON_H_
#define MAGNETRON_H_

#define MAGNETRON_PORT	PORTB
#define MAGNETRON_PIN	PINB
#define MAGNETRON_DDR	DDRB
#define MAGNETRON_VEC	0
#define MAGNETRON_LED0	3
#define MAGNETRON_LED1	4
#define MAGNETRON_LED2	5
#define MAGNETRON_LED3	6
#define MAGNETRON_LED4	7

#define MAGNETRON_TIMEBASE	20

typedef struct TMagnetron
{
	unsigned char ticks;
	unsigned char halfticks;

	unsigned char foo:1;
	unsigned char percent:7;
	unsigned char on:1;
	unsigned char changed:1;
} TMagnetron;

TMagnetron magnetron;

void initMagnetron(void);
void magnetronPlus(void);
void magnetronMinus(void);
void magnetronStop(void);
void magnetronStart(void);
void magnetronToString(unsigned char *str);
void magnetronToLed(void); 
void magnetronProcess(void);

#endif /* MAGNETRON_H_ */