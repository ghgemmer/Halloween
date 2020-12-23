#if defined(PWM_SERVO_DEBUG)
	#include <stdio.h>
	#include <string.h>
#endif
#include <avr/interrupt.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "wiring.h"
#endif
#include "PWMServoNew.h"

/*
  PWMServoNew.cpp - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Author: Jim Studt, jim@federated.com
  Copyright (c) 2007 David A. Mellis.  All right reserved.
  renamed to PWMServoNew by Mikal Hart
  ported to other chips by Paul Stoffregen

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



PWMServoNew::servoInfoDef PWMServoNew::servoInfo[SERVO_MAX_NUM_PINS] = {};

const PWMServoNew::servoHdwrCntrlInfoDef PWMServoNew::servoHdwrCntrlInfo[SERVO_MAX_NUM_PINS] =

#if defined(SERVO_CPU_BOARD_TYPE1)
{
		{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		9, //uint8_t boardPinNumber; //actual pin number on board //Pin9  PB1(OC1A/PCINT1)
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		10, //uint8_t boardPinNumber; //actual pin number on board Pin 10 PB2(SS/OC1B/PCINT2)
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  }

};
#elif	defined(SERVO_CPU_BOARD_TYPE2)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		11, //uint8_t boardPinNumber; //actual pin number on board //Pin 11 (OC1A/PCINT5)PB5
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		12, //uint8_t boardPinNumber; //actual pin number on board Pin 12 // (OC1B/PCINT6)PB6
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		13, //uint8_t boardPinNumber; //actual pin number on board Pin 13 // (OC0A/OC1C/PCINT7)PB7
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1C0) | _BV(COM1C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1C, //uint16_t * writeOcrnx;
  },
{
		3, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		5, //uint8_t boardPinNumber; //actual pin number on board Pin 5 // PE3(OC3A/AIN1)
		//uint16_t * tcntn;
		&TCCR3A, //uint8_t * tccrnA;
		&TCCR3B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR3A, //uint16_t * ocrnA;
		&OCR3B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK3, //uint8_t * timskn;
		&ICR3, //uint16_t * icrn;
		_BV(COM3A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM3A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE3A) | _BV(OCIE3B) | _BV(OCIE3C) | _BV(TOIE3) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM3A0) | _BV(COM3A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR3A, //uint16_t * writeOcrnx;
  },
{
		4, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		2, //uint8_t boardPinNumber; //actual pin number on board Pin 2 // PE4(OC3B/INT4)
		//uint16_t * tcntn;
		&TCCR3A, //uint8_t * tccrnA;
		&TCCR3B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR3A, //uint16_t * ocrnA;
		&OCR3B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK3, //uint8_t * timskn;
		&ICR3, //uint16_t * icrn;
		_BV(COM3B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM3B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE3A) | _BV(OCIE3B) | _BV(OCIE3C) | _BV(TOIE3) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM3B0) | _BV(COM3B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR3B, //uint16_t * writeOcrnx;
  },
{
		5, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		3, //uint8_t boardPinNumber; //actual pin number on board Pin 3 // PE5(OC3C/INT5)
		//uint16_t * tcntn;
		&TCCR3A, //uint8_t * tccrnA;
		&TCCR3B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR3A, //uint16_t * ocrnA;
		&OCR3B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK3, //uint8_t * timskn;
		&ICR3, //uint16_t * icrn;
		_BV(COM3C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM3C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
	  (_BV(OCIE3A) | _BV(OCIE3B) | _BV(OCIE3C) | _BV(TOIE3) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM3C0) | _BV(COM3C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR3C, //uint16_t * writeOcrnx;
  },
{
		6, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		6, //uint8_t boardPinNumber; //actual pin number on board Pin 6 // PH3(OC4A)
		//uint16_t * tcntn;
		&TCCR4A, //uint8_t * tccrnA;
		&TCCR4B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR4A, //uint16_t * ocrnA;
		&OCR4B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK4, //uint8_t * timskn;
		&ICR4, //uint16_t * icrn;
		_BV(COM4A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM4A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE4A) | _BV(OCIE4B) | _BV(OCIE4C) | _BV(TOIE4) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM4A0) | _BV(COM4A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR4A, //uint16_t * writeOcrnx;
  },
{
		7, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		7, //uint8_t boardPinNumber; //actual pin number on board Pin 7 // PH4(OC4B)
		//uint16_t * tcntn;
		&TCCR4A, //uint8_t * tccrnA;
		&TCCR4B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR4A, //uint16_t * ocrnA;
		&OCR4B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK4, //uint8_t * timskn;
		&ICR4, //uint16_t * icrn;
		_BV(COM4B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM4B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE4A) | _BV(OCIE4B) | _BV(OCIE4C) | _BV(TOIE4) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM4B0) | _BV(COM4B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR4B, //uint16_t * writeOcrnx;
  },
{
		8, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		8, //uint8_t boardPinNumber; //actual pin number on board Pin 8 // PH5(OC4C)
		//uint16_t * tcntn;
		&TCCR4A, //uint8_t * tccrnA;
		&TCCR4B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR4A, //uint16_t * ocrnA;
		&OCR4B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK4, //uint8_t * timskn;
		&ICR4, //uint16_t * icrn;
		_BV(COM4C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM4C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE4A) | _BV(OCIE4B) | _BV(OCIE4C) | _BV(TOIE4) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM4C0) | _BV(COM4C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR4C, //uint16_t * writeOcrnx;
  },
{
		9, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		46, //uint8_t boardPinNumber; //actual pin number on board Pin 46 // PL3(OC5A)
		//uint16_t * tcntn;
		&TCCR5A, //uint8_t * tccrnA;
		&TCCR5B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR5A, //uint16_t * ocrnA;
		&OCR5B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK5, //uint8_t * timskn;
		&ICR5, //uint16_t * icrn;
		_BV(COM5A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM5A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE5A) | _BV(OCIE5B) | _BV(OCIE5C) | _BV(TOIE5) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM5A0) | _BV(COM5A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR5A, //uint16_t * writeOcrnx;
  },
{
		10, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		45, //uint8_t boardPinNumber; //actual pin number on board Pin 45 // PL4(OC5B)
		//uint16_t * tcntn;
		&TCCR5A, //uint8_t * tccrnA;
		&TCCR5B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR5A, //uint16_t * ocrnA;
		&OCR5B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK5, //uint8_t * timskn;
		&ICR5, //uint16_t * icrn;
		_BV(COM5B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM5B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE5A) | _BV(OCIE5B) | _BV(OCIE5C) | _BV(TOIE5) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM5B0) | _BV(COM5B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR5B, //uint16_t * writeOcrnx;
  },
{
		11, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		44, //uint8_t boardPinNumber; //actual pin number on board Pin 44 // PL5(OC5C)
		//uint16_t * tcntn;
		&TCCR5A, //uint8_t * tccrnA;
		&TCCR5B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR5A, //uint16_t * ocrnA;
		&OCR5B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK5, //uint8_t * timskn;
		&ICR5, //uint16_t * icrn;
		_BV(COM5C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM5C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE5A) | _BV(OCIE5B) | _BV(OCIE5C) | _BV(TOIE5) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM5C0) | _BV(COM5C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR5C, //uint16_t * writeOcrnx;
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE3)
{
		{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		13, //uint8_t boardPinNumber; //actual pin number on board //Pin13
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		12, //uint8_t boardPinNumber; //actual pin number on board Pin 12
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  }

};
#elif	defined(SERVO_CPU_BOARD_TYPE4)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		17, //uint8_t boardPinNumber; //actual pin number on board //Pin 17
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		18, //uint8_t boardPinNumber; //actual pin number on board Pin 18
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		15, //uint8_t boardPinNumber; //actual pin number on board Pin 15
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1C0) | _BV(COM1C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1C, //uint16_t * writeOcrnx;
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE5)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		14, //uint8_t boardPinNumber; //actual pin number on board //Pin 14
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		15, //uint8_t boardPinNumber; //actual pin number on board Pin 15
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		4, //uint8_t boardPinNumber; //actual pin number on board Pin 4
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1C0) | _BV(COM1C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1C, //uint16_t * writeOcrnx;
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE6)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		25, //uint8_t boardPinNumber; //actual pin number on board //Pin 25
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		26, //uint8_t boardPinNumber; //actual pin number on board Pin 26
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		27, //uint8_t boardPinNumber; //actual pin number on board Pin 27
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		&TIMSK1, //uint8_t * timskn;
		&ICR1, //uint16_t * icrn;
		_BV(COM1C0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1C1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1C0) | _BV(COM1C1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1C, //uint16_t * writeOcrnx;
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE7)
//#if defined(__AVR_ATmega8__)
//  TIMSK &= ~(_BV(TICIE1) | _BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) );
{
		{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		9, //uint8_t boardPinNumber; //actual pin number on board //Pin9  PB1(OC1A/PCINT1)
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		#if defined(__AVR_ATmega8__)
		&TIMSK, //uint8_t * timskn;
		#else
		&TIMSK1, //uint8_t * timskn;
		#endif
		&ICR1, //uint16_t * icrn;
		_BV(COM1A0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1A1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		#if defined(__AVR_ATmega8__)
		(_BV(TICIE1) | _BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ),
		#else
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		#endif
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1A0) | _BV(COM1A1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1A, //uint16_t * writeOcrnx;
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		10, //uint8_t boardPinNumber; //actual pin number on board Pin 10 PB2(SS/OC1B/PCINT2)
		//uint16_t * tcntn;
		&TCCR1A, //uint8_t * tccrnA;
		&TCCR1B, //uint8_t * tccrnB;
		//uint8_t * tccrnC;
		&OCR1A, //uint16_t * ocrnA;
		&OCR1B, //uint16_t * ocrnB;
		//uint16_t * ocrnC;
		#if defined(__AVR_ATmega8__)
		&TIMSK, //uint8_t * timskn;
		#else
		&TIMSK1, //uint8_t * timskn;
		#endif
		&ICR1, //uint16_t * icrn;
		_BV(COM1B0), //uint8_t attachTccrnaClrMsk;
		_BV(COM1B1), //uint8_t attachTccrnaSetMsk;
		//uint8_t seizeTimerTccrnAClrMsk;
		//uint8_t seizeTimerTccrnASetMsk;
		//uint8_t seizeTimerTccrnBClrMsk;
		//uint8_t seizeTimerTccrnBSetMsk;
		#if defined(__AVR_ATmega8__)
		(_BV(TICIE1) | _BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ),
		#else
		(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1) ), //uint8_t seizeTimerTimsknClrMsk;
		#endif
		0, //uint16_t seizeTimerTimsknSetMsk;
		(_BV(COM1B0) | _BV(COM1B1)), //uint8_t detachTccrnaClrMsk;
		0, //uint8_t detachTccrnaSetMsk;
		&OCR1B, //uint16_t * writeOcrnx;
  }
};
#endif


void PWMServoNew::seizeTimer()
{
  uint8_t oldSREG = SREG;

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Enter PWMServoNew::seizeTimer"));
  #endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Reg Contents Before"));
  printTimerRegisterContents(-1);
  #endif

  cli();
  *HdwrCntrlInfo.tccrnA = _BV(WGM11); /* Fast PWM, ICRn is top */
  *HdwrCntrlInfo.tccrnB = _BV(WGM13) | _BV(WGM12) /* Fast PWM, ICRn is top */
	| _BV(CS11) /* div 8 clock prescaler */;
  *HdwrCntrlInfo.ocrnA = 3000;
  *HdwrCntrlInfo.ocrnB = 3000;
  *HdwrCntrlInfo.icrn = clockCyclesPerMicrosecond()*(20000L/8);  // 20000 uS is a bit fast for the refresh, 20ms, but
                                                  // it keeps us from overflowing ICR1 at 20MHz clocks
                                                  // That "/8" at the end is the prescaler.
	*HdwrCntrlInfo.timskn = (*HdwrCntrlInfo.timskn & ~(HdwrCntrlInfo.seizeTimerTimsknClrMsk)) | HdwrCntrlInfo.seizeTimerTimsknSetMsk;

  SREG = oldSREG;  // undo cli()

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Reg Contents After"));
  printTimerRegisterContents(-1);
  #endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Exit PWMServoNew::seizeTimer"));
  #endif
}

