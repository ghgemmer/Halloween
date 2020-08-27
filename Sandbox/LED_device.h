
/*
LED device class
*/

#ifndef LED_device_h
#define LED_device_h

#include <inttypes.h>
#include "base_device.h"

class LED_device : public base_device
{  
  public:
    LED_device(int pin);  // pin is the avr pin
 
    // writes the value to the device 
    // currently a non zero value is full on, and a 0 value is off
    void device_write(uint16_t value);
        
    uint16_t device_read();  // returns the device write setting

   private:
        int LED_pin;   

};

#endif
