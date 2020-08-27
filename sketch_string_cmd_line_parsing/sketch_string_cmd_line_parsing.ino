#include "Arduino.h"
#include <stdio.h> 
#include <string.h> 

#define CmdLineMaxSize  50
char cmdLine [CmdLineMaxSize];
unsigned int cmdLineIndex;
const char Carriage_Return = 13;
const char delimiters[] = " ";
bool cmdComplete;


void setup() {
  Serial.begin(9600);
  cmdLineIndex = 0;
  cmdComplete = false;
  }

void loop() 
{ 

 if (Serial.available())
  {
    char char_value = Serial.read();
    if (cmdLineIndex < CmdLineMaxSize) 
    {
      
      if ( Carriage_Return == char_value)
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
      if ( Carriage_Return == char_value)
      {
        cmdLineIndex = 0;
        Serial.println("Cmd Line to long" );
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
    
    if ((token = strtok_r(restcmdLine, delimiters, &restcmdLine)))
    {
      if (0 == strcmp(token, "cmd1"))
      {
        int value;
        Serial.print("Cmd:"); 
        Serial.print(token);
        Serial.println( ":parameters following: " );
        if (sscanf(restcmdLine, "%d%n", &value, &charsScanned) == 2)                   
        {
          char str[80];
          restcmdLine += charsScanned;
          int len = sprintf(str, "%d", value);
          if (len >= 0)
          {
            Serial.print("IntParam1 decoded as:");
            Serial.println(str);
            if (sscanf(restcmdLine, "%d%n", &value, &charsScanned) == 2)                   
            {
              restcmdLine += charsScanned;
              len = sprintf(str, "%d", value);
              if (len >= 0)
              {
                Serial.print("IntParam2 decoded as:");
                Serial.println(str);
              }
              else
              {
                Serial.println("sprintf Error on Int Param 2:");
              }           
            }
            else
            {
              Serial.print("Command:");
              Serial.println(token);
              Serial.println("Error: Param 1 not an integer");
            }
          }
          else
          {
            Serial.println("sprintf Error on Int Param 1:");
          }           
        }
        else
        {
          Serial.print("Command:");
          Serial.println(token);
          Serial.println("Error: Param 1 not an integer");
        }
      }
      else if (strcmp(token, "cmd2"))
      {
        Serial.print("Cmd:"); 
        Serial.println(token);
      }
    } 
    // reset command line and completion indication
    cmdComplete = false;
    cmdLineIndex = 0;   
  }

}

