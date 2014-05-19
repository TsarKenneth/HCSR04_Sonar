/**************************************************************
 * Sample.c
 *
 * Author:	Kenneth Wong
 * Email:	kenneth.wongwx@gmail.com
 * Version:	1.0
 *
 * - Description -
 * This is a sample of how the library is used.
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

#define F_CPU 16000000
#include <avr/io.h>
#include <m2560/USART.h>
#include "HCSR04.h"

int main(void)
{
	char msg[10];
	InitSonar();
	StartSonar();
	InitUSART0();
	
    while(1)
    {
  		dtostrf(dist_cm, 5, 1, msg);
  		strcat(msg, "cm\r\n");
  		
  		Transmit(msg);
  		_delay_ms(1000);
    }
}
