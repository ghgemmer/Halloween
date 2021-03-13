 
#include "devices_player.h"
#include <arduino.h>

devices_player::devices_player():
    play_interval(100),
    playing_state(STOPPED),
    playing_type(PLAY_ONCE),
    timeout(0),
    max_size_of_all_reg_arrays(0),
    play_index(0)
{
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        registered_devices[i].p_device = 0;
    }
}


/*
-----------------------------------------------------------------
set_play_interval
------------------------------------------------------------------
*/     
void devices_player::set_play_interval (unsigned int interval)
{
    play_interval = interval;
}

/*
-----------------------------------------------------------------
get_play_interval
------------------------------------------------------------------
*/     
unsigned int devices_player::get_play_interval ()
{
    return play_interval;
}

/*
-----------------------------------------------------------------
determine_max_array_size
------------------------------------------------------------------
*/     
unsigned long devices_player::determine_max_array_size()
{
    unsigned long max_size = 0;
    
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (registered_devices[i].p_device)
        {
            if (registered_devices[i].num_write_values > max_size)
            {
                max_size = registered_devices[i].num_write_values;
            }
        }
    }
    
    return max_size;  
}

/*
-----------------------------------------------------------------
register_device
------------------------------------------------------------------
*/     
int devices_player::register_device (base_device * p_device,
                      indexed_values_reader * pdevice_values_reader,
                      const unsigned long num_write_values)
{
    int device_number = -1;
    int i = 0;
    
    for (i = 0; i < MAX_DEVICES; i++)
    {
        if (!registered_devices[i].p_device)
        {
            registered_devices[i].p_device = p_device;
            registered_devices[i].pdevice_values_reader = pdevice_values_reader;
            registered_devices[i].num_write_values = num_write_values;
            device_number = i;
            break;
        }
    }
    
    max_size_of_all_reg_arrays = determine_max_array_size();
       
    return i;    
}


/*
-----------------------------------------------------------------
unregister_device
------------------------------------------------------------------
*/     
bool devices_player::unregister_device (int device_number)
{
    bool ok = false;
    
    if ((device_number < MAX_DEVICES)   && 
        (device_number >= 0)            &&
        (registered_devices[device_number].p_device)
       )
    {
        registered_devices[device_number].p_device = 0;
        ok = true;
    }

    max_size_of_all_reg_arrays = determine_max_array_size();
    
    return ok;
} 

/*
-----------------------------------------------------------------
unregister_all_devices
------------------------------------------------------------------
*/     

// Return value indicates if successed (true).    
bool devices_player::unregister_all_devices ()
{
  for (int device_number = 0; device_number < MAX_DEVICES; device_number++)
  {
    if (registered_devices[device_number].p_device)
    {
      unregister_device (device_number);
    }
  }
  return true;
}


/*
-----------------------------------------------------------------
start_play
------------------------------------------------------------------
*/     
bool devices_player::start_play(e_play_type play_type)
{
    bool ok = false;
    if (max_size_of_all_reg_arrays)
    { 
        stop_play();
        playing_type = play_type;
        playing_state = PLAYING;
        play_index = 0;
        timeout = millis();  // force timeout
        ok = true;
    }
    return ok;
    
}

/*
-----------------------------------------------------------------
stop_play
------------------------------------------------------------------
*/     
bool devices_player::stop_play()
{
    
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (registered_devices[i].p_device)
        {
            registered_devices[i].p_device->stop();
        }
    }
    playing_state = STOPPED;
   
    return true;
}

/*
-----------------------------------------------------------------
pause_play
------------------------------------------------------------------
*/     
bool devices_player::pause_play()
{
    bool ok = false;
    
    if (playing_state == PLAYING)
    {
        for (int i = 0; i < MAX_DEVICES; i++)
        {
            if (registered_devices[i].p_device)
            {
                registered_devices[i].p_device->pause();
            }
        }
        playing_state = PAUSED;
        ok = true; 
    }

    return ok;
}


/*
-----------------------------------------------------------------
resume_play
------------------------------------------------------------------
*/     
bool devices_player::resume_play()
{
    bool ok = false;
    
    if (playing_state == PAUSED)
    {
        for (int i = 0; i < MAX_DEVICES; i++)
        {
            if (registered_devices[i].p_device)
            {
                registered_devices[i].p_device->resume();
            }
        }
        playing_state = PLAYING;
        ok = true; 
    }

    return ok;
}



/*
-----------------------------------------------------------------
set_devices_for_index
------------------------------------------------------------------
*/     
void devices_player::write_devices (unsigned long index)
{
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (registered_devices[i].p_device)
        {
          uint16_t value_to_write;

          value_to_write = registered_devices[i].pdevice_values_reader->read(index % registered_devices[i].num_write_values);
          registered_devices[i].p_device->device_write(value_to_write);

        }
    }
    
}

/*
-----------------------------------------------------------------
perform_devices_player
------------------------------------------------------------------
*/     
void devices_player::perform_devices_player()
{
    switch (playing_state) {
        case PLAYING:
            if (timeout < millis())
            // play interval has passed
            {
                write_devices(play_index);
                if ((playing_type == PLAY_ONCE) && 
                    max_size_of_all_reg_arrays &&
                    (play_index >= max_size_of_all_reg_arrays  - 1))
                {
                    playing_state = STOPPED;
                }
                else
                {
                    play_index = (play_index + 1) % max_size_of_all_reg_arrays;
                    timeout += play_interval;              
                }               
            }
            break;
        default:
            break;
    }
}       


                    






