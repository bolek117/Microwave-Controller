/*
 * common.h
 *
 *  Author: Micha³ Witas
 */ 

#ifndef COMMON_H_
#define COMMON_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define Timer250Hz			TCCR0
#define Timer250HzOComp		OCR0
#define Timer250HzOCIE		OCIE0
#define Timer250HzCompVect	TIMER0_COMP_vect

#define PWM100Hz			TCCR2
#define PWM100HzOComp		OCR2
#define PWM100HzOCIE		OCIE2
#define PWM100HzCompVect	TIMER2_COMP_vect

#define SAFETY_PORT PORTC
#define SAFETY_PIN	PINC
#define SAFETY_DDR	DDRC
#define SAFETY_VEC	6

enum
{
	K_START,
	K_STOP,
	K_1s,
	K_10s,
	K_1m,
	K_10m,
	K_MAX
};

typedef struct TConfig
{
	unsigned char powerDisplayed:1;
	unsigned char powerDispTicks:1;
	unsigned char powerDispTicks2;
} TConfig;

TConfig config;

#include "rotaryEncoder.h"
#include "time.h"
#include "led7segment.h"
#include "keyboard.h"
#include "magnetron.h"

void initDevice(void);
void initSafety(void);
void safetyProcess(TTime *time);
unsigned char keyboardHandle(TKeyboard *keyboard, TTime *time);

#endif /* COMMON_H_ */