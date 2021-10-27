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