void PWMServoNew::releaseTimer()
{
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Enter PWMServoNew::releaseTimer"));
  #endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Exit PWMServoNew::releaseTimer"));
  #endif

}

#define NO_ANGLE (0xff)

PWMServoNew::PWMServoNew() :  pin(0), servoPinIndex(-1), angle(NO_ANGLE)
{

	#if (SERVO_MAX_NUM_PINS > 0)
		HdwrCntrlInfo = servoHdwrCntrlInfo[0];  //as default
	#endif

}

uint8_t PWMServoNew::attach(int pinArg)
{
  return attach(pinArg, 544, 2400);
}

uint8_t PWMServoNew::attach(int pinArg, int min, int max)
{

	#if defined(PWM_SERVO_DEBUG)
	Serial.print(F("Enter PWMServoNew::attach"));
	Serial.print(F("int pinArg: "));
	Serial.print(pinArg);
	Serial.print(F(" min: "));
	Serial.print(min);
	Serial.print(F(" max: "));
	Serial.println(max);
  #endif

  if ((pinArg < 0) || (pinArg >= SERVO_MAX_NUM_PINS) || (servoPinIndex != -1) || (servoInfo[pinArg].attached))
  // pin_arg out of range or this object already has attached a servo or some other servo object already has attached that same servo.
  // servoPinIndex != -1 means this servo is attached, i.e. can't attach more than 1 servo for a given PWMServoNew object.
  {
  	return 0;
  }

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("attach Before - Reg Contents"));
  printTimerRegisterContents(-1);
  #endif

  HdwrCntrlInfo = servoHdwrCntrlInfo[pinArg];
  
	#if defined(PWM_SERVO_DEBUG)
  printHdwrCntrlInfo(HdwrCntrlInfo);
  #endif

  min16 = min / 16;
  max16 = max / 16;

	pin = HdwrCntrlInfo.boardPinNumber;
  angle = NO_ANGLE;
  digitalWrite(pin, LOW);
  pinMode(pin, OUTPUT);

	{
		volatile uint8_t * tccrna = HdwrCntrlInfo.tccrnA;
		bool timerAlreadySeized = false;
		for (int i = 0; i < SERVO_MAX_NUM_PINS; i++)
		{
			if ((servoInfo[i].attached) && (tccrna == servoHdwrCntrlInfo[i].tccrnA))
			// a servo is already attached that already uses the same timer we want to use for attaching this servo
			{
				timerAlreadySeized = true;
				break;
			}
		}
	  if (!timerAlreadySeized)
	  {
	  	seizeTimer();
	  }
	}
	*HdwrCntrlInfo.tccrnA = (*HdwrCntrlInfo.tccrnA & ~HdwrCntrlInfo.attachTccrnaClrMsk) | HdwrCntrlInfo.attachTccrnaSetMsk;
  servoPinIndex = pinArg;
	servoInfo[servoPinIndex].attached = true;

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("attach After - Reg Contents"));
  printTimerRegisterContents(-1);
  #endif
	#if defined(PWM_SERVO_DEBUG)
	printServosAttached();
	#endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Exit PWMServoNew::attach"));
  #endif

  return 1;
}

