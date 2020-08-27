#include <inttypes.h>
#include <PWMServo.h>
#include "servo_device.h"

servo_device::servo_device(): base_device(), PWMServo()   
{    
}
 
void servo_device::device_write(uint16_t value)
{
    if (read() != value)
    // if not already that value so as to not cause glitches.
    {
        write(value);
    }
}
    
uint16_t servo_device::device_read()
{
    return read();
}
