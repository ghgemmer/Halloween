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
