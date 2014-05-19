/**************************************************************
 * HCSR04.h
 *
 * Author:	Kenneth Wong
 * Email:	kenneth.wongwx@gmail.com
 * Version:	1.0
 *
 * - Description -
 * This library is created for HC-SR04 Ultrasonic Proximity
 * sensor and verified on Atmel Atmega 2560 micro controller.
 *
 * - Copyrights and Permissions -
 * Author retains all intellectual property (IP) rights to this
 * document. Users, however, have the permission to use, modify
 * and/or distribute this document for any non-commercial
 * purposes. Please retain this credit during use. If in doubt,
 * please feel free to contact the author at the e-mail address
 * provided above.
 *
 * Finally, have fun with it! :)
 ***************************************************************/

#ifndef _HCSR04_H_
#define _HCSR04_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define START_TIMER1	{TCCR1B |= 0x03;}
#define STOP_TIMER1		{TCCR1B &= ~(0x07);}
#define RESET_TIMER1	{TCNT1 = 0;}
#define TRIGGER			{PORTH |= 0x20; _delay_us(10); PORTH &= ~(0x20);}

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

static short rcvEcho;
static int timerCount;
static double dist_cm;

ISR(TIMER3_COMPA_vect)
{
	dist_cm = (double) (timerCount << 2) / 56;
	TRIGGER;
}

ISR(INT0_vect)
{
	if (rcvEcho == TRUE)
	{
		STOP_TIMER1;
		timerCount = TCNT1;
		RESET_TIMER1;
		rcvEcho = FALSE;
	} else if (rcvEcho == FALSE)
	{
		START_TIMER1;
		rcvEcho = TRUE;
	}
}

void InitSonar()
{
	/****Global Variables****/
	rcvEcho = FALSE;
	timerCount = 0;
	dist_cm = 0.0;
	
	/****Trigger****/
	DDRH |= 0x20;
	
	/****16-Bit Timer 3****/
	TCCR3A &= ~(0xC3);
	TCCR3A |= 0x40;
	TCCR3B &= ~(0x1F);
	TCCR3B |= 0x08;
	TCNT3 = 0;
	OCR3A = 3125;
	TIMSK3 |= 0x02;
	
	/****External Interrupt 0****/
	DDRD &= ~(0x01);
	EIMSK |= 0x01;
	EICRA &= ~(0x02);
	EICRA |= 0x01;
	
	/****16-bit Counter 1****/
	TCCR1A &= ~(0xC3);
	TCCR1B &= ~(0x1F);
	RESET_TIMER1;
	
	sei();
}

void StartSonar()
{
	TCCR3B |= 0x04;
	TRIGGER;
}

void StopSonar()
{
	TCCR3B &= ~(0x07);
}

#endif /* _HCSR04_H_ */
