/*
 * keyboard.c
 *
 *  Author: Micha³ Witas
 */ 

 #include "common.h"

 void initKeyboard()
 {
	for (unsigned char i=0;i<K_MAX;++i)
	{
		KEY_DDR &= ~(1<<(KEY_STARTPIN+i));	// set as input
		KEY_PORT |= (1<<(KEY_STARTPIN+i));	// pull up to logic one

		keyboardReset(&keyboard[i]);
	}
 }

 void keyboardReset(TKeyboard *keyboard)
{
	keyboard->halfPressed = 0;
	keyboard->pressed = 0;
	keyboard->ticks = 0;
	keyboard->blocked = 0;
}

void keyboardProcess()
{
	for (unsigned char i=0;i<K_MAX;++i)
	{
		if (keyboard[i].blocked)
		{
			if (keyboard[i].ticks > 62)
			{
				keyboard[i].blocked = 0;
				keyboard[i].ticks = 0;
				return;
			}

			keyboard[i].ticks++;
			return;	
		}

		if (keyboard[i].halfPressed == 1 && (++keyboard[i].ticks) > 12)
		{
			keyboard[i].halfPressed = 0;
			keyboard[i].ticks = 0;

			if (!(KEY_PIN & 1<<(KEY_STARTPIN+i)))
			{
				keyboard[i].pressed = 1;
			}
		}
		else if (!(KEY_PIN & 1<<(KEY_STARTPIN+i)))
		{
			keyboard[i].halfPressed = 1;
		}
	}
}

unsigned char keyboardCheckAnyPressed()
{
	for (unsigned int i=0;i<K_MAX;++i)
	{
		if (keyboard[i].pressed)
			return 1;
	}

	return 0;
}

