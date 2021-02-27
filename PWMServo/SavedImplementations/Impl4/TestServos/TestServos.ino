#include <stdio.h> 
#include <string.h> 
//#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
//#else
//#include "wiring.h"
//#endif
#include "PWMServoNew.h"
#include <inttypes.h>

#define servoMaxPins 2
//#define servoMaxPins SERVO_MAX_NUM_PINS

// Instantiate all 12 servos a Mega can use
PWMServoNew myservos[servoMaxPins];

unsigned int pos = 0;
unsigned int servoNum = 0;
 
void setup() 
{ 
	Serial.begin(115200);
	myservos[0 ].attach (SERVO_PIN_I,536,1736 );  // Pin 8 

	myservos[0 ].attach (SERVO_PIN_A,800,2200 );  // Pin 11 
	myservos[1 ].attach (SERVO_PIN_B,800,2200 );  // Pin 12 
	myservos[2 ].attach (SERVO_PIN_C,800,2200 );  // Pin 13 
	myservos[3 ].attach (SERVO_PIN_D,800,2200 );  // Pin 5 
	myservos[4 ].attach (SERVO_PIN_E,800,2200 );  // Pin 2 
	myservos[5 ].attach (SERVO_PIN_F,800,2200 );  // Pin 3 
	myservos[6 ].attach (SERVO_PIN_G,800,2200 );  // Pin 6 
	myservos[7 ].attach (SERVO_PIN_H,800,2200 );  // Pin 7 
//	myservos[8 ].attach (SERVO_PIN_I,800,2200 );  // Pin 8 
	myservos[9 ].attach (SERVO_PIN_J,800,2200 );  // Pin 46 
	myservos[10].attach (SERVO_PIN_K,800,2200 );  // Pin 45 
	myservos[11].attach (SERVO_PIN_L,800,2200 );  // Pin 44 
  
} 

 
 
void loop() 
{ 
  myservos[servoNum].write(pos);
  if (0 == pos)
	{
		delay(1500);
	}
	else
	{
		delay(400);
	}

	pos += 90;
	if (pos <= 180)
	{
	}
	else
	{
		servoNum++;
		pos = 0;
		if (servoNum >= servoMaxPins)
		{
			servoNum = 0;
		}
	}
} 
