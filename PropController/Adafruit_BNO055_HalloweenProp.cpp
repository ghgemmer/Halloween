/***************************************************************************
  This is a derived library for the BNO055 orientation sensor

  This class is derived from the Adafruit_BNO055 class.
 ***************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "i2cSwitch.h"
#include "Adafruit_BNO055_HalloweenProp.h"

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Instantiates a new Adafruit_BNO055 class
*/
/**************************************************************************/
Adafruit_BNO055_HalloweenProp::Adafruit_BNO055_HalloweenProp(int32_t sensorID, uint8_t address, i2cSwitch * i2cSwitchPtr, uint8_t i2cSwitchChannels = 0,  uint8_t i2cSwitchChannelsMask = 0): Adafruit_BNO055(sensorID, address)
{
    _i2cSwitchChannels = i2cSwitchChannels;
    _i2cSwitchChannelsMask = i2cSwitchChannelsMask;
    _i2cSwitchPtr = i2cSwitchPtr;
}


/***************************************************************************
 PROTECTED FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Writes an 8 bit value over I2C
*/
/**************************************************************************/
bool Adafruit_BNO055_HalloweenProp::write8(adafruit_bno055_reg_t reg, byte value)
{
    bool ok = true;
    if (_i2cSwitchPtr && _i2cSwitchChannelsMask)
    {
        ok = _i2cSwitchPtr->enableChannels( _i2cSwitchChannels, _i2cSwitchChannelsMask);
    }
    return ok && Adafruit_BNO055::write8( reg, value);
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
*/
/**************************************************************************/
byte Adafruit_BNO055_HalloweenProp::read8(adafruit_bno055_reg_t reg )
{
    if (_i2cSwitchPtr && _i2cSwitchChannelsMask)
    {
        _i2cSwitchPtr->enableChannels( _i2cSwitchChannels, _i2cSwitchChannelsMask);
    }
    return Adafruit_BNO055::read8( reg );
}

/**************************************************************************/
/*!
    @brief  Reads the specified number of bytes over I2C
*/
/**************************************************************************/
bool Adafruit_BNO055_HalloweenProp::readLen(adafruit_bno055_reg_t reg, byte * buffer, uint8_t len)
{
    bool ok = true;
    if (_i2cSwitchPtr && _i2cSwitchChannelsMask)
    {
        ok = _i2cSwitchPtr->enableChannels( _i2cSwitchChannels, _i2cSwitchChannelsMask);
    }
    return ok && Adafruit_BNO055::readLen(reg, buffer, len);
}
