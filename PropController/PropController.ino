// Prop Controller

#include "Arduino.h"
#include <PWMServo.h>
#include <AltSoftSerial.h>
#include <inttypes.h>
#include "base_device.h"
#include "servo_device.h"
#include "relay_device.h"
#include "mp3_device.h"
#include "LED_device.h"
#include "devices_player.h"
#include "mp3_Player.h"

enum e_pneumatic_back_position_def {
    PNEUMATIC_BACK_UPRIGHT  = HIGH,
    PNEUMATIC_BACK_BENTOVER = LOW
};

enum e_eye_LEDs_def {
    EYE_LEDS_OFF    = 0,
    EYE_LEDS_ON     = 255
};

enum e_voice_files {
    CHEWING_AT_HEAD_FILE            = 0,
    BLOOD_CURDLING_SCREAM_FILE      = 1,
    HISSING_FILE                    = 2
    
};

#define NUM_ARRAY_ENTRIES(a)  (sizeof(a)/sizeof(a[0]))
#define MKVoiceEntry(cmd, param) ((mp3_device::cmd << 8) | (param & 0x00ff))

// imported from excel spreadsheet
const uint16_t Head_Horizontal_Rotation_values[] = {	90	,100	,90	,80	,90	,90	,90	,90	,90	,90	,90	,90	,90	,90	,90	,90	,90	,90	,110	,110	,110	,110	,110	,110																																																																																															
};																																																																																																																							
																																																																																																																							
const uint16_t Head_Vertical_Rotation_values[] = {	90	,90	,90	,90	,90	,95	,90	,85	,90	,90	,90	,120	,120	,120	,120	,120	,120	,120	,100	,100	,100	,100	,100	,100																																																																																															
};																																																																																																																							
																																																																																																																							
const uint16_t Eyes_LEDs_values[] = {	EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_OFF	,EYE_LEDS_ON	,EYE_LEDS_ON	,EYE_LEDS_ON	,EYE_LEDS_ON	,EYE_LEDS_ON	,EYE_LEDS_ON																																																																																															
};																																																																																																																							
																																																																																																																							
const uint16_t Pneumatic_Back_values[] = {	PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_BENTOVER	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT	,PNEUMATIC_BACK_UPRIGHT																																																																																															
};																																																																																																																							
																																																																																																																							
const uint16_t Voice_Player_values[] = {	MKVoiceEntry(START,  CHEWING_AT_HEAD_FILE)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(STOP, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(START,  BLOOD_CURDLING_SCREAM_FILE)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)	, MKVoiceEntry(UNCHANGED, 0)																																																																																															
};																																																																																																																							




// Create the devices that make up the Prop

servo_device    Head_Horizontal_Rotation_servo      ;   // attached to pins in setup
servo_device    Head_Vertical_Rotation_servo        ;   // attached to pins in setup
LED_device      Eyes_LEDs                           (22); // pin 22
relay_device    Pneumatic_Back_relay                (23); // pint 23
mp3_device      Voice_Player                        ;
devices_player  Devices_Player                      ;



 
void setup() 
{
    // attach Head servos to specific pins on the cpu board
    // Only can use pins 11,12,or 13 as these are the only hardware only PWM control pins
    // (i.e. the PWM is completely done in hardware)
    Head_Horizontal_Rotation_servo.attach (SERVO_PIN_A,800,2200 );  // pin 11 on Mega2560,
                                                                    // 800usec for 0 degrees
                                                                    // 2200usec for 180 degrees
    Head_Vertical_Rotation_servo.attach   (SERVO_PIN_B,800,2200);   // pin 12 on Mega2560
                                                                    // 800usec for 0 degrees
                                                                    // 2200usec for 180 degrees
    // setup prop head to be completely level and looking straight forward.
    Head_Horizontal_Rotation_servo.device_write(90);               
    Head_Vertical_Rotation_servo.device_write(90);
    
    // Setup Eye LEDs to be off
    Eyes_LEDs.device_write(EYE_LEDS_OFF);
    
    // Setup Pneumatic Back to be bent over
    Pneumatic_Back_relay.device_write(PNEUMATIC_BACK_BENTOVER);
                                                                
    // Setup voice player to be stopped and at max volume
    Voice_Player.device_write(mp3_device::STOP << 8);
    Voice_Player.device_write((mp3_device::VOLUME << 8) + 10); // 10 is max volume
    
    // Setup interval for entries in the device player
    Devices_Player.set_play_interval(500); // 500 milliseconds between device writes;
    
    // register the devices with the devices player along with the table of values to play

    Devices_Player.register_device (&Head_Horizontal_Rotation_servo,
                                    Head_Horizontal_Rotation_values,
                                    NUM_ARRAY_ENTRIES(Head_Horizontal_Rotation_values));
    Devices_Player.register_device (&Head_Vertical_Rotation_servo,
                                    Head_Vertical_Rotation_values,
                                    NUM_ARRAY_ENTRIES(Head_Vertical_Rotation_values));
    Devices_Player.register_device (&Eyes_LEDs,
                                    Eyes_LEDs_values,
                                    NUM_ARRAY_ENTRIES(Eyes_LEDs_values));
    Devices_Player.register_device (&Pneumatic_Back_relay,
                                    Pneumatic_Back_values,
                                    NUM_ARRAY_ENTRIES(Pneumatic_Back_values));
    Devices_Player.register_device (&Voice_Player,
                                    Voice_Player_values,
                                    NUM_ARRAY_ENTRIES(Voice_Player_values));
                                    
    // For testing purposes play the devices once. 
    Devices_Player.start_play(devices_player::PLAY_ONCE);                                
    
}
 
void loop() 
{ 
    // perform device playing operations
    Devices_Player.perform_devices_player();
} 
