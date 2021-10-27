/*
 Author: Greg Gemmer, ghgemmer@gmail.com
 Copyright (c) 2021 Greg Gemmer.
 MIT license
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