void PWMServoNew::detach()
{
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Enter PWMServoNew::detach"));
  #endif

  if (-1 == servoPinIndex)
  // Servo not attached
  {
  	return;
  }
  *HdwrCntrlInfo.tccrnA = (*HdwrCntrlInfo.tccrnA & ~HdwrCntrlInfo.detachTccrnaClrMsk) | HdwrCntrlInfo.detachTccrnaSetMsk;
  pinMode(pin, INPUT);
	{
		volatile uint8_t * tccrna = HdwrCntrlInfo.tccrnA;
		bool tccrnaUsedCount = 0;
		for (int i = 0; i < SERVO_MAX_NUM_PINS; i++)
		{
			if ((servoInfo[i].attached) && (tccrna == servoHdwrCntrlInfo[i].tccrnA))
			// a servo is attached that uses that timer.
			{
				tccrnaUsedCount++;
			}
		}
	  if (1 == tccrnaUsedCount)
	  // only this objects servo is using that timer (i.e. no other servo objects are using that timer
	  {
	  	releaseTimer();
	  }
	}
  servoInfo[servoPinIndex].attached = false;
	servoPinIndex = -1;

	#if defined(PWM_SERVO_DEBUG)
	printServosAttached();
	#endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Exit PWMServoNew::detach"));
  #endif
}

