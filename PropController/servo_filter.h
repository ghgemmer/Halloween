
/*
servo filter class:
This class supports providing a filtered servo degree settings output based on the
servo degree settings input given to it, and the filtering parameters setup to it.
*/
#ifndef  servo_filter_h
#define  servo_filter_h

#include <inttypes.h>

class  servo_filter
{  
    public:
        // constructor 
        // servoNoLoadSpeed units of degrees/millisecond
        // servoMaxTorque units of oz-in
        servo_filter(float servoNoLoadSpeed, float servoMaxTorque = 0);
        
        // setUpdatePeriod sets the period (in milliseconds) each input is given to this filter
        virtual void setUpdatePeriod(int period);
        // startingPointDegrees - Indicates to the filter the position in degrees the servo was 
        // last set to.  Normally called once before a sequence of input/outputs are called.
        virtual void startingPointDegrees(int degrees);
        // function input is passed the desired servo degree setting, and current torque load on the servo if available.
        // The torque load along with the servoNoLoadSpeed is used to determines how fast a loaded servo can transition
        // !!!! THE TORQUELOAD PARAMETER IS CURRENTLY IGNORED.
        // After input is called,  output should be called once and only once before calling input again.
        // It is assumed that the output is then written to the servo by the caller.
        // It is assumed that method startingPointDegrees has been called initially before any sequence
        // off calls to input/output to indicate the initial position of the servo.
        virtual void input(int degrees, float torqueLoad = 0);
        // function output contains the filtered output servo degrees.
        virtual void output(int &degrees);
        // flush the filter output, so filtering starts anew.
        virtual void flush();
    private:
        static const int maxBufferSize = 20;
        float _servoNoLoadSpeed;
        float _servoMaxTorque;
        int _period;
        int _buffer[maxBufferSize];
        int _bufferReadIndex; // Index in buffer to be read.  -1 indicates nothing to read
        int _lastInput;  // the last input we transitioned to.
        int _lastOutput; // the last output we returned.
        int _lastTorqueLoad;
    
};

#endif
