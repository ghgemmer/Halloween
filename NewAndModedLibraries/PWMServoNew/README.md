# PWM Servo Driver  #

This driver is for any Arduino to drive servos on its PWM signal outputs using the PWM hardware timers of the arduino.
Use of hardware generated PWM eliminates any jitter issues on the PWM signal generated.
The number of timers determines the number of servos that can be driven (assuming timers are not dedicated
to other things).  Generally each timer can drive 3 servos independently (each timer has 3 independent channels).
Up to 12 Servos on an Arduino Mega256 can be driven using all 4 timers.


