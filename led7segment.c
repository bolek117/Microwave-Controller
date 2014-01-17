/*
 * led7segment.c
 *
 *  Author: Micha³ Witas
 */ 

 #include "common.h"

 unsigned char digits[] = {
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_C)|(1<<LED_D)|(1<<LED_E)|(1<<LED_F)),
	 ~((1<<LED_B)|(1<<LED_C)),
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_G)|(1<<LED_D)|(1<<LED_E)),
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_G)|(1<<LED_C)|(1<<LED_D)),
	 ~((1<<LED_B)|(1<<LED_C)|(1<<LED_F)|(1<<LED_G)),
	 ~((1<<LED_A)|(1<<LED_C)|(1<<LED_D)|(1<<LED_F)|(1<<LED_G)),
	 ~((1<<LED_A)|(1<<LED_C)|(1<<LED_D)|(1<<LED_E)|(1<<LED_F)|(1<<LED_G)),
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_C)),
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_C)|(1<<LED_D)|(1<<LED_E)|(1<<LED_F)|(1<<LED_G)),
	 ~((1<<LED_A)|(1<<LED_B)|(1<<LED_C)|(1<<LED_D)|(1<<LED_F)|(1<<LED_G)),
	 0xFF
 };

 void init7Segment()
 {
	LEDCYF_DDR = (1<<LED_1)|(1<<LED_2)|(1<<LED_3)|(1<<LED_4);
	LEDSEG_DDR = 0xFF;
 }

 void sendTo7seg(unsigned char* str)
 {
	static unsigned char dig = 0;
	unsigned char ch;

	if (dig > 3) dig = 0;

	LEDCYF_PORT |= ((1<<LED_1)|(1<<LED_2)|(1<<LED_3)|(1<<LED_4));
	LEDCYF_PORT &= ~(1<<(LED_1+dig));

	ch = str[(3-dig)]-'0';
	if (ch == 10)
	{
		LEDSEG_PORT = digits[0];
		str[(3-dig)] = '0';
	}
	if (ch < 0 || ch > 9)
		LEDSEG_PORT = digits[10];
	else
	{
		if (dig == 2) LEDSEG_PORT = (digits[ch]&(~(1<<LED_DOT)));
		else LEDSEG_PORT = (digits[ch]);
	}

	dig++;
 }