void PWMServoNew::write(int angleArg)
{
  uint16_t p;

  if (-1 == servoPinIndex)
  // Servo not attached
  {
  	return;
  }


  if (angleArg < 0) angleArg = 0;
  if (angleArg > 180) angleArg = 180;
  angle = angleArg;

  // bleh, have to use longs to prevent overflow, could be tricky if always a 16MHz clock, but not true
  // That 8L on the end is the TCNT1 prescaler, it will need to change if the clock's prescaler changes,
  // but then there will likely be an overflow problem, so it will have to be handled by a human.
  p = (min16*16L*clockCyclesPerMicrosecond() + (max16-min16)*(16L*clockCyclesPerMicrosecond())*angle/180L)/8L;
  *HdwrCntrlInfo.writeOcrnx = p;

  #if defined(PWM_SERVO_DEBUG)  
	Serial.print(F("PWMServoNew::write ServoIndex: "));
  Serial.println(servoPinIndex);
	Serial.print(F("PWMServoNew::write wrote to "));
	printAdrsValueHex((unsigned long)HdwrCntrlInfo.writeOcrnx, *HdwrCntrlInfo.writeOcrnx);
	Serial.println(F(""));
  #endif

}

uint8_t PWMServoNew::read()
{
  return angle;
}

uint8_t PWMServoNew::attached()
{
	uint8_t attached = 0;
  if (-1 != servoPinIndex)
  {
  	attached = 1;
  }
  return (attached);
}

