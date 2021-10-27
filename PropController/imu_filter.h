
/*
imu filter class:
This class supports providing a filtered imu output that limits the imu ranges to eliminate imu Euler mapping issues.
*/
#ifndef  imu_filter_h
#define  imu_filter_h

#include <inttypes.h>

class  imu_filter
{  
    public:
        // constructor 
        imu_filter(int defaultYaw, int defaultRoll, int defaultPitch, int minYaw, int maxYaw, int minRoll, int maxRoll, int minPitch, int maxPitch);        
        virtual void input(int degYaw, int degRoll, int degPitch, bool restart = false);  // restart is currently ignored
        // function output contains the filtered imu output.          
        // Currently the output is the current input if all values were in range otherwise
        // the last output where all values were in range, with the exception that if the Roll input is out of range we still allow the Yaw input to be
        // used as output if in range but ignore the Pitch input (even if in range) and use the last valid Pitch input.
        // After  input is called output must be called once before the next input is called
        virtual void output(int &degYaw, int &degRoll, int &degPitch);
    private:
        int _defaultYaw;
        int _defaultRoll;
        int _defaultPitch;
        int _minYaw;
        int _maxYaw;
        int _minRoll;
        int _maxRoll;
        int _minPitch;
        int _maxPitch;
        int _YawOutput;
        int _RollOutput;
        int _PitchOutput;
    
};

#endif
