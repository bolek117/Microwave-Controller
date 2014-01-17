/*
 * keyboard.h
 *
 *  Author: Micha³ Witas
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEY_PORT	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

#define KEY_STARTPIN 0

typedef struct TKeyboard
{
	unsigned char halfPressed:1;
	unsigned char pressed:1;
	unsigned char blocked:1;

	unsigned char ticks;
	
} TKeyboard;

TKeyboard keyboard[K_MAX];

void initKeyboard();
void keyboardProcess();
void keyboardReset(TKeyboard *keyboard);
unsigned char keyboardCheckAnyPressed();

#endif /* KEYBOARD_H_ */