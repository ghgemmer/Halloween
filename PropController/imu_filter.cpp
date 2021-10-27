#include <inttypes.h>
#include "Arduino.h"
#include "imu_filter.h"

imu_filter::imu_filter(int defaultYaw, int defaultRoll, int defaultPitch, 
                       int minYaw, int maxYaw, int minRoll, int maxRoll, int minPitch, int maxPitch):
        _defaultYaw(defaultYaw),
        _defaultRoll(defaultRoll),
        _defaultPitch(defaultPitch),
        _minYaw(minYaw),
        _maxYaw(maxYaw),
        _minRoll(minRoll),
        _maxRoll(maxRoll),
        _minPitch(minPitch),
        _maxPitch(maxPitch),
        _YawOutput(defaultYaw),
        _RollOutput(defaultRoll),
        _PitchOutput(defaultPitch)
{
    if ((defaultYaw < _minYaw) || (defaultYaw > _maxYaw))
    {
        _YawOutput = _minYaw;
    }
    if ((_defaultRoll < _minRoll) || (_defaultRoll > _maxRoll))
    {
        _RollOutput = _minRoll;
    }
    if ((_defaultPitch < _minPitch) || (_defaultPitch > _maxPitch))
    {
        _PitchOutput = _minPitch;
    }
}

void imu_filter::input(int degYaw, int degRoll, int degPitch, bool restart)
    
{
    if ((degYaw >= _minYaw) && (degYaw <= _maxYaw) && 
        (degRoll >= _minRoll) && (degRoll <= _maxRoll) && 
        (degPitch >= _minPitch) && (degPitch <= _maxPitch))
    {
        _YawOutput = degYaw;
        _RollOutput = degRoll;
        _PitchOutput = degPitch;
    }
    else if ( ((degRoll < _minRoll) || (degRoll > _maxRoll)) && ((degYaw >= _minYaw) && (degYaw <= _maxYaw)))
        // Roll out of range but Yaw is in range.
    {
        _YawOutput = degYaw;
    }
}

void imu_filter::output(int &degYaw, int &degRoll, int &degPitch)
{
    degYaw = _YawOutput;
    degRoll = _RollOutput;
    degPitch = _PitchOutput;
}
