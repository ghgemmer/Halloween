#include <inttypes.h>
//#define i2cSwitchDebug
#ifdef i2cSwitchDebug
#include <stdio.h> 
#include <string.h> 
#include "Arduino.h"
#endif
#include <Wire.h>
#include "i2cSwitch.h"

// The I2C switch is a TCA9548A Low-Voltage 8-Channel I2C switch with reset.
i2cSwitch::i2cSwitch(uint8_t switchI2cAdrs):
enabledChannels(0),
switchI2cAddress(switchI2cAdrs)
{
}

void i2cSwitch::begin(bool doWireBegin)
{
    if (doWireBegin)
    {
        Wire.begin();
    }
}

bool i2cSwitch::enableChannels( uint8_t channels, uint8_t mask, bool force)
{
    bool ok = false;
    uint8_t result;
    if (((channels & mask) != (enabledChannels & mask)) || force)
    {
        Wire.beginTransmission(switchI2cAddress);
        #if ARDUINO >= 100
        Wire.write((uint8_t)((enabledChannels & ~mask) | (channels & mask)));
        #else
        Wire.send((enabledChannels & ~mask) | (channels & mask));
        #endif
        result = Wire.endTransmission();
        if (0 == result)
        // send successful
        {
            enabledChannels = (enabledChannels & ~mask) | (channels & mask);
            ok = true;
        }
        else
        {
            // transmission error
            #ifdef i2cSwitchDebug
            Serial.print("i2cSwitch::enableChannels error.  Wire.endTransmission Return value = ");
            Serial.println(result);
            #endif
        }
    }
    else
    {
        ok = true;
    }
    return ok;
}

bool i2cSwitch::getEnabledChannels(uint8_t & channels)
{
    Wire.requestFrom(switchI2cAddress, (uint8_t)1);
    #if ARDUINO >= 100
    channels = Wire.read();
    #else
    channels = Wire.receive();
    #endif
    return true;
}
