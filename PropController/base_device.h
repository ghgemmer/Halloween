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

This class is the base class for device write/read functionality.
It is an abstract class requiring a derived class to implement
the certain functionalities.
*/
#ifndef base_device_h
#define base_device_h

#include <inttypes.h>

class base_device 
{  
  public:
    base_device();
 
    // writes the value to the device   
    virtual void device_write(uint16_t value) = 0;
    virtual uint16_t device_read() = 0; // returns the device write setting
    

    // pause,stop, resume are only for devices whose set can cause the device
    // to play, for example an mp3 file.  In which case a pause
    // will pause the device (i.e. pause the playing)
    // a resume then continues playing 
    // If a derived device class needs this it must override this    
    virtual void pause();     
    virtual void stop();     
    virtual void resume(); 
    
    protected:
        uint16_t current_device_write_value;    
};

#endif


