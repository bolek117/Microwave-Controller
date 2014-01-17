/*
 * led7segment.h
 *
 *  Author: Micha³ Witas
 */ 


#ifndef LED7SEGMENT_H_
#define LED7SEGMENT_H_

#define LEDSEG_PORT PORTD
#define LEDSEG_DDR DDRD
#define LEDCYF_PORT PORTC
#define LEDCYF_DDR DDRC

#define LED_A 0
#define LED_B 1
#define LED_C 2
#define LED_D 3
#define LED_E 4
#define LED_F 5
#define LED_G 6
#define LED_DOT 7

#define LED_1 0
#define LED_2 1
#define LED_3 2
#define LED_4 3

void test(void);
void init7Segment(void);
void sendTo7seg(unsigned char* str);

#endif /* LED7SEGMENT_H_ */