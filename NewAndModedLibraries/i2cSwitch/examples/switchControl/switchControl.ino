#include <inttypes.h>
#include <stdio.h> 
#include <string.h> 
#include "Arduino.h"
//#include <Wire.h>


#if 1
#include <i2cSwitch.h>
#else
#include "i2cSwitch.h"
#endif

/* 
   This example sets 
   History
   =======
   2021-08-18  - First release
*/

i2cSwitch switchDevice = i2cSwitch(0x70);  // I2C switch address is 0x70

/**************************************************************************/
/*
    Displays the currently enabled swtich channels
*/
/**************************************************************************/
void displayI2cSwitchChannels(void)
{
    bool ok = false;
    uint8_t channels = 0;
    Serial.print(F("I2C Switch Get Enabled Channels = "));
    ok = switchDevice.getEnabledChannels(channels);
    Serial.print(channels, HEX);
    Serial.print(F(", ok = "));
    Serial.println(ok);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
    bool ok;
    switchDevice.begin(true);
    Serial.begin(115200);
    Serial.println(F("I2C Swtich Test"));
    for (int i = 0; i < 8; i++)
    {
        Serial.print(F("Setting enabled channels to "));
        Serial.print(1<<i, HEX);        
        Serial.println(F(", mask = 0xff "));
        ok = switchDevice.enableChannels((uint8_t)(1<<i), 0xff);
        if (ok)
        {
            displayI2cSwitchChannels();
        }
        else
        {
            Serial.println(F("Failed to set enabled channels"));
        }
    }
    Serial.println(F("Setting enabled channels to 0x00, mask = 0xff"));       
    ok = switchDevice.enableChannels(0x00, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xff, mask = 0xff"));       
    ok = switchDevice.enableChannels(0xff, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xaa, mask = 0xff"));       
    ok = switchDevice.enableChannels(0xaa, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0x55, mask = 0xff"));       
    ok = switchDevice.enableChannels(0x55, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0x00, mask = 0xff"));       
    ok = switchDevice.enableChannels(0x00, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xff, mask = 0xaa"));       
    ok = switchDevice.enableChannels(0xff, 0xaa);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xff, mask = 0x55"));       
    ok = switchDevice.enableChannels(0xff, 0x55);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0x00, mask = 0xff"));       
    ok = switchDevice.enableChannels(0x00, 0xff);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xaa, mask = 0xf0"));       
    ok = switchDevice.enableChannels(0xaa, 0xf0);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
    Serial.println(F("Setting enabled channels to 0xff, mask = 0x00"));       
    ok = switchDevice.enableChannels(0xff, 0x00);
    if (ok)
    {
        displayI2cSwitchChannels();
    }
    else
    {
        Serial.println(F("Failed to set enabled channels"));
    }
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
}
