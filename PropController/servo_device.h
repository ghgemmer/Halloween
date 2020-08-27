
/*
servo device class
*/
#ifndef servo_device_h
#define servo_device_h

#include <inttypes.h>
#include "base_device.h"
#include <PWMServo.h>

class servo_device : public base_device, public PWMServo
{  
  public:
    servo_device();
 
    // writes the value to the device 
    // value is in degrees of angle (0 to 180)
    void device_write(uint16_t value);
        
    uint16_t device_read();  // returns the device write setting
    

};

#endif
