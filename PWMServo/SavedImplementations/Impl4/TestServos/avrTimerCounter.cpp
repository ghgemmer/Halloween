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
#include "program_memory_misc.h"
#include "PWMServoNew.h"


/*
  avrTimerCounter.cpp - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Author: G. Gemmer ghgemmer@gmail.com
  Copyright (c) 2020 G. Gemmer.  All right reserved.


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

const avrTimerCounter::HdwrBitDef avrTimerCounter::TimerHdwrBitDefsTable[MAX_NUM_TIMER_BITDEFS] PROGMEM =
#if defined(TIMER_CPU_BOARD_TYPE1)
{
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), 0},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), 0},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10)// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11)// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12)// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), 0},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), __BV(OCIE1B), 0},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), 0},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE2)
{
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), _BV(COM1C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), _BV(COM1C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), _BV(FOC1C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), _BV(OCIE1B), _BV(OCIE1C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), _BV(OCF1C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	},
	{ // TimerId3 bit defs
		1, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM3A0), _BV(COM3B0), _BV(COM3C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM3A1), _BV(COM3B1), _BV(COM3C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM30),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM31),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC3),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES3),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS30),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS31),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS32),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM32),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM33),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC3A),_BV(FOC3B), _BV(FOC3C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE3),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE3A), _BV(OCIE3B), _BV(OCIE3C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE3),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF3),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF3A),_BV(OCF3B), _BV(OCF3C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV3),// uint8_t tovBitMsk;  //reg tifr
	},
	{ // TimerId4 bit defs
		2, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM4A0), _BV(COM4B0), _BV(COM4C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM4A1), _BV(COM4B1), _BV(COM4C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM40),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM41),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC4),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES4),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS40),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS41),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS42),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM42),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM43),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC4A),_BV(FOC4B), _BV(FOC4C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE4),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE4A), _BV(OCIE4B), _BV(OCIE4C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE4),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF4),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF4A),_BV(OCF4B), _BV(OCF4C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV4),// uint8_t tovBitMsk;  //reg tifr
	},
	{ // TimerId5 bit defs
		3, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM5A0), _BV(COM5B0), _BV(COM5C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM5A1), _BV(COM5B1), _BV(COM5C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM50),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM51),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC5),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES5),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS50),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS51),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS52),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM52),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM53),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC5A),_BV(FOC5B), _BV(FOC5C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE5),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE5A), _BV(OCIE5B), _BV(OCIE5C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE5),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF5),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF5A),_BV(OCF5B), _BV(OCF5C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV5),// uint8_t tovBitMsk;  //reg tifr
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE3)
{
	{ // TimerId3 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), 0},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), 0},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), 0},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), __BV(OCIE1B), 0},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), 0},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE4)
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), _BV(COM1C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), _BV(COM1C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), _BV(FOC1C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), _BV(OCIE1B), _BV(OCIE1C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), _BV(OCF1C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE5)
{
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), _BV(COM1C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), _BV(COM1C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), _BV(FOC1C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), _BV(OCIE1B), _BV(OCIE1C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), _BV(OCF1C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	},
	{ // TimerId3 bit defs
		1, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM3A0), _BV(COM3B0), _BV(COM3C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM3A1), _BV(COM3B1), _BV(COM3C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM30),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM31),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC3),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES3),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS30),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS31),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS32),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM32),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM33),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC3A),_BV(FOC3B), _BV(FOC3C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE3),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE3A), _BV(OCIE3B), _BV(OCIE3C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE3),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF3),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF3A),_BV(OCF3B), _BV(OCF3C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV3),// uint8_t tovBitMsk;  //reg tifr
	},
};
#elif	defined(TIMER_CPU_BOARD_TYPE6)
{
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), _BV(COM1C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), _BV(COM1C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), _BV(FOC1C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), _BV(OCIE1B), _BV(OCIE1C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), _BV(OCF1C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	},
	{ // TimerId3 bit defs
		1, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM3A0), _BV(COM3B0), _BV(COM3C0)},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM3A1), _BV(COM3B1), _BV(COM3C1)},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM30),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM31),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC3),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES3),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS30),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS31),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS32),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM32),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM33),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC3A),_BV(FOC3B), _BV(FOC3C)},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE3),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE3A), _BV(OCIE3B), _BV(OCIE3C)},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE3),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF3),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF3A),_BV(OCF3B), _BV(OCF3C)},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV3),// uint8_t tovBitMsk;  //reg tifr
	},
};
#elif	defined(TIMER_CPU_BOARD_TYPE7)
	{ // TimerId1 bit defs
		0, // uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
		{_BV(COM1A0), _BV(COM1B0), 0},// uint8 com0BitMsk[MaxNumChannels]; //reg tccrA
		{_BV(COM1A1), _BV(COM1B1), 0},// uint8 com1BitMsk[MaxNumChannels]; //reg tccrA
		_BV(WGM10),// uint8_t wgm0BitMsk; //reg tccrA
		_BV(WGM11),// uint8_t wgm1BitMsk; //reg tccrA
		_BV(ICNC1),// uint8_t icncBitMsk; //reg tccrB
		_BV(ICES1),// uint8_t icesBitMsk; //reg tccrB
		_BV(CS10),// uint8_t cs0BitMsk; //reg tccrB
		_BV(CS11),// uint8_t cs1BitMsk; //reg tccrB
		_BV(CS12),// uint8_t cs2BitMsk; //reg tccrB
		_BV(WGM12),// uint8_t wgm2BitMsk; //reg tccrB
		_BV(WGM13),// uint8_t wgm3BitMsk; //reg tccrB
		{ _BV(FOC1A),_BV(FOC1B), 0},// uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
		_BV(ICIE1),// uint8_t icieBitMsk; //reg timsk
		{_BV(OCIE1A), __BV(OCIE1B), 0},// uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
		_BV(TOIE1),// uint8_t toieBitMsk; //reg timsk
		_BV(ICF1),// uint8_t icfBitMsk; //reg tifr
		{ _BV(OCF1A),_BV(OCF1B), 0},// uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
		_BV(TOV1),// uint8_t tovBitMsk;  //reg tifr
	}
};
#endif


const avrTimerCounter::HdwrCntrlInfoDef avrTimerCounter::TimerHdwrCntrlInfo[MAX_NUM_TIMER_COUNTERS] =

#if defined(TIMER_CPU_BOARD_TYPE1)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		2, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,NULL},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE2)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,&OCR1C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
	{
		TimerId3, // timerCounterIdsDef timerId;
		&TCCR3A, // volatile uint8_t * tccrA;
		&TCCR3B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR3A,&OCR3B,&OCR3C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK3, // volatile uint8_t * timsk;
		&ICR3, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		1 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
	{
		TimerId4, // timerCounterIdsDef timerId;
		&TCCR4A, // volatile uint8_t * tccrA;
		&TCCR4B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR4A,&OCR4B,&OCR4C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK4, // volatile uint8_t * timsk;
		&ICR4, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		2 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
	{
		TimerId5, // timerCounterIdsDef timerId;
		&TCCR5A, // volatile uint8_t * tccrA;
		&TCCR5B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR5A,&OCR5B,&OCR5C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK5, // volatile uint8_t * timsk;
		&ICR5, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		3 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  }
};
#elif	defined(TIMER_CPU_BOARD_TYPE3)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		2, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,NULL},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
	}
};
#elif	defined(TIMER_CPU_BOARD_TYPE4)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,&OCR1C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  }
};
#elif	defined(TIMER_CPU_BOARD_TYPE5)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,&OCR1C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
	{
		TimerId3, // timerCounterIdsDef timerId;
		&TCCR3A, // volatile uint8_t * tccrA;
		&TCCR3B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		1, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR3A,NULL,NULL},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK3, // volatile uint8_t * timsk;
		&ICR3, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		1 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
};
#elif	defined(TIMER_CPU_BOARD_TYPE6)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,&OCR1C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		0 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  },
	{
		TimerId3, // timerCounterIdsDef timerId;
		&TCCR3A, // volatile uint8_t * tccrA;
		&TCCR3B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		3, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR3A,&OCR3B,&OCR3C},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK3, // volatile uint8_t * timsk;
		&ICR3, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		1 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  }
};
#elif	defined(TIMER_CPU_BOARD_TYPE7)
{
	{
		TimerId1, // timerCounterIdsDef timerId;
		&TCCR1A, // volatile uint8_t * tccrA;
		&TCCR1B, // volatile uint8_t * tccrB;
		// //volatile uint8_t * tccrC;  //Not needed at this time
		// //volatile uint8_t * tifr;   //Not needed at this time
		2, // uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
		{&OCR1A,&OCR1B,NULL},// volatile uint16_t * ocr[MaxNumChannels];
		&TIMSK1, // volatile uint8_t * timsk;
		&ICR1, // volatile uint16_t * icr;
		// &TCNT1//volatile uint16_t * tcnt; //Not needed at this time
		// &GTTCR//volatile uint8_t * gttcr;  //Not needed at this time
		4 // int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
	}
};
#endif

// Instantiate the timers objects in the system
avrTimerCounter avrTimerCounter::timersObjects[MAX_NUM_TIMER_COUNTERS] =

#if	defined(TIMER_CPU_BOARD_TYPE1)
{
	avrTimerCounter(TimerId1)
};
#elif	defined(TIMER_CPU_BOARD_TYPE2)
{
	avrTimerCounter(TimerId1),
	avrTimerCounter(TimerId3),
	avrTimerCounter(TimerId4),
	avrTimerCounter(TimerId5)
};
#elif	defined(TIMER_CPU_BOARD_TYPE3)
{
	avrTimerCounter(TimerId1)
};
#elif	defined(TIMER_CPU_BOARD_TYPE4)
{
	avrTimerCounter(TimerId1)
};
#elif	defined(TIMER_CPU_BOARD_TYPE5)
{
	avrTimerCounter(TimerId1),
	avrTimerCounter(TimerId3)
};
#elif	defined(TIMER_CPU_BOARD_TYPE6)
{
	avrTimerCounter(TimerId1),
	avrTimerCounter(TimerId3)
};
#elif	defined(TIMER_CPU_BOARD_TYPE7)
{
	avrTimerCounter(TimerId1)
};
#endif


avrTimerCounter::avrTimerCounter(timerCounterIdsDef tmrId):  timerId(TimerIdNone), timerIndex(-1), bitDefsIndex(-1), numberOfChannels(0)
{
	for (int i = 0; i < MAX_NUM_TIMER_COUNTERS; i++)
	{
		if (TimerHdwrCntrlInfo[i].timerId == tmrId)
		{
			timerId = tmrId;
			timerIndex = i;
			bitDefsIndex = TimerHdwrCntrlInfo[i].bitDefsIndex;
			numberOfChannels = TimerHdwrCntrlInfo[i].numberOfChannels;
			for (int j = 0; j < MaxNumChannels; j++)
			{
				ocr[j] = TimerHdwrCntrlInfo[i].ocr[j];
			}
			break;
		}
	}
}

avrTimerCounter * avrTimerCounter::getAvrTimerCounter(timerCounterIdsDef tmrId)
{
	avrTimerCounter * tmr = NULL;
	for (int i = 0; i < MAX_NUM_TIMER_COUNTERS; i++)
	{
		if (timersObjects[i].timerId == tmrId)
		{
			tmr = &timersObjects[i];
			break;
		}
	}
	return tmr;
}

bool avrTimerCounter::initialize()
{
	HdwrCntrlInfoDef info = TimerHdwrCntrlInfo[timerIndex];
	*info.timsk = 0; // clear all timer interrupt enables
	*info.tccrB = 0; // Stop timer clock.
	*info.tccrA = 0; // All channels with compare output mode to normal to disconnect Compare output channels from output pins
	return true;
}

uint8_t avrTimerCounter::getNumberChannels()
{
	return numberOfChannels;
}

bool avrTimerCounter::setCompareOutputMode(channelDef channel,compareOutputModeDef mode )
{
	bool ok = false;
	if ((uint8_t)channel < numberOfChannels)
  {
  	ok = true;
  	HdwrBitDef hdwrBitDefsInfo;
  	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
		uint8_t com0BitMsk = hdwrBitDefsInfo.com0BitMsk[(unsigned int)channel];
		uint8_t com1BitMsk = hdwrBitDefsInfo.com1BitMsk[(unsigned int)channel];
		volatile uint8_t * tccrA = TimerHdwrCntrlInfo[timerIndex].tccrA;

		*tccrA = (*tccrA  &  ~(com0BitMsk | com1BitMsk)) | (mode & (1 << 0)? com0BitMsk : 0) | (mode & (1 << 1)? com1BitMsk : 0);
	}
	return ok;
}

void avrTimerCounter::setWaveformGenerationMode(waveformGenerationModeDef wgm)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t wgm0BitMsk = hdwrBitDefsInfo.wgm0BitMsk;
	uint8_t wgm1BitMsk = hdwrBitDefsInfo.wgm1BitMsk;
	uint8_t wgm2BitMsk = hdwrBitDefsInfo.wgm2BitMsk;
	uint8_t wgm3BitMsk = hdwrBitDefsInfo.wgm3BitMsk;
	volatile uint8_t * tccrA = TimerHdwrCntrlInfo[timerIndex].tccrA;
	volatile uint8_t * tccrB = TimerHdwrCntrlInfo[timerIndex].tccrB;

	*tccrA = (*tccrA  &  ~(wgm0BitMsk | wgm1BitMsk)) | (wgm & (1 << 0)? wgm0BitMsk : 0) | (wgm & (1 << 1)? wgm1BitMsk : 0);
	*tccrB = (*tccrB  &  ~(wgm2BitMsk | wgm3BitMsk)) | (wgm & (1 << 2)? wgm2BitMsk : 0) | (wgm & (1 << 3)? wgm3BitMsk : 0);
}

void avrTimerCounter::setInputNoiseCanceller(bool enable)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t icncBitMsk = hdwrBitDefsInfo.icncBitMsk;
	volatile uint8_t * tccrB = TimerHdwrCntrlInfo[timerIndex].tccrB;
	*tccrB = (*tccrB  &  ~(icncBitMsk )) | (enable ? icncBitMsk : 0);
}

void avrTimerCounter::setInputCaptureEdgeSelect(bool positiveEdge)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t icesBitMsk = hdwrBitDefsInfo.icesBitMsk;
	volatile uint8_t * tccrB = TimerHdwrCntrlInfo[timerIndex].tccrB;
	*tccrB = (*tccrB  &  ~(icesBitMsk )) | (positiveEdge ? icesBitMsk : 0);
}

void avrTimerCounter::setInputClockSelect(inputClockSelectDef select)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t cs0BitMsk = hdwrBitDefsInfo.cs0BitMsk;
	uint8_t cs1BitMsk = hdwrBitDefsInfo.cs1BitMsk;
	uint8_t cs2BitMsk = hdwrBitDefsInfo.cs2BitMsk;
	volatile uint8_t * tccrB = TimerHdwrCntrlInfo[timerIndex].tccrB;

	*tccrB = (*tccrB  &  ~(cs0BitMsk | cs1BitMsk | cs2BitMsk)) | (select & (1 << 0)? cs0BitMsk : 0)| (select & (1 << 1)? cs1BitMsk : 0) | (select & (1 << 2)? cs2BitMsk : 0);
}

// not needed at this time
//bool avrTimerCounter::forceOutputCompare(channelDef channel)
//{
//	bool ok = false;
//	if ((uint8_t)channel < numberOfChannels)
//  {
//  	ok = true;
//	HdwrBitDef hdwrBitDefsInfo;
//	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
//		uint8_t focBitMsk = hdwrBitDefsInfo.focBitMsk[(unsigned int)channel];
//		volatile uint8_t * tccrC = TimerHdwrCntrlInfo[timerIndex].tccrC;
//
//		*tccrC = *tccrC | focBitMsk;
//	}
//	return ok;
//}

bool avrTimerCounter::setOutputCompareReg(channelDef channel, uint16_t val)
{
	bool ok = false;
	if ((uint8_t)channel < numberOfChannels)
  {
  	ok = true;
		volatile uint16_t * ocr = TimerHdwrCntrlInfo[timerIndex].ocr[(unsigned int)channel];

		*ocr = val;
	}
	return ok;

}

void avrTimerCounter::setInputCaptureReg(uint16_t val)
{
	volatile uint16_t * icr = TimerHdwrCntrlInfo[timerIndex].icr;

	*icr = val;
}

void avrTimerCounter::clrAllInterruptEnables()
{
	volatile uint8_t * timsk = TimerHdwrCntrlInfo[timerIndex].timsk;
	*timsk = 0; // assume 0 is disabled for all cpus and all bits are interrupt enables
}

void avrTimerCounter::setInputCaptureIntEnable(bool enable)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t icieBitMsk = hdwrBitDefsInfo.icieBitMsk;
	volatile uint8_t * timsk = TimerHdwrCntrlInfo[timerIndex].timsk;
	*timsk = (*timsk  &  ~(icieBitMsk )) | (enable ? icieBitMsk : 0);
}

bool avrTimerCounter::setOutputCompareIntEnable(channelDef channel, bool enable)
{
	bool ok = false;
	if ((uint8_t)channel < numberOfChannels)
  {
  	ok = true;
		HdwrBitDef hdwrBitDefsInfo;
		GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
		uint8_t ocieBitMsk = hdwrBitDefsInfo.ocieBitMsk[(unsigned int)channel];
		volatile uint8_t * timsk = TimerHdwrCntrlInfo[timerIndex].timsk;

		*timsk = (*timsk &  ~(ocieBitMsk )) | (enable ? ocieBitMsk : 0);
	}
	return ok;
}

void avrTimerCounter::setTimerOverflowIntEnable(bool enable)
{
	HdwrBitDef hdwrBitDefsInfo;
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, hdwrBitDefsInfo);
	uint8_t toieBitMsk = hdwrBitDefsInfo.toieBitMsk;
	volatile uint8_t * timsk = TimerHdwrCntrlInfo[timerIndex].timsk;
	*timsk = (*timsk  &  ~(toieBitMsk )) | (enable ? toieBitMsk : 0);
}

#ifdef AVR_TIMER_COUNTER_DEBUG
void avrTimerCounter::printTimerRegisterContents()
{
	printTimerRegisterContents(timerId);
}

void avrTimerCounter::printTimerRegisterContents(timerCounterIdsDef tmrId)
{
	switch (tmrId)
	{
		case TimerId1:
			Serial.print(F("Timer:"));
			Serial.println(tmrId);
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
		case TimerId3:
			Serial.print(F("Timer:"));
			Serial.println(tmrId);
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
		case TimerId4:
			Serial.print(F("Timer:"));
			Serial.println(tmrId);
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
		case TimerId5:
			Serial.print(F("Timer:"));
			Serial.println(tmrId);
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
		case TimerIdAll:
			printTimerRegisterContents(TimerId1);
			printTimerRegisterContents(TimerId3);
			printTimerRegisterContents(TimerId4);
			printTimerRegisterContents(TimerId5);
			break;
	}
}

void avrTimerCounter::printAdrsValueHex(unsigned long address, unsigned long value)
{
	Serial.print(F("Adrs: "));
	Serial.print(address, HEX);
	Serial.print(F(" Val:"));
	Serial.println(value, HEX);
}


void avrTimerCounter::printHdwrCntrlInfo()
{
	volatile uint16_t * temp;
	HdwrCntrlInfoDef info = TimerHdwrCntrlInfo[timerIndex];
	HdwrBitDef bitInfo;
  GET_PROGRAM_MEMORY_ARRAY_ENTRY(TimerHdwrBitDefsTable, bitDefsIndex, bitInfo);
	Serial.println(F("Timer HdwrCntrlInfo:"));
	Serial.print(F("avrTimerCounter::timerId  "));
	Serial.println(timerId);
	Serial.print(F("avrTimerCounter::timerIndex: "));
	Serial.println(timerIndex);
	Serial.print(F("TimerHdwrCntrlInfo[timerIndex].timerId: "));
	Serial.println((unsigned long)info.timerId);
	Serial.print(F("sizeof volatile unit16_t * :"));
	Serial.println(sizeof(temp));
	Serial.print(F("tccrnA: "));
	Serial.println((unsigned long)info.tccrA, HEX);
	Serial.print(F("tccrnB: "));
	Serial.println((unsigned long)info.tccrB, HEX);
	Serial.print(F("numberOfChannels: "));
	Serial.println((unsigned long)info.numberOfChannels, HEX);
	Serial.print(F("ocrnA: "));
	Serial.println((unsigned long)info.ocr[(unsigned int)ChanA], HEX);
	Serial.print(F("ocrnB: "));
	Serial.println((unsigned long)info.ocr[(unsigned int)ChanB], HEX);
	Serial.print(F("ocrnC: "));
	Serial.println((unsigned long)info.ocr[(unsigned int)ChanC], HEX);
	Serial.print(F("timskn: "));
	Serial.println((unsigned long)info.timsk, HEX);
	Serial.print(F("icrn: "));
	Serial.println((unsigned long)info.icr, HEX);
	Serial.print(F("bitDefsIndex: "));
	Serial.println((unsigned long)info.bitDefsIndex, HEX);
	Serial.print(F("bitDefsIndex: "));
	Serial.println(F("Timer HdwrBitDef Info: "));
	Serial.println((unsigned long)bitInfo.index, HEX);
	for(int i = 0; i < MaxNumChannels; i++)
	{
		Serial.print(F("Channel: "));
		Serial.print((unsigned long)i, HEX);
		Serial.print(F(" com0BitMsk: "));
		Serial.println((unsigned long)bitInfo.com0BitMsk[i], HEX);
		Serial.print(F("Channel: "));
		Serial.print((unsigned long)i, HEX);
		Serial.print(F(" com1BitMsk: "));
		Serial.println((unsigned long)bitInfo.com1BitMsk[i], HEX);
	}
	Serial.print(F("wgm0BitMsk: "));
	Serial.println((unsigned long)bitInfo.wgm0BitMsk, HEX);
	Serial.print(F("wgm1BitMsk: "));
	Serial.println((unsigned long)bitInfo.wgm1BitMsk, HEX);
	Serial.print(F("icncBitMsk: "));
	Serial.println((unsigned long)bitInfo.icncBitMsk, HEX);
	Serial.print(F("icesBitMsk: "));
	Serial.println((unsigned long)bitInfo.icesBitMsk, HEX);
	Serial.print(F("cs0BitMsk: "));
	Serial.println((unsigned long)bitInfo.cs0BitMsk, HEX);
	Serial.print(F("cs1BitMsk: "));
	Serial.println((unsigned long)bitInfo.cs1BitMsk, HEX);
	Serial.print(F("cs2BitMsk: "));
	Serial.println((unsigned long)bitInfo.cs2BitMsk, HEX);
	Serial.print(F("wgm2BitMsk: "));
	Serial.println((unsigned long)bitInfo.wgm2BitMsk, HEX);
	Serial.print(F("wgm3BitMsk: "));
	Serial.println((unsigned long)bitInfo.wgm3BitMsk, HEX);
	for(int i = 0; i < MaxNumChannels; i++)
	{
		Serial.print(F("Channel: "));
		Serial.print((unsigned long)i, HEX);
		Serial.print(F(" focBitMsk: "));
		Serial.println((unsigned long)bitInfo.focBitMsk[i], HEX);
	}
	Serial.print(F("icieBitMsk: "));
	Serial.println((unsigned long)bitInfo.icieBitMsk, HEX);
	for(int i = 0; i < MaxNumChannels; i++)
	{
		Serial.print(F("Channel: "));
		Serial.print((unsigned long)i, HEX);
		Serial.print(F(" ocieBitMsk: "));
		Serial.println((unsigned long)bitInfo.ocieBitMsk[i], HEX);
	}
	Serial.print(F("toieBitMsk: "));
	Serial.println((unsigned long)bitInfo.toieBitMsk, HEX);
	Serial.print(F("icfBitMsk: "));
	Serial.println((unsigned long)bitInfo.icfBitMsk, HEX);
	for(int i = 0; i < MaxNumChannels; i++)
	{
		Serial.print(F("Channel: "));
		Serial.print((unsigned long)i, HEX);
		Serial.print(F(" ocfBitMsk: "));
		Serial.println((unsigned long)bitInfo.ocfBitMsk[i], HEX);
	}
	Serial.print(F("tovBitMsk: "));
	Serial.println((unsigned long)bitInfo.tovBitMsk, HEX);
}

#endif

