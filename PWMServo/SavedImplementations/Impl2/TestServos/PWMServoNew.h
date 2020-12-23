#ifndef PWMServoNew_h
#define PWMServoNew_h

/*
  PWMServoNew.h - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Author: Jim Studt, jim@federated.com
  Copyright (c) 2007 David A. Mellis.  All right reserved.
  renamed to PWMServoNew by Mikal Hart
  ported to other chips by Paul Stoffregen
  Updated to handle all PWM pins for Mega, and changed to generalize methods - G. Gemmer

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#define PWM_SERVO_DEBUG 0
#include <inttypes.h>

//ATMega 168/328			Timer 1   Channels A,B
//ATMega 1280/2560		Timer 1,3,4,5   Channels A,B,C
//ATMega 644/644P			Timer 1 Channels A,B
//AT90USB162					Timer 1 channels A,B,C
//ATMega32U4					Timer 1 channels A,B,C, this also has a Timer 3 with channels A,B,C but only channel A gets outside on a teensy 2.0
//AT90USB646/1286			Timer 1,3 channels A,B,C

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) // Arduino
  #define SERVO_CPU_BOARD_TYPE1 0 
  #define SERVO_PIN_A 0 // Pin 9   PB1(OC1A/PCINT1)
  #define SERVO_PIN_B 1 // Pin 10  PB2(SS/OC1B/PCINT2)
  #define SERVO_MAX_NUM_PINS 2
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // Arduino Mega
  #define SERVO_CPU_BOARD_TYPE2 0 
  #define SERVO_PIN_A 0 // Pin 11 // (OC1A/PCINT5)PB5
  #define SERVO_PIN_B 1 // Pin 12 // (OC1B/PCINT6)PB6
  #define SERVO_PIN_C 2 // Pin 13 // (OC0A/OC1C/PCINT7)PB7
	#define SERVO_PIN_D 3 // Pin 5 // PE3(OC3A/AIN1)
	#define SERVO_PIN_E 4 // Pin 2 // PE4(OC3B/INT4)
	#define SERVO_PIN_F 5 // Pin 3 // PE5(OC3C/INT5)
	#define SERVO_PIN_G 6 // Pin 6 // PH3(OC4A)
	#define SERVO_PIN_H 7 // Pin 7 // PH4(OC4B)
	#define SERVO_PIN_I 8 // Pin 8 // PH5(OC4C)
  #define SERVO_PIN_J 9 // Pin 46 // PL3(OC5A)
  #define SERVO_PIN_K 10// Pin 45 // PL4(OC5B)
  #define SERVO_PIN_L 11// Pin 44 // PL5(OC5C)
  #define SERVO_MAX_NUM_PINS 12
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__) // Sanguino
  #define SERVO_CPU_BOARD_TYPE3 0 
  #define SERVO_PIN_A 0 // Pin 13
  #define SERVO_PIN_B 1 // Pin 12
  #define SERVO_MAX_NUM_PINS 2 
#elif defined(__AVR_AT90USB162__) // Teensy 1.0
  #define SERVO_CPU_BOARD_TYPE4 0 
  #define SERVO_PIN_A 0 // Pin 17
  #define SERVO_PIN_B 1 // Pin 18
  #define SERVO_PIN_C 2 // Pin 15
  #define SERVO_MAX_NUM_PINS 3 
#elif defined(__AVR_ATmega32U4__) // Teensy 2.0
  #define SERVO_CPU_BOARD_TYPE5 0 
  #define SERVO_PIN_A 0 // Pin 14
  #define SERVO_PIN_B 1 // Pin 15
  #define SERVO_PIN_C 2 // Pin 4
  #define SERVO_MAX_NUM_PINS 3 
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) // Teensy++
  #define SERVO_CPU_BOARD_TYPE6 0 
  #define SERVO_PIN_A 0 // Pin 25
  #define SERVO_PIN_B 1 // Pin 26
  #define SERVO_PIN_C 2 // Pin 27
  #define SERVO_MAX_NUM_PINS 3 
#else
  #define SERVO_CPU_BOARD_TYPE7 0 
  #define SERVO_PIN_A 0 // Pin 9
  #define SERVO_PIN_B 1 // Pin 10
  #define SERVO_MAX_NUM_PINS 2 
#endif

class PWMServoNew
{
  private:
  	struct servoHdwrCntrlInfoDef 
  	{
  		// Used to define which 16 bit PWM timer counter registers and set/clr masks are used for a given output
  		// This captures this information in a table instead of inline logic for 16 bit counters to generalize the operations
  		int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
  		// constructed correctly
  		uint8_t boardPinNumber; //actual pin number on board
  		//int16_t * tcntn;
  		volatile uint8_t * tccrnA;
  		volatile uint8_t * tccrnB;
  		//uint8_t * tccrnC;
  		volatile uint16_t * ocrnA;
  		volatile uint16_t * ocrnB;
  		//volatile uint16_t * ocrnC;
  		volatile uint8_t * timskn;
  		volatile uint16_t * icrn;
  		uint8_t attachTccrnaClrMsk;  // a bit = 1 gets cleared, a bit = 0 is left alone
  		uint8_t attachTccrnaSetMsk;  // a bit = 1 gets set, a bit = 0 is left alone
  		//uint16_t seizeTimerTccrnAClrMsk;
  		//uint16_t seizeTimerTccrnASetMsk;
  		//uint16_t seizeTimerTccrnBClrMsk;
  		//uint16_t seizeTimerTccrnBSetMsk;
  		uint8_t seizeTimerTimsknClrMsk;
  		uint8_t seizeTimerTimsknSetMsk;
  		uint8_t detachTccrnaClrMsk;
  		uint8_t detachTccrnaSetMsk;
  		volatile uint16_t * writeOcrnx; //register to write when write mthod called
  	};
  	
  	struct servoInfoDef 
  	{
  		servoInfoDef() : attached(false){}
  		bool attached;
  	};
  	
    uint8_t pin;
    int8_t  servoPinIndex; // index of the attached servo.  -1 means no servo attached for this object.  
    											 // Only one servo can be attached per PWMServoNew object.
    uint8_t angle;       // in degrees
    uint8_t min16;       // minimum pulse, 16uS units  (default is 34)
    uint8_t max16;       // maximum pulse, 16uS units, 0-4ms range (default is 150)
    static const servoHdwrCntrlInfoDef servoHdwrCntrlInfo[SERVO_MAX_NUM_PINS];
    servoHdwrCntrlInfoDef HdwrCntrlInfo;
    static servoInfoDef servoInfo[SERVO_MAX_NUM_PINS];
    
    void seizeTimer();
    void releaseTimer();
#ifdef PWM_SERVO_DEBUG
		void printServosAttached();
		void printTimerRegisterContents(int timer); // timer number, -1 for all
		void printAdrsValueHex(unsigned long address, unsigned long value);
		void printHdwrCntrlInfo(servoHdwrCntrlInfoDef &info);
#endif 

  public:
    PWMServoNew();
    uint8_t attach(int);
                             // pulse length for 0 degrees in microseconds, 544uS default
                             // pulse length for 180 degrees in microseconds, 2400uS default
    uint8_t attach(int, int, int);
                             // attach to a pin, sets pinMode, returns 0 on failure, won't
                             // position the servo until a subsequent write() happens
                             // Only works for 9 and 10.
    void detach();
    void write(int);         // specify the angle in degrees, 0 to 180
    uint8_t read();
    uint8_t attached();
};

#endif
