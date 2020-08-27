#include "relay_device.h"
#include <arduino.h>

relay_device::relay_device(int pin): base_device(),
relay_pin(pin)
{
  current_device_write_value = LOW;
  digitalWrite(relay_pin, current_device_write_value);
  pinMode(relay_pin, OUTPUT);   
}

// writes the value to the device 
// currently a non zero value is full on, and a 0 value is off
void relay_device::device_write(uint16_t value)
{
    current_device_write_value = value;
    if (value)
    {
        digitalWrite(relay_pin, HIGH);
    }
    else{
        digitalWrite(relay_pin, LOW);
    }
    
}
    
uint16_t relay_device::device_read()
{
    return current_device_write_value;
}
