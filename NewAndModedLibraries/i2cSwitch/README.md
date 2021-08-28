# TCA9548A I2C Switch Driver  #

This driver is for the TCA9548A I2C Switch.
The switch allows a user to connect a master I2C bus up to 8 I2C slave buses , i.e. channels.
Any combination of channels can be enabled/disabled allowing the user to handle
situations such as multiple devices with the same i2C Address (using different channels), or spreading out the
capacitive loading of devices by placing them on different channels so only the 

