#include <inttypes.h>
#include "Arduino.h"
#include "servo_filter.h"

servo_filter::servo_filter(float servoNoLoadSpeed, float servoMaxTorque):
    _servoNoLoadSpeed(servoNoLoadSpeed),
    _servoMaxTorque(servoMaxTorque),
    _period(50),
    _bufferReadIndex(-1),
    _lastInput(0),
    _lastOutput(0),
    _lastTorqueLoad(0)
{
}
 
void servo_filter::setUpdatePeriod(int period)
{
    _period = period;
}

void servo_filter::startingPointDegrees(int degrees)
{
    _lastInput = degrees;
}

void servo_filter::input(int degrees, float torqueLoad)
{
    // torqueLoad currently ignored
    if (_bufferReadIndex >= 0)
        // output entries to still be read as transitioning to end point.  Ignore input
    {
    }
    else
    {
        int degreeChange = degrees - _lastInput; // diff between where we want to go to and what we last went to
        float degreesPerMsec = _servoNoLoadSpeed;
        int periods = ceil(abs((((float)degreeChange) / degreesPerMsec)/_period));
        if (periods > maxBufferSize)
        {
            periods =  maxBufferSize;
            // Serial.println(F("servo_filter::input: Exceeded max entries"));
        }
        if (periods <= 0)
        {
            periods = 1;
        }
        // set all entries to the final end point (i.e. no intermediate settings and just allow the number of periods time to reach that point)
        for (int i = 0; i < periods; i++)
        {
            _buffer[i] = degrees;
        }
        _bufferReadIndex = periods - 1;
        _lastInput = degrees;  // save last end point we are transitioning to
    }
}
void servo_filter::output(int &degrees)
{
    if (_bufferReadIndex >= 0)
    // entires to still be read
    {
        _lastOutput = _buffer[_bufferReadIndex];
        _bufferReadIndex--;
    }
    degrees = _lastOutput;
}

void servo_filter::flush()
{
    _bufferReadIndex = -1;
}
