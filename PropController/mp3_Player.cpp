/*
 Author: Greg Gemmer, ghgemmer@gmail.com
 Copyright (c) 2021 Greg Gemmer.
 MIT license
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
	-------------------------------------------------
	File:  MP3_Player
	-------------------------------------------------
		Implements the MP3 Player object.
		The MP3 hardware module this object controls is a
		MDFLY MOL-AU5121 SD Card MP3 Player Module RS232-TTL
	
	-------------------------------------------------
*/

#include "mp3_player.h"
#include "Arduino.h"


/*
	-------------------------------------------------
	Constant declarations
	-------------------------------------------------	
*/
static const int mp3_serial_baud_rate 		= 4800;
static const int mp3_ser_max_volume_level 	= 31;
static const int mp3_ser_min_volume_level 	= 0;
static const int mp3_ser_cmd_delay_ms 		= 3;

#define m_mp3_serial_port Serial3
// The above defines the true serial port on the Mega 2560 to use 
//Serial:0 (RX) and 1 (TX); Pins 0 and 1 are also connected to the corresponding pins of the ATmega16U2 USB-to-TTL Serial chip.
//Serial 1: 19 (RX) and 18 (TX); 
//Serial 2: 17 (RX) and 16 (TX); 
//Serial 3: 15 (RX) and 14 (TX). 

/*
	-------------------------------------------------
	Type declarations
	-------------------------------------------------
*/
// The following are the serial commands the mdfly accepts.
// Each command is 1 byte in length and is defined as follows.
enum mp3_serial_cmd_byte_type 
{
	MP3_SER_CMD_RANDOM_PLAY 			= 0X0,
	//Play specified MP3 file (001-199)
	MP3_SER_CMD_PLAY_FILE_MIN_NUM		= 0x01,
	//Play files 0x01-0xC7
	MP3_SER_CMD_PLAY_FILE_MAX_NUM		= 0xC7,
	MP3_SER_CMD_VOLUME_INCREASE 		= 0XE8,
	MP3_SER_CMD_VOLUME_DECREASE 		= 0XE9,
	MP3_SER_CMD_PAUSE_RESUME_PLAY 	= 0XEA,
	MP3_SER_CMD_HOLD 						= 0XEB,
	MP3_SER_CMD_RESUME 					= 0XEC,
	MP3_SER_CMD_STOP 						= 0XEF
};

/*
	-------------------------------------------------
	Variable declarations
	-------------------------------------------------
*/


