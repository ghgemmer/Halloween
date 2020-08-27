/*
This class is for playing devices. Each device to be played is registered with this class
along with a pointer to an array and the number of values in the array.  The class plays the device by calling the devices
write method for each value in the array in order waiting interval milliseconds between each set.  All
registered devices are played simultaneously (i.e. the set for each registerd device A is called with its respective
registered array [1] value, and the interval milliseconds is waited, then the same is done for array[2] value, etc.
Playing can be done continuously with wraparound or once stopping at the end of the array.
Wraparound wraps at the end of each array.
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
                          const uint16_t * p_device_write_value,
                          const unsigned long num_write_values);
 
    // unregisters the device associated with device_number.
    // Return value indicates if successed (true).    
    bool unregister_device (int device_number);

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
      const uint16_t * p_device_write_value;
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

