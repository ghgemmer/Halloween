#ifndef i2cSwitch_h
#define i2cSwitch_h

#include <inttypes.h>

class i2cSwitch {
/*
This i2cSwitch class handles the physical I2C switch functionality.
Currently this handles a single physical switch (not chained swtiches)
The switch allows a user to connect a master I2C bus up to 8 I2C slave buses , i.e. channels.
Any combination of channels can be enabled/disabled allowing the user to handle
situations such as multiple devices with the same i2C Address (using different channels), or spreading out the
capacitive loading of devices by placing them on different channels so only the 
loading of enabled channel(s) is incurred at any one time.
The user typically will create a set of constants defining the I2C switch channel and mask
combinations to use in another file.  If a class uses a device that is on one of these channels the
appropriate channel and mask constants are generally passed to the class during instantiation and the class handles
setting the appropriate channels in the switch as needed.
*/
private:
uint8_t enabledChannels; // The enabled channels in the switch. bit0 = channel0, bit1 = channel1, etc
uint8_t switchI2cAddress;  // I2C address of the physcial switch. Used to control the switch

public:
i2cSwitch(uint8_t switchI2cAdrs);
// The switchI2cAdrs is currently limited to addresses 0x70 to 0x77 inclusive
void begin(bool doWireBegin);
// Called once to begin use of the i2cSwitch.  Wire.begin is performed if doWireBegin is true
bool enableChannels( uint8_t channels, uint8_t mask, bool force = false);
// Set the switch channel enable bits to the values in channels for only the bit positions corresponding to bits = 1 in mask 
// Thus if mask bit x = 1 then  switch channel enable bit x = channels bit x
// channels bit 0 is channel 0 of the physical switch, channels bit 1 is channel 1, etc
// If force = true then the physical switch is updated even if the channel enables did not change, otherwise time is saved by not updating 
// the physical switch. Force can be used at power up as a safeguard if the physical switch did not default for any reason
// to its known powerup state.
// Return - True if successful, false otherwise
bool getEnabledChannels(uint8_t & channels);
// Directly reads the switch device control register to return the enabled channels in the channels ref parameter
// Method returns true if read ok, otherwise false
// 
};
#endif