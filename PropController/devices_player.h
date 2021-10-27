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


/*
This class is for playing devices. Each device to be played is registered with this class
along with the values to write (play) and the max number of values for that device.  
Values to write are passed via a reader class derived from the 
indexed_values_reader class to read a device value (to be written) associated with a given index
The class plays the device by calling the devices
write method for the value the reader returns in order waiting interval milliseconds between each set.  All
registered devices are played simultaneously (i.e. Each registerd device is called with its respective
registered reader.read(1) value, and the interval milliseconds is waited, then the same is done for reader.read(2) value, etc.
Playing can be done continuously with wraparound or once stopping at the end of the array.
Wraparound wraps at the end of the max entries for that device.
The playing can also be paused, and then resumed.
The inteval for playing all registered devices can be set (all devices are played at the same
interval)

In order for the class to perform the playing the perform_devices_player method must be 
called periodically.  See the method for further detail.
*/

#ifndef devices_player_h
#define devices_player_h

#include <inttypes.h>
#include "devices_player.h"
#include "base_device.h"
#include "indexed_values_reader.h"

class devices_player
{
  public:
  
    enum e_play_type {
      PLAY_CONTINUOUSLY,
      PLAY_ONCE
    };
    
    devices_player();
    
    void set_play_interval (unsigned int interval);
    unsigned int get_play_interval ();

    // registers a device to play. Returns a number which is used to
    // refer to the registered device.  A return value of -1 indicates the
    // registration failed.    
    int register_device (base_device * p_device,
                         indexed_values_reader * pdevice_values_reader,
                         const unsigned long num_write_values);

                          
    // unregisters the device associated with device_number.
    // Return value indicates if successed (true).    
    bool unregister_device (int device_number);
    
    // unregisters all device .
    // Return value indicates if successed (true).    
    bool unregister_all_devices ();
   

    // starts playing the devices at the start of their respective arrays.    
    bool start_play(e_play_type play_type);
    
    // stops playing the devices.  You must start_play after a stop    
    bool stop_play();

    bool pause_play();
    
    bool resume_play();
    
    // must be periodically called for this class to perfom playing    
    // at least as often as 1/4 the play interval setting.
    void perform_devices_player();       

  private:
  
    #define MAX_DEVICES 10
    enum e_state_type {
      STOPPED,
      PLAYING,
      PAUSED
    };
        
    
    struct device_reg_info_def {
      base_device * p_device;  // null for not registered
      indexed_values_reader * pdevice_values_reader;
      unsigned long num_write_values;
    };
    
    e_state_type playing_state;
    
    e_play_type playing_type;
    
    unsigned int play_interval; // play interval in milliseconds
    
    unsigned long timeout; // timeout for the play interval

    device_reg_info_def registered_devices[MAX_DEVICES];
        
    unsigned long max_size_of_all_reg_arrays;
    
    // current index into the arrays,  actually this modulo the device array size 
    // is the index into the device array
    unsigned long play_index; 
    
    unsigned long determine_max_array_size(); 
    
    // for each registered device write the value at index associated with the registered device to the device
    void write_devices (unsigned long index); 
                                 
};

#endif