/*
	-------------------------------------------------
	Prototypes
	-------------------------------------------------
*/

	
	
	/*
	-------------------------------------------------
	Function: MP3_Player
	-------------------------------------------------
	*/
	MP3_Player::MP3_Player():
		m_state(INITIALIZING),
		m_volume(-1),
		m_mp3_ser_volume(-1)
	{

	}
	
	/*
	-------------------------------------------------
	Function: Initialize
	-------------------------------------------------
	*/
	void MP3_Player::Initialize(unsigned int volume)
	{
	
		// the mdfly mp3 uses 4800 baud, 8 data bits, no parity, 1 stop bit
		m_mp3_serial_port.begin(mp3_serial_baud_rate, SERIAL_8N1); 

		// Stop any currently playing song if one is playing.
		Stop();
		
		// Send sufficient number of decrease volume commands to get to known min m_volume level
		// in mp3 player
		for (int i = 0; i < (mp3_ser_max_volume_level - mp3_ser_min_volume_level); i++)
		{
			m_mp3_serial_port.write(MP3_SER_CMD_VOLUME_DECREASE);
			delay(mp3_ser_cmd_delay_ms);
			
		}
		m_volume = mp3_min_volume_level;
		m_mp3_ser_volume = mp3_ser_min_volume_level;
		
		// set to initial volume
		Set_Volume(volume);
	}
	
	/*
	-------------------------------------------------
	Function: Play
	-------------------------------------------------
	*/
	void MP3_Player::Play(char * mp3file_name)
	{
		// convert file root name to integer (ascii string "001" to "199")
		int mp3_file_number = (int)(strtol(mp3file_name,NULL,10));
		
		if ((mp3_file_number >= MP3_SER_CMD_PLAY_FILE_MIN_NUM) &&
		    (mp3_file_number <= MP3_SER_CMD_PLAY_FILE_MAX_NUM))
		{
			m_mp3_serial_port.write(mp3_file_number);
			delay(mp3_ser_cmd_delay_ms);
                        m_state = PLAYING;
		}	
	}
	
	/*
	-------------------------------------------------
	Function: Stop
	-------------------------------------------------
	*/
	void MP3_Player::Stop()
	{
		m_mp3_serial_port.write(MP3_SER_CMD_STOP);
		delay(mp3_ser_cmd_delay_ms);
				// TODO delay?
		m_state = STOPPED;
                //Serial.print("m_state is ");
                //Serial.println(m_state);
	}
	
	/*
	-------------------------------------------------
	Function: Pause
	-------------------------------------------------
	*/
	void MP3_Player::Pause()
	{
		switch (m_state) 
		{
	   	case PLAYING:
				m_mp3_serial_port.write(MP3_SER_CMD_PAUSE_RESUME_PLAY);
				delay(mp3_ser_cmd_delay_ms);
				m_state = PAUSED;
                                //Serial.print("m_state is ");
                                //Serial.println(m_state);
	   		break;
	   	default:
	   		// otherwise ignore 
	   		break;
	   }
	}
	
	/*
	-------------------------------------------------
	Function: Resume_Play
	-------------------------------------------------
	*/
	void MP3_Player::Resume_Play()
	{
		switch (m_state) 
		{
	   	case PAUSED:
				m_mp3_serial_port.write(MP3_SER_CMD_PAUSE_RESUME_PLAY);
				delay(mp3_ser_cmd_delay_ms);
				m_state = PLAYING;
                                //Serial.print("m_state is ");
                                //Serial.println(m_state);
	   		break;
	   	default:
	   		// otherwise ignore
	   		break;
	   }
	}
	
   /*
	-------------------------------------------------
	Function: Set_Volume
	-------------------------------------------------
	*/
	void MP3_Player::Set_Volume(unsigned int volume)
	{
		int i;
		if ((m_volume >= mp3_min_volume_level) &&
		    (m_volume <= mp3_max_volume_level))
		// current volume in valid range
		{
                        //Serial.print("Set Volume to ");
                        //Serial.println(volume);
			// scale the desired volume to the mp3 serial volume range
			long ser_vol;
			ser_vol = ((volume - mp3_min_volume_level) * (mp3_ser_max_volume_level - mp3_ser_min_volume_level) / (mp3_max_volume_level -mp3_min_volume_level))
			      + mp3_ser_min_volume_level;
			      
			if (ser_vol < mp3_ser_min_volume_level)
			{
				ser_vol = mp3_ser_min_volume_level;
			}
			else if (ser_vol > mp3_ser_max_volume_level)
			{
				ser_vol = mp3_ser_max_volume_level;
			}
			
                        //Serial.print("Set mp ser volume to ");
                        //Serial.println(ser_vol);

			for (i = 0; i < (ser_vol - m_mp3_ser_volume); i++)
			{
				m_mp3_serial_port.write(MP3_SER_CMD_VOLUME_INCREASE);
                                //Serial.println("Vol+");
				delay(2*mp3_ser_cmd_delay_ms);
			}
			for (i = 0; i < (m_mp3_ser_volume - ser_vol ); i++)
			{
				m_mp3_serial_port.write(MP3_SER_CMD_VOLUME_DECREASE);
		                //Serial.println("Vol-");
				delay(2*mp3_ser_cmd_delay_ms);
			}
			m_mp3_ser_volume = ser_vol;
		}
		else
		{
			// do nothing
		}
	}
	
