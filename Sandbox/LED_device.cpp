#include "LED_device.h"
#include <arduino.h>

LED_device::LED_device(int pin): base_device(),
LED_pin(pin)
{
  current_device_write_value = LOW;
  digitalWrite(LED_pin, current_device_write_value);
  pinMode(LED_pin, OUTPUT);   
}

// writes the value to the device 
// currently a non zero value is full on, and a 0 value is off
void LED_device::device_write(uint16_t value)
{
    current_device_write_value = value;
    if (value)
    {
        digitalWrite(LED_pin, HIGH);
    }
    else{
        digitalWrite(LED_pin, LOW);
    }
    
}
    
uint16_t LED_device::device_read()
{
    return current_device_write_value;
}
