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

#include <inttypes.h>
#include "mp3_device.h"
#include "Arduino.h"


mp3_device::mp3_device(): base_device(), MP3_Player()
{
    current_device_write_value = STOP << 8;
    //Initialize(8);
    //Stop();
}

void mp3_device::device_write(uint16_t value)
{
    uint16_t  cmd       = (value >> 8) & 0x00ff;
    uint16_t  parameter = value & 0x00ff;
    
    current_device_write_value = value;

    switch (cmd) {
        case START:
                char filename[20];
                sprintf(filename, "%d.mp3", parameter);
                Play(filename);
            break;
        case STOP:
                Stop();
            break;
        case PAUSE:
                Pause();
            break;
        case RESUME:
                Resume_Play();
            break;
        case VOLUME:
                Set_Volume(parameter);
            break;
        default:
            break;
    }


}

uint16_t mp3_device::device_read()
{
    return current_device_write_value;
}


void mp3_device::pause()      
{
    Pause();
}

void mp3_device::stop()      
{
    Stop();
}

void mp3_device::resume()      
{
    Resume_Play();
}

