#include <stdio.h> 
#include <string.h> 
//#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
//#else
//#include "wiring.h"
//#endif
#include "PWMServoNew.h"
#include <inttypes.h>

// Command Line structures
#define CmdLineMaxSize  100
char cmdLine [CmdLineMaxSize];
unsigned int cmdLineIndex;
const char Carriage_Return = 13;
const char CmdSeperator = ';';
const char delimiters[] = " ";
bool cmdComplete;


//#define servoMaxPins 3
#define servoMaxPins SERVO_MAX_NUM_PINS

// Instantiate servos a Mega can use
PWMServoNew myservos[servoMaxPins];
 
void setup() 
{ 
    // setup cmd line structures
    cmdLineIndex = 0;
    cmdComplete = false;
// goBILDA 2000 Series Dual Mode Servo (25-2):   300 degrees for 500-2500.  Thus for 0-180 deg use 500 - 1700
// Savox SA1230SG Coreless Digital Servo: 135 degrees for 800-2200µsec. Thus use truncates to 
    Serial.begin(115200);
    myservos[0 ].attach (SERVO_PIN_A,500,1700,0,180 );  // Pin 11 
    myservos[1 ].attach (SERVO_PIN_B,800,2200 );  // Pin 12 
    myservos[2 ].attach (SERVO_PIN_C,800,2200 );  // Pin 13 
    myservos[3 ].attach (SERVO_PIN_D,500,1700,0,180 );  // Pin 5 
    myservos[4 ].attach (SERVO_PIN_E,800,2200 );  // Pin 2 
    myservos[5 ].attach (SERVO_PIN_F,800,2200 );  // Pin 3 
    myservos[6 ].attach (SERVO_PIN_G,500,1700,0,180 );  // Pin 6 
    myservos[7 ].attach (SERVO_PIN_H,800,2200 );  // Pin 7 
    myservos[8 ].attach (SERVO_PIN_I,800,2200 );  // Pin 8 
    myservos[9 ].attach (SERVO_PIN_J,500,2500,0,300 );  // Pin 46 
    myservos[10].attach (SERVO_PIN_K,800,2200 );  // Pin 45 
    myservos[11].attach (SERVO_PIN_L,800,2200,0,135 );  // Pin 44 
  
} 

void loop() 
{ 
  if (Serial.available())
  {
    char char_value = Serial.read();
    if (cmdLineIndex < CmdLineMaxSize) 
    {
      
      if (( Carriage_Return == char_value) || (CmdSeperator == char_value))
      {
        cmdLine[cmdLineIndex] = 0; // set end of string
        cmdComplete = true;
      }
      else
      {
        cmdLine[cmdLineIndex] = char_value;
      }
      cmdLineIndex++;
    }
    else
    {
      // cmd line is too long dump the characters until we get a CR then allow cmd line to start again.
      if (( Carriage_Return == char_value) || (CmdSeperator == char_value))
      {
        cmdLineIndex = 0;
        Serial.println(F("CmdLine to long") );
      }    
    } 
  }
  if (cmdComplete) // we have a complete command
  {
    unsigned int index = 0;   
    char* token; 
    char* restcmdLine = cmdLine;    
    int charsScanned = 0; 
    int numParms = 0;
    int value;
    
    if ((token = strtok_r(restcmdLine, delimiters, &restcmdLine)))
    {
        if (0 == strcmp(token, "SetServo"))
        {
            int servoId;
            int servoAngle;
            int forceArg;
            bool force;
            int numArgs;
            if ((numArgs = sscanf(restcmdLine, "%d %d %d", &servoId, &servoAngle, &forceArg)) >= 2)
            {
                if ((servoId >= 0) && (servoId < servoMaxPins))
                {
                    if ((servoAngle <= 400) && (servoAngle >= 0))
                    // 400 used to allow code to take then statement showing that max angle in the constructor is enforced by the servo write method
                    {
                        force = true;
                        if ((numArgs >= 3) && (forceArg == 0))
                        {
                            force = false;
                        }
                        myservos[servoId].write(servoAngle, force);
                        Serial.print(F("Wrote Servo Id "));
                        Serial.print(servoId);
                        Serial.print(F(", angle degrees "));
                        Serial.println(servoAngle);
                    }
                    else
                    {
                        Serial.print(F("Servo Angle out of range: "));
                        Serial.println(servoAngle);
                    }
                }
                else
                {
                    Serial.print(F("Servo Id out of range:  "));
                    Serial.println(servoId);
                }
            }
            else
            {
                Serial.println(F("Invalid number of arguements to cmd: "));
                Serial.println(token);
            }
        }
        else
        {
            Serial.print(F("Unknown Cmd:  "));
            Serial.println(token);
        }
    }
    // reset command line and completion indication
    cmdComplete = false;
    cmdLineIndex = 0;
  }
} 
