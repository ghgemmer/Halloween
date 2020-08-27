
/*
mp3 device class
*/

#ifndef mp3_device_h
#define mp3_device_h

#include <inttypes.h>
#include "base_device.h"
#include "mp3_player.h"

class mp3_device : public base_device, public MP3_Player
{  
  public:
  
    enum e_mp3_device_write_cmds_def {
        // The value passed to device_write has the upper byte as the command 
        // and the lower byte as any parameters.
        START   = 0, // the lower byte contains a number x that represents a file to play where
                     // x = 0-199 correspond to file name "000.mp3" to "199.mp3"
        STOP    = 1,
        PAUSE   = 2,
        RESUME  = 3,
        VOLUME  = 4, // the lower byte contains the volume level 1-10 with 1 min and 10 max
        UNCHANGED = 5
    };
    
    mp3_device();
 
    // The value passed to device_write has the upper byte as the command 
    // and the lower byte is any parameters.  See e_mp3_device_write_cmds_def
    void device_write(uint16_t value);
        
    uint16_t device_read();  // returns the device write setting

    void pause();     
    void stop();     
    void resume(); 

   private:  

};

#endif
