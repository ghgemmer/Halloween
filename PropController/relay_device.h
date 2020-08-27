
/*
relay device class
*/

#ifndef relay_device_h
#define relay_device_h

#include <inttypes.h>
#include "base_device.h"

class relay_device : public base_device
{  
  public:
    relay_device(int pin);  // pin is the avr pin
 
    // writes the value to the device 
    // a non zero value is on, and a 0 value is off
    void device_write(uint16_t value);
        
    uint16_t device_read();  // returns the device write setting

   private:
        int relay_pin;   

};

#endif
