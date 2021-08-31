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
#include "program_memory_misc.h"


/*
  PWMServoNew.cpp - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Author: Jim Studt, jim@federated.com
  Copyright (c) 2007 David A. Mellis.  All right reserved.
  renamed to PWMServoNew by Mikal Hart
  ported to other chips by Paul Stoffregen
  Updated to all 16 bit timer PWM pins available on avr hardware by G. Gemmer

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
	
const PWMServoNew::servoHdwrCntrlInfoDef PWMServoNew::servoHdwrCntrlInfo[SERVO_MAX_NUM_PINS] PROGMEM =

#if defined(SERVO_CPU_BOARD_TYPE1)
{
		{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		9, //uint8_t boardPinNumber; //actual pin number on board //Pin9  PB1(OC1A/PCINT1)
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		10, //uint8_t boardPinNumber; //actual pin number on board Pin 10 PB2(SS/OC1B/PCINT2)
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  }

};
#elif	defined(SERVO_CPU_BOARD_TYPE2)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		11, //uint8_t boardPinNumber; //actual pin number on board //Pin 11 (OC1A/PCINT5)PB5
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		12, //uint8_t boardPinNumber; //actual pin number on board Pin 12 // (OC1B/PCINT6)PB6
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		13, //uint8_t boardPinNumber; //actual pin number on board Pin 13 // (OC0A/OC1C/PCINT7)PB7
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanC
  },
{
		3, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		5, //uint8_t boardPinNumber; //actual pin number on board Pin 5 // PE3(OC3A/AIN1)
		avrTimerCounter::TimerId3,
		avrTimerCounter::ChanA
  },
{
		4, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		2, //uint8_t boardPinNumber; //actual pin number on board Pin 2 // PE4(OC3B/INT4)
		avrTimerCounter::TimerId3,
		avrTimerCounter::ChanB
 },
{
		5, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		3, //uint8_t boardPinNumber; //actual pin number on board Pin 3 // PE5(OC3C/INT5)
		avrTimerCounter::TimerId3,
		avrTimerCounter::ChanC
  },
{
		6, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		6, //uint8_t boardPinNumber; //actual pin number on board Pin 6 // PH3(OC4A)
		avrTimerCounter::TimerId4,
		avrTimerCounter::ChanA
  },
{
		7, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		7, //uint8_t boardPinNumber; //actual pin number on board Pin 7 // PH4(OC4B)
		avrTimerCounter::TimerId4,
		avrTimerCounter::ChanB
  },
{
		8, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		8, //uint8_t boardPinNumber; //actual pin number on board Pin 8 // PH5(OC4C)
		avrTimerCounter::TimerId4,
		avrTimerCounter::ChanC
  },
{
		9, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		46, //uint8_t boardPinNumber; //actual pin number on board Pin 46 // PL3(OC5A)
		avrTimerCounter::TimerId5,
		avrTimerCounter::ChanA
  },
{
		10, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		45, //uint8_t boardPinNumber; //actual pin number on board Pin 45 // PL4(OC5B)
		avrTimerCounter::TimerId5,
		avrTimerCounter::ChanB
  },
{
		11, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		44, //uint8_t boardPinNumber; //actual pin number on board Pin 44 // PL5(OC5C)
		avrTimerCounter::TimerId5,
		avrTimerCounter::ChanC
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE3)
{
		{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		13, //uint8_t boardPinNumber; //actual pin number on board //Pin13
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		12, //uint8_t boardPinNumber; //actual pin number on board Pin 12
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  }

};
#elif	defined(SERVO_CPU_BOARD_TYPE4)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		17, //uint8_t boardPinNumber; //actual pin number on board //Pin 17
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		18, //uint8_t boardPinNumber; //actual pin number on board Pin 18
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		15, //uint8_t boardPinNumber; //actual pin number on board Pin 15
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanC
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE5)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		14, //uint8_t boardPinNumber; //actual pin number on board //Pin 14
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		15, //uint8_t boardPinNumber; //actual pin number on board Pin 15
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		4, //uint8_t boardPinNumber; //actual pin number on board Pin 4
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanC
  }
};
#elif	defined(SERVO_CPU_BOARD_TYPE6)
{
	{
		0, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		25, //uint8_t boardPinNumber; //actual pin number on board //Pin 25
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		26, //uint8_t boardPinNumber; //actual pin number on board Pin 26
		//uint16_t * tcntn;
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  },
{
		2, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		27, //uint8_t boardPinNumber; //actual pin number on board Pin 27
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanC
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
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanA
  },
	{
		1, //int8_t servoPinIndex;  // Used to verify array index entry matches SERVO_PIN_<n> used as index.  Verifies constant tables
		// constructed correctly
		10, //uint8_t boardPinNumber; //actual pin number on board Pin 10 PB2(SS/OC1B/PCINT2)
		avrTimerCounter::TimerId1,
		avrTimerCounter::ChanB
  }
};
#endif

int8_t  PWMServoNew::getServoPinIndex(uint8_t pin)
{
	int8_t index = -1;
	for (int8_t i = 0; i < SERVO_MAX_NUM_PINS; i++)
	{
		servoHdwrCntrlInfoDef hdwrInfo;
		GET_PROGRAM_MEMORY_ARRAY_ENTRY(servoHdwrCntrlInfo, i, hdwrInfo);
		if (pin == hdwrInfo.boardPinNumber)
		{
			index = i;
			break;
		}
	}
	return index;
}

void PWMServoNew::seizeTimer()
{
  uint8_t oldSREG = SREG;

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Enter PWMServoNew::seizeTimer"));
  #endif
	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Reg Contents Before"));
  timerPtr->printTimerRegisterContents(avrTimerCounter::TimerIdAll);
  #endif

  cli();
  timerPtr->initialize();
  timerPtr->clrAllInterruptEnables();
  timerPtr->setWaveformGenerationMode(avrTimerCounter::WgmFastPwmIcrTop);
  timerPtr->setInputClockSelect(avrTimerCounter::csFromPrescalerDiv8);  	
	for (uint8_t chan = 0; chan < timerPtr->getNumberChannels(); chan++)
	{
		timerPtr->setOutputCompareReg((avrTimerCounter::channelDef)chan, 3000);
	}
	timerPtr->setInputCaptureReg(clockCyclesPerMicrosecond()*(20000L/8));  // 20000 uS is a bit fast for the refresh, 20ms, but
                                                  // it keeps us from overflowing ICR1 at 20MHz clocks
                                                  // That "/8" at the end is the prescaler.
//	timerPtr->setInputCaptureIntEnable(false);
//	for (uint8_t chan = 0; chan < timerPtr->getNumberChannels(); chan++)
//	{
//		timerPtr->setOutputCompareIntEnable((avrTimerCounter::channelDef)chan, false);
//	}
//	
//	timerPtr->setTimerOverflowIntEnable(false);                                                 

  SREG = oldSREG;  // undo cli()

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("Reg Contents After"));
  timerPtr->printTimerRegisterContents(avrTimerCounter::TimerIdAll);
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

PWMServoNew::PWMServoNew() :  pin(0), servoPinIndex(-1), angle(NO_ANGLE), timerPtr(NULL)
{
}

uint8_t PWMServoNew::attach(int pinArg)
{
  return attach(pinArg, 544, 2400);
}

uint8_t PWMServoNew::attach(int pinArg, int min, int max, int minAngleDeg, int maxAngleDeg)
{

	#if defined(PWM_SERVO_DEBUG)
	Serial.print(F("Enter PWMServoNew::attach"));
	Serial.print(F("int pinArg: "));
	Serial.print(pinArg);
	Serial.print(F(" min: "));
	Serial.print(min);
	Serial.print(F(" max: "));
	Serial.print(max);
	Serial.print(F(" min angle: "));
	Serial.print(minAngleDeg);
	Serial.print(F(" max angle: "));
	Serial.println(maxAngleDeg);
  #endif

	int8_t newIndex = getServoPinIndex(pinArg);
  if ((newIndex < 0) || (newIndex >= SERVO_MAX_NUM_PINS) || (servoPinIndex != -1) || (servoInfo[newIndex].attached))
  // pin_arg not valid or this object already has attached a servo or some other servo object already has attached that same servo.
  // servoPinIndex != -1 means this servo is attached, i.e. can't attach more than 1 servo for a given PWMServoNew object.
  {
		#if defined(PWM_SERVO_DEBUG)
		Serial.print(F(" Attach failed Exit: newIndex: "));
		Serial.println(newIndex);
		Serial.print(F(" servoPinIndex: "));
		Serial.println(servoPinIndex);
		Serial.print(F(" servoInfo[newIndex].attached: "));
		Serial.println(servoInfo[newIndex].attached);
  	#endif
  	
  	return 0;
  }
  
	GET_PROGRAM_MEMORY_ARRAY_ENTRY(servoHdwrCntrlInfo, newIndex, HdwrCntrlInfo);
	//HdwrCntrlInfo = servoHdwrCntrlInfo[newIndex];
	#if defined(PWM_SERVO_DEBUG)
  printHdwrCntrlInfo(HdwrCntrlInfo);
  #endif
	  

	timerPtr = avrTimerCounter::getAvrTimerCounter(HdwrCntrlInfo.timerId); // get ptr to timer object

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("attach Before - Reg Contents"));
  timerPtr->printTimerRegisterContents(avrTimerCounter::TimerIdAll);
  #endif
  
	#if defined(PWM_SERVO_DEBUG)
  timerPtr->printHdwrCntrlInfo();
  #endif

  min16 = min / 16;
  max16 = max / 16;
  _minAngleDeg = minAngleDeg;
  _maxAngleDeg = maxAngleDeg;

	pin = pinArg;
  angle = NO_ANGLE;
  digitalWrite(pin, LOW);
  pinMode(pin, OUTPUT);

	{
		avrTimerCounter::timerCounterIdsDef tmId = HdwrCntrlInfo.timerId;
		bool timerAlreadySeized = false;
		for (int i = 0; i < SERVO_MAX_NUM_PINS; i++)
		{
			servoHdwrCntrlInfoDef hdwrInfo;
			GET_PROGRAM_MEMORY_ARRAY_ENTRY(servoHdwrCntrlInfo, i, hdwrInfo);
			if ((servoInfo[i].attached) && (tmId == hdwrInfo.timerId))
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
	timerPtr->setCompareOutputMode(HdwrCntrlInfo.outputChannel,avrTimerCounter::ComClrOcxOnCmpMatch ); //For Fast PWM  additionally set on bottom 
	
  servoPinIndex = newIndex;
	servoInfo[servoPinIndex].attached = true;

	#if defined(PWM_SERVO_DEBUG)
	Serial.println(F("attach After - Reg Contents"));
  timerPtr->printTimerRegisterContents(avrTimerCounter::TimerIdAll);
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
	timerPtr->setCompareOutputMode(HdwrCntrlInfo.outputChannel,avrTimerCounter::ComNormal ); // disconnect Ocx from pin
  pinMode(pin, INPUT);
	{
		avrTimerCounter::timerCounterIdsDef tmId = HdwrCntrlInfo.timerId;
		bool timerUsedCount = 0;
		for (int i = 0; i < SERVO_MAX_NUM_PINS; i++)
		{
			servoHdwrCntrlInfoDef hdwrInfo;
			GET_PROGRAM_MEMORY_ARRAY_ENTRY(servoHdwrCntrlInfo, i, hdwrInfo);
			if ((servoInfo[i].attached) && (tmId == hdwrInfo.timerId))
			// a servo is attached that uses that timer.
			{
				timerUsedCount++;
			}
		}
	  if (1 == timerUsedCount)
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
	Serial.println(F("detach After - Reg Contents"));
  timerPtr->printTimerRegisterContents(avrTimerCounter::TimerIdAll);
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


  if (angleArg < _minAngleDeg) angleArg = _minAngleDeg;
  if (angleArg > _maxAngleDeg) angleArg = _maxAngleDeg;
  angle = angleArg;

  // bleh, have to use longs to prevent overflow, could be tricky if always a 16MHz clock, but not true
  // That 8L on the end is the TCNT1 prescaler, it will need to change if the clock's prescaler changes,
  // but then there will likely be an overflow problem, so it will have to be handled by a human.
  p = (min16*16L*clockCyclesPerMicrosecond() + (max16-min16)*(16L*clockCyclesPerMicrosecond())*(angle - (long)_minAngleDeg) /((long)_maxAngleDeg - (long)_minAngleDeg))/8L;
  timerPtr->setOutputCompareReg(HdwrCntrlInfo.outputChannel, p);

  #if defined(PWM_SERVO_DEBUG)
	Serial.print(F("PWMServoNew::write wrote angle "));
	Serial.print(angle);
	Serial.print(F(" to channel "));
	Serial.print(HdwrCntrlInfo.outputChannel);
	Serial.print(F(" of timer "));
	Serial.print(HdwrCntrlInfo.timerId);
	Serial.print(F(" for pin "));
	Serial.println(pin);
	timerPtr->printTimerRegisterContents(HdwrCntrlInfo.timerId);
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
	Serial.println(F("Servo HdwrCntrlInfo:"));
	Serial.print(F("sizeof volatile unit16_t * :"));
	Serial.println(sizeof(temp));
	Serial.print(F("servoPinIndex: "));
	Serial.println(info.servoPinIndex);
	Serial.print(F("boardPinNumber: "));
	Serial.println(info.boardPinNumber);
	Serial.print(F("timerId;: "));
	Serial.println((unsigned long)info.timerId, HEX);
	Serial.print(F("outputChannel;	: "));
	Serial.println((unsigned long)info.outputChannel	, HEX);
}


#endif