#ifdef PWM_SERVO_DEBUG
void PWMServoNew::printServosAttached()
{
	for (int i = 0; i < SERVO_MAX_NUM_PINS; i++)
	{
		Serial.print(F("Servo Index:"));
		Serial.print(i);
		Serial.print(F(" Attached:"));
		Serial.println(servoInfo[i].attached );
	}
}
void PWMServoNew::printTimerRegisterContents(int timer) // timer number, -1 for all
{
	switch (timer)
	{
		case 1:
			Serial.print(F("Timer:"));
			Serial.println(timer);
			#ifdef TCCR1A
			Serial.print(F("TCCR1A:"));
			printAdrsValueHex((unsigned long)&TCCR1A, TCCR1A);
			Serial.println(F(""));
			#endif
			#ifdef TCCR1B
			Serial.print(F("TCCR1B:"));
			printAdrsValueHex((unsigned long)&TCCR1B, TCCR1B);
			Serial.println(F(""));
			#endif
			#ifdef OCR1A
			Serial.print(F("OCR1A:"));
			printAdrsValueHex((unsigned long)&OCR1A, OCR1A);
			Serial.println(F(""));
			#endif
			#ifdef OCR1B
			Serial.print(F("OCR1B:"));
			printAdrsValueHex((unsigned long)&OCR1B, OCR1B);
			Serial.println(F(""));
			#endif
			#ifdef OCR1C
			Serial.print(F("OCR1C:"));
			printAdrsValueHex((unsigned long)&OCR1C, OCR1C);
			Serial.println(F(""));
			#endif
			#ifdef TIMSK1
			Serial.print(F("TIMSK1:"));
			printAdrsValueHex((unsigned long)&TIMSK1, TIMSK1);
			Serial.println(F(""));
			#endif
			#ifdef ICR1
			Serial.print(F("ICR1:"));
			printAdrsValueHex((unsigned long)&ICR1, ICR1);
			Serial.println(F(""));
			#endif
			break;
		case 3:
			Serial.print(F("Timer:"));
			Serial.println(timer);
			#ifdef TCCR3A
			Serial.print(F("TCCR3A:"));
			printAdrsValueHex((unsigned long)&TCCR3A, TCCR3A);
			Serial.println(F(""));
			#endif
			#ifdef TCCR3B
			Serial.print(F("TCCR3B:"));
			printAdrsValueHex((unsigned long)&TCCR3B, TCCR3B);
			Serial.println(F(""));
			#endif
			#ifdef OCR3A
			Serial.print(F("OCR3A:"));
			printAdrsValueHex((unsigned long)&OCR3A, OCR3A);
			Serial.println(F(""));
			#endif
			#ifdef OCR3B
			Serial.print(F("OCR3B:"));
			printAdrsValueHex((unsigned long)&OCR3B, OCR3B);
			Serial.println(F(""));
			#endif
			#ifdef OCR3C
			Serial.print(F("OCR3C:"));
			printAdrsValueHex((unsigned long)&OCR3C, OCR3C);
			Serial.println(F(""));
			#endif
			#ifdef TIMSK3
			Serial.print(F("TIMSK3:"));
			printAdrsValueHex((unsigned long)&TIMSK3, TIMSK3);
			Serial.println(F(""));
			#endif
			#ifdef ICR3
			Serial.print(F("ICR3:"));
			printAdrsValueHex((unsigned long)&ICR3, ICR3);
			Serial.println(F(""));
			#endif
			break;
		case 4:
			Serial.print(F("Timer:"));
			Serial.println(timer);
			#ifdef TCCR4A
			Serial.print(F("TCCR4A:"));
			printAdrsValueHex((unsigned long)&TCCR4A, TCCR4A);
			Serial.println(F(""));
			#endif
			#ifdef TCCR4B
			Serial.print(F("TCCR4B:"));
			printAdrsValueHex((unsigned long)&TCCR4B, TCCR4B);
			Serial.println(F(""));
			#endif
			#ifdef OCR4A
			Serial.print(F("OCR4A:"));
			printAdrsValueHex((unsigned long)&OCR4A, OCR4A);
			Serial.println(F(""));
			#endif
			#ifdef OCR4B
			Serial.print(F("OCR4B:"));
			printAdrsValueHex((unsigned long)&OCR4B, OCR4B);
			Serial.println(F(""));
			#endif
			#ifdef OCR4C
			Serial.print(F("OCR4C:"));
			printAdrsValueHex((unsigned long)&OCR4C, OCR4C);
			Serial.println(F(""));
			#endif
			#ifdef TIMSK4
			Serial.print(F("TIMSK4:"));
			printAdrsValueHex((unsigned long)&TIMSK4, TIMSK4);
			Serial.println(F(""));
			#endif
			#ifdef ICR4
			Serial.print(F("ICR4:"));
			printAdrsValueHex((unsigned long)&ICR4, ICR4);
			Serial.println(F(""));
			#endif
			break;
		case 5:
			Serial.print(F("Timer:"));
			Serial.println(timer);
			#ifdef TCCR5A
			Serial.print(F("TCCR5A:"));
			printAdrsValueHex((unsigned long)&TCCR5A, TCCR5A);
			Serial.println(F(""));
			#endif
			#ifdef TCCR5B
			Serial.print(F("TCCR5B:"));
			printAdrsValueHex((unsigned long)&TCCR5B, TCCR5B);
			Serial.println(F(""));
			#endif
			#ifdef OCR5A
			Serial.print(F("OCR5A:"));
			printAdrsValueHex((unsigned long)&OCR5A, OCR5A);
			Serial.println(F(""));
			#endif
			#ifdef OCR5B
			Serial.print(F("OCR5B:"));
			printAdrsValueHex((unsigned long)&OCR5B, OCR5B);
			Serial.println(F(""));
			#endif
			#ifdef OCR5C
			Serial.print(F("OCR5C:"));
			printAdrsValueHex((unsigned long)&OCR5C, OCR5C);
			Serial.println(F(""));
			#endif
			#ifdef TIMSK5
			Serial.print(F("TIMSK5:"));
			printAdrsValueHex((unsigned long)&TIMSK5, TIMSK5);
			Serial.println(F(""));
			#endif
			#ifdef ICR5
			Serial.print(F("ICR5:"));
			printAdrsValueHex((unsigned long)&ICR5, ICR5);
			Serial.println(F(""));
			#endif
			break;
		case -1:
			printTimerRegisterContents(1);
			printTimerRegisterContents(3);
			printTimerRegisterContents(4);
			printTimerRegisterContents(5);
			break;
	}
}

