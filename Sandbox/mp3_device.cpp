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

