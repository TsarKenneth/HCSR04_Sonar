HCSR04_Sonar
============

Author:		Kenneth Wong
Email:		kenneth.wongwx@gmail.com
Version:	1.0

- Description -
This library is created for HC-SR04 Ultrasonic Proximity
sensor and verified on Atmel Atmega 2560 micro controller.

Port mappings are as follows:
	Atmega Port			| Sensor Pin
	PORT H [5]			| TRIG
	PORT D [0] (INT0)	| ECHO
Timers used:
	Timer 1	- Measures the duration of echo.
	Timer 3 - Maintains period of 50ms.

Once initialized, the sensor will be triggered in periods
of 50ms. Distance, in cm, will be available for reading
100ms from initialization via the variable "dist_cm".

- Copyrights and Permissions -
Author retains all intellectual property (IP) rights to this 
document. Users, however, have the permission to use, modify 
and/or distribute this document for any non-commercial 
purposes. Please retain this credit during use. If in doubt, 
please feel free to contact the author at the e-mail address 
provided above.
 
Finally, have fun with it! :)
	
- Functions -
InitSonar()
Initializes the proximity sensor.

StartSonar()
Starts the proximity sensing routine.

StopSonar()
Stops the proximity sensing routine.

