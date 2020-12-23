#ifndef avrTimerCounter_h
#define avrTimerCounter_h

/*
  avrTimerCounter.h - AVR Hardware Timer Counter Library
  Copyright (c) 2020 G. Gemmer All right reserved.
 
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
// Currently this only handles the AVR 16 bit Timer/Counters

//#define AVR_TIMER_COUNTER_DEBUG 0
#include <inttypes.h>

//ATMega 168/328			Timer 1   Channels A,B
//ATMega 1280/2560		Timer 1,3,4,5   Channels A,B,C
//ATMega 644/644P			Timer 1 Channels A,B
//AT90USB162					Timer 1 channels A,B,C
//ATMega32U4					Timer 1 channels A,B,C, this also has a Timer 3 with channels A,B,C but only channel A gets outside on a teensy 2.0
//AT90USB646/1286			Timer 1,3 channels A,B,C

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) // Arduino
	// TimerId1
  #define TIMER_CPU_BOARD_TYPE1 0 
	#define MAX_NUM_TIMER_COUNTERS 1
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // Arduino Mega
	// TimerId1,3,4,5
  #define TIMER_CPU_BOARD_TYPE2 0 
	#define MAX_NUM_TIMER_COUNTERS 4
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__) // Sanguino
	// TimerId1
  #define TIMER_CPU_BOARD_TYPE3 0 
	#define MAX_NUM_TIMER_COUNTERS 1
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#elif defined(__AVR_AT90USB162__) // Teensy 1.0
	// TimerId1
  #define TIMER_CPU_BOARD_TYPE4 0 
	#define MAX_NUM_TIMER_COUNTERS 1
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#elif defined(__AVR_ATmega32U4__) // Teensy 2.0
	// TimerId1
  #define TIMER_CPU_BOARD_TYPE5 0 
	#define MAX_NUM_TIMER_COUNTERS 2
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) // Teensy++
	// TimerId1,3
  #define TIMER_CPU_BOARD_TYPE6 0 
	#define MAX_NUM_TIMER_COUNTERS 2
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#else
	// TimerId1
  #define TIMER_CPU_BOARD_TYPE7 0 
	#define MAX_NUM_TIMER_COUNTERS 1
	#define MAX_NUM_TIMER_BITDEFS  MAX_NUM_TIMER_COUNTERS
#endif

class avrTimerCounter
{
	public:
  	enum channelDef
  	// must be in this exact order with ChanA being 0 so can use for loops and getNumberChannels
  	{
  		ChanA,
  		ChanB,
  		ChanC,
  		MaxNumChannels
		};
  	enum timerCounterIdsDef
  	{
  		TimerId0,
  		TimerId1,
  		TimerId2,
  		TimerId3,
  		TimerId4,
  		TimerId5,
  		TimerId6,
  		TimerId7,
  		TimerId8,
  		TimerId9,
  		TimerId10,
  		TimerIdAll,
  		TimerIdNone
		};
		
		enum waveformGenerationModeDef
		{
			// Values must match hardware
			WgmNormal													= 0 ,
			WgmPwmPhaseCorrect8Bit						= 1 ,
			WgmPwmPhaseCorrect9Bit						= 2 ,
			WgmPwmPhaseCorrect10Bit						= 3 ,
			WgmCtcOcrTop											= 4 ,
			WgmFastPwmPhaseCorrect8Bit				= 5 ,
			WgmFastPwmPhaseCorrect9Bit				= 6 ,
			WgmFastPwmPhaseCorrect10Bit				= 7 ,
			WgmPwmPhaseFreqCorrectIcrTop			= 8 ,
			WgmPwmPhaseFreqCorrectOcrTop			= 9 ,
			WgmPwmPhaseCorrectIcrTop					= 10,
			WgmPwmPhaseCorrectOcrTop					= 11,
			WgmCtcIcrTop											= 12,
			WgmReserved1											= 13,
			WgmFastPwmIcrTop									= 14,
			WgmFastPwmOcrTop									= 15
		};
		enum compareOutputModeDef
		{
			// Values must match hardware
			ComNormal											= 0, // Normal port operation, disconnects OCx from controlling port pin
			ComToggleOcxOnCmpMatch				= 1,
				// For Fast PWM and Phase Freq Correct PWM only Oc1A is toggled, Oc1B,Oc1C is disconnected
			ComClrOcxOnCmpMatch						= 2,
				// For Fast PWM  additionally set on bottom 
				// For Phase Freq Correct PWM  clear on up counting Match, set on down counting match
			ComSetOcxOnCmpMatch						= 3
				// For Fast PWM  additionally clear on bottom 
				// For Phase Freq Correct PWM  set on up counting Match, clear on down counting match
		};
		
		enum inputClockSelectDef
		{
			// Values must match hardware
			csStopped											=  0,				
			csFromPrescalerDiv1           =  1,
			csFromPrescalerDiv8           =  2,
			csFromPrescalerDiv64          =  3,
			csFromPrescalerDiv256         =  4,
			csFromPrescalerDiv1024        =  5,
			csExtClkSrcTnPinFallingEdge   =  6,
			csExtClkSrcTnPinRisingEdge    =  7
		};
		
  private:
  	struct HdwrBitDef
  	{
  		// uses same naming as in cpu documentation
  		uint8_t index;  // for verifying table was constructed correctly. Index in entry should match index used to access table
  		uint8_t com0BitMsk[MaxNumChannels]; //reg tccrA
  		uint8_t com1BitMsk[MaxNumChannels]; //reg tccrA
  		uint8_t wgm0BitMsk; //reg tccrA
  		uint8_t wgm1BitMsk; //reg tccrA
  		uint8_t icncBitMsk; //reg tccrB
  		uint8_t icesBitMsk; //reg tccrB
  		uint8_t cs0BitMsk; //reg tccrB
  		uint8_t cs1BitMsk; //reg tccrB
  		uint8_t cs2BitMsk; //reg tccrB
  		uint8_t wgm2BitMsk; //reg tccrB
  		uint8_t wgm3BitMsk; //reg tccrB
  		uint8_t focBitMsk[MaxNumChannels]; //reg tccrC
  		uint8_t icieBitMsk; //reg timsk
  		uint8_t ocieBitMsk[MaxNumChannels]; //reg timsk
  		uint8_t toieBitMsk; //reg timsk
  		uint8_t icfBitMsk; //reg tifr
  		uint8_t ocfBitMsk[MaxNumChannels]; //reg tifr
  		uint8_t tovBitMsk;  //reg tifr
  	};

  	struct HdwrCntrlInfoDef 
  	// Defines the hardware control information for an AVR processor 16 TimerCounter
  	{
  		timerCounterIdsDef timerId;
  		volatile uint8_t * tccrA;
  		volatile uint8_t * tccrB;
  		//volatile uint8_t * tccrC;  //Not needed at this time
  		//volatile uint8_t * tifr;   //Not needed at this time
  		uint8_t numberOfChannels; // number of channels this timer actually supports (starts from ChanA on up to ChanC)
  		volatile uint16_t * ocr[MaxNumChannels];
  		volatile uint8_t * timsk;
  		volatile uint16_t * icr;
  		//volatile uint16_t * tcnt; //Not needed at this time
  		//volatile uint8_t * gttcr;  //Not needed at this time
  		int8_t bitDefsIndex; // index into the TimerHdwrBitDefsTable defining the bit defs for this Timer
  	};
  	
		timerCounterIdsDef timerId;
    int8_t  timerIndex;  // index into TimerHdwrCntrlInfo for this timer.  -1 indicates no timer
    int8_t  bitDefsIndex;  // copy of index into TimerHdwrBitDefsTable for this timer  
    uint8_t numberOfChannels; // copy for fast access for this timer
    volatile uint16_t * ocr[MaxNumChannels]; // copy for fast access for this timer
    
    const static HdwrCntrlInfoDef TimerHdwrCntrlInfo[MAX_NUM_TIMER_COUNTERS];
    const static HdwrBitDef TimerHdwrBitDefsTable[MAX_NUM_TIMER_BITDEFS];
    static avrTimerCounter timersObjects[MAX_NUM_TIMER_COUNTERS];
    //void getHdwrCntrlInfo(int8_t index, HdwrCntrlInfoDef &info);
    //void getHdwrBitDefs(int8_t index, HdwrBitDef &def);
    

#ifdef AVR_TIMER_COUNTER_DEBUG
		void printAdrsValueHex(unsigned long address, unsigned long value);
#endif 

  public:
    avrTimerCounter(timerCounterIdsDef tmrId);
    static avrTimerCounter * getAvrTimerCounter(timerCounterIdsDef tmrId);
    bool initialize();
    uint8_t getNumberChannels();
    bool setCompareOutputMode(channelDef channel,compareOutputModeDef mode );
    void setWaveformGenerationMode(waveformGenerationModeDef wgm);
    void setInputNoiseCanceller(bool enable);
    void setInputCaptureEdgeSelect(bool positiveEdge);
    void setInputClockSelect(inputClockSelectDef select);
		// bool forceOutputCompare(channelDef channel); // Not needed at this time
		bool setOutputCompareReg(channelDef channel, uint16_t val);
		void setInputCaptureReg(uint16_t val);
		void clrAllInterruptEnables();
		void setInputCaptureIntEnable(bool enable);
		bool setOutputCompareIntEnable(channelDef channel, bool enable);
		void setTimerOverflowIntEnable(bool enable);
		//void clrInputCaptureFlag(); // Not needed at this time
		//void clrOutputCompareFlag(channelDef channel); // Not needed at this time
		//void clrTimerOverflowIntEnable(); // Not needed at this time
		
#ifdef AVR_TIMER_COUNTER_DEBUG
		void printTimerRegisterContents();
		void printTimerRegisterContents(timerCounterIdsDef tmrId);
		void printHdwrCntrlInfo();
#endif 
};

#endif