void PWMServoNew::printAdrsValueHex(unsigned long address, unsigned long value)
{
	Serial.print(F("Adrs: "));
	Serial.print(address, HEX);
	Serial.print(F(" Val:"));
	Serial.println(value, HEX);
}


void PWMServoNew::printHdwrCntrlInfo(servoHdwrCntrlInfoDef &info)
{
	volatile uint16_t * temp;
	Serial.println(F("HdwrCntrlInfo:"));
	Serial.print(F("sizeof volatile unit16_t * :"));
	Serial.println(sizeof(temp));
	Serial.print(F("servoPinIndex: "));
	Serial.println(info.servoPinIndex);
	Serial.print(F("boardPinNumber: "));
	Serial.println(info.boardPinNumber);
	Serial.print(F("tccrnA: "));
	Serial.println((unsigned long)info.tccrnA, HEX);
	Serial.print(F("tccrnB: "));
	Serial.println((unsigned long)info.tccrnB, HEX);
	Serial.print(F("ocrnA: "));
	Serial.println((unsigned long)info.ocrnA, HEX);
	Serial.print(F("ocrnB: "));
	Serial.println((unsigned long)info.ocrnB, HEX);
	Serial.print(F("timskn: "));
	Serial.println((unsigned long)info.timskn, HEX);
	Serial.print(F("icrn: "));
	Serial.println((unsigned long)info.icrn, HEX);
	Serial.print(F("attachTccrnaClrMsk: "));
	Serial.println(info.attachTccrnaClrMsk, HEX);
	Serial.print(F("attachTccrnaSetMsk: "));
	Serial.println(info.attachTccrnaSetMsk, HEX);
	Serial.print(F("seizeTimerTimsknClrMsk: "));
	Serial.println(info.seizeTimerTimsknClrMsk, HEX);
	Serial.print(F("seizeTimerTimsknSetMsk: "));
	Serial.println(info.seizeTimerTimsknSetMsk, HEX);
	Serial.print(F("detachTccrnaClrMsk: "));
	Serial.println(info.detachTccrnaClrMsk, HEX);
	Serial.print(F("detachTccrnaSetMsk: "));
	Serial.println(info.detachTccrnaSetMsk, HEX);
	Serial.print(F("writeOcrnx: "));
	Serial.println((unsigned long)info.writeOcrnx, HEX);
}


#endif

