/*
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


