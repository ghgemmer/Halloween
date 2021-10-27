/*
 Author: Greg Gemmer, ghgemmer@gmail.com
 Copyright (c) 2021 Greg Gemmer.
 MIT license.
 Dervied class from Adafruit Industries class Adafruit_BNO055
 See Adafruit_BNO055.h header for licensing and distrubution.
/*

/***************************************************************************
  This class is derived from the Adafruit_BNO055 class.
  It additionally accomodates multiple BNO055s with the same I2C address.
  This is accomplished using these devices on slave channels of an I2C switch

 ***************************************************************************/

#ifndef __ADAFRUIT_BNO055_HALLOWEENP_H__
#define __ADAFRUIT_BNO055_HALLOWEENP_H__

#include "i2cSwitch.h"
#include <Adafruit_BNO055.h>


class Adafruit_BNO055_HalloweenProp : public Adafruit_BNO055
{
    public:
#if defined (ARDUINO_SAMD_ZERO) && ! (ARDUINO_SAMD_FEATHER_M0)
#error "On an arduino Zero, BNO055's ADR pin must be high. Fix that, then delete this line."
    Adafruit_BNO055_HalloweenProp ( int32_t sensorID = -1, uint8_t address = BNO055_ADDRESS_B, i2cSwitch * i2cSwitchPtr = 0, uint8_t i2cSwitchChannels = 0,  uint8_t i2cSwitchChannelsMask = 0);
#else
    Adafruit_BNO055_HalloweenProp ( int32_t sensorID = -1, uint8_t address = BNO055_ADDRESS_A, i2cSwitch * i2cSwitchPtr = 0, uint8_t i2cSwitchChannels = 0,  uint8_t i2cSwitchChannelsMask = 0);
#endif
// i2cSwitchPtr - ptr to the i2cSwitch object if a single I2C switch is being used to access the BNO055 device, otherwise if 0 the I2C switch 
//                is not being used to access the device.
// 

    protected:
    byte  read8   ( adafruit_bno055_reg_t );
    bool  readLen ( adafruit_bno055_reg_t, byte* buffer, uint8_t len );
    bool  write8  ( adafruit_bno055_reg_t, byte value );

    private:
    uint8_t _i2cSwitchChannels;
    uint8_t _i2cSwitchChannelsMask;
    i2cSwitch * _i2cSwitchPtr;

};

#endif
