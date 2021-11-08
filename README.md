**Halloween Prop and Controller project**

## Table of Contents
* [General Info](#general-info)
* [Hardware](#hardware)
* [Software](#software)
* [Directories and files](#directories-and-files)
* [URLs](#urls)
* [Contacts](#contacts)



# General Info

This project is for a prop controller and an animated prop for Halloween.  The prop is a DIY with a female
vampire head on an approx 4 foot Walgreen's skeleton body.
    
Servos are used to animate the head, mouth and right arm and elbow.
The prop can both emit audio thru a speaker and listen thru a mic and has red LED eyes that can be turned on or off.
The prop can also, thru pneumatics, lean forward parallel to the ground, or sit upright.
The prop has a minature night vision camera on the top front of its head allowing it to see.  The camera is controlled
thru a smartphone, and allows the user to see what the prop head is seeing and record it if desired (both audio and video).
    
    The controller for the prop is an Arduino Mega 2560 which is used to perform both live interactive
    sessions or capture and playback of recorded sessions. Almost all aspects of the prop can be controlled thru
    the serial command line interface of the Arduino USB port. The prop can be exactly synchronized to the users
    movements thru inertial management units (IMUs) attached to the users head and mouth, and eventually ones
    attached to the users arm.  This allows for quick, and effortless choreographing of prop movements by matching the users head,
    mouth and arm/forearm movements.  This choreographing can be captured for playback later on.
    There is also an MP3 module the Arduino controls to play audio files to the props speaker.


# Hardware

## Prop Head

    The head nod, rotate, and mouth are controlled by servos and custom aluminum brackets along with Actobotics
    brackets that attach to the head and mouth. The head rotate servo is actually in the body and rotates a PVC
    pipe that goes up to the head.  The nod servo is in the head as well as the mouth servo.  All servos except
    the mouth use Actobotics servo blocks to handle lateral loads on the servo axis. The head also has red LED
    eyes that can be turned on or off although these could instead be connected to a PWM signal or an analog
    signal to adjust intensity.  At the top of the head is a Relohas minature night vision camera (a cube that is
    0.79 inches long on each side) with a base that is at the back of the head and connected to the camera by a
    thin 8" flat cable. The base uses Wifi to conenct to a smartphone.  The base also has a rechargeable battery
    in it and a USB connector to charge it. The camera can also be powered by the USB connector which is how it is
    currently used.

## Prop Body

    The prop skeleton body has the bottoms of the legs bent back on the ground as if the prop is sitting on its knees
    and lower leg. The body uses an iHome speaker to talk and emit audio,  an Adafruit microphone and amplifier
    module with AGC to listen, a pneumatic cylinder, solenoid valves, and air compressor to rotate the body with
    head from a leaning over position, parallel to the ground, to an upright position and vice versa. 
    
    The user hasa Adafruit 9814 mic and line amp, with AGC disabled, that is connected thru wires to the speaker that allows
    the user to talk out of the prop speaker. There is also a MidFly MP3 module that is conencted to the Arduino
    and thru wires to the speaker that is used to play mp3 files.  
    
    The body is attached to a base via a bolt hinge
    that allows it to swing so it can either be leaning over or upright. The body is pushed/pulled by a pneumatic
    cylinder to stand upright or lean over. The pneumatic cylinder is controlled by a solenoid valve device which the
    main controller controls. Elastic cables and pneuamtic speed controllers are used to slow the pneumatic
    cylinder as it nears its end points, either upright or leaning over. The pneumatics have not been used in the
    past few years as I have been concentrating on the servo operation. 
    
    The right skeleton arm has 3 servos at the
    shoulder for pitch, yaw, and roll and one at the elbow to bend the elbow. All servos except the mouth are
    held in Actobotics servo blocks to withstand lateral forces off the servo axis. Mostly Actobotics hardware,
    such as screws, hubs, spacers, brackets, channels, patterns, bearings, etc, is used to connect the servo
    blocks to the arm/head. The servos are run at 6 volts with the exception of the arm pitch servo being run at
    7.4 volts to get the needed speed and torque. GoBilda servos are used for the arm and elbow, while Hitec are
    used for the head and mouth (see Prop Wiring.docx for detail). GoBilda servos are dead quiet when holding a
    position, even when under load, so are perfect for the application.  Hitec servos tend to make a high pitched
    whine when holding a position under load. Hitec servos were used when the head was first animated before it
    was discovered much later on that GoBilda servos would be better in that case.  Eventually the head nod servo
    will be replaced with a GoBilda servo as it is the one Hitec servo with the most noticable whine. All the
    servos allow a farily fluid/natural/and speedy(when needed) movement of the skeleton head and arm/forearm. The
    clothes on the skeleton body came from an old Halloween costume.

## IMUs and Sychronized User Movements

    To easily allow a user to naturally manipulate the prop for live interactive sessions as well as catpure
    for playback, Adafruit BNO055 Inertial Measurment Units (IMUs) are attached to the user and the servos can
    be synchronized to the movements of the user thru software. Currently 1 IMU is used on the top of the head
    using a ball cap,  1 on the mouth using a mouth guard, and two on a simulated arm/forearm in the interim
    until I can get them to work on an actual arm.
    The Arduino I2C interface is used to access these IMUs.

## Physical Wiring

    Currently the controller is connected to the prop thru standard heavy duty twisted servo wire, and thru a 11
    wire cable. Standard servo wire consists of 3 wires twisted around each other.  For servos this is used for
    power, ground, and signal. Twisted wires also help eliminate noise. The servo wires are also used for things
    other than the servos as the wire is very flexible and easy to use. The 11 wire cable is an underground type
    cable, although not used underground.  It was first used for the connections between prop and controller but,
    due to the gauge of wire in it, is much less flexible than the servo wire which was used later on.
    
    Both cable and servo wire is about 15 feet in length from controller to prop.  The goal was to be able to
    easily look at and change controller connections to the peripherals, and connect/disconnect power to the
    servos without having to do to this at prop. The wire at the controller first connects to a terminal block
    which then connects to the Arduino, and peripheral devies.  This makes moving connections around easier (at
    the terminal block) and also eliminates any pulling stress of wires that go to the Arduino, although wire hold
    down brackets and painters/duct tape are used on the wires.
    
    The Arduino and all peripheral hardware are placed on a 1/2 inch piece of plywood to make it easy to move all
    at once. Connectors are used at the prop to allow all the wires to be easily disconnected from the prop so the
    prop can be easily transported. The MP3, I2C switch, user Mic amp, drive circuit for the solenoid valve, and
    LED resistors are place on breadboards to make them easy to connect to.

## Processor board and Interfaces/Peripherals used

The controller is an Arduino Mega 2560 processor board.  

The Arduino Interfaces used are as follows along with the devices they control:

    - 7 of its 12 Pulse Width Modulation (PWM) outputs are used to generate PWM signals for jitter free control of the 7 servos.  
    - 1 digital output is used to control the solenoid valve to set the pneumatic cylinder either fully extended or 
        fully retracted.  This output goes to a 12V transistor driver circuit with fly back diode then to the solenoid valve in the prop.
    - 1 digital output is used to turn the eye LEDs on or off through a resistor.
    - The USB connection on the Arduino is used to both program the Arduino and communciate with the running program thru serial commands
      and responses
    - The I2C bus is used to interface to an I2C switch which interfaces to 2 IMUs
      on one channel and 2 on another channel of the switch.  The I2C switch is needed to resolve I2C address
      bus conflicts as the IMUs can only have one of two I2C addresses.
    - 1 TTL serial interface to control an MP3 module to generate audio and play audio files from an SD card
    on the MP3 module.  The audio output of that MP3 goes to the speaker
    - 1 digital input pulled up to 5 volts and used to read a button.
    
The prop wiring/schematic is contained in the file \Halloween\Prop Wiring.docx
      
# Software

    The program is written in Arduino C++ and uses several Arduino libraries, some new DIY. All code was written
    using the UltraEdit IDE, although any text editor could be used, and then compiled/built/downloaded using the
    Arduino IDE (version 1.8.13 or later).  The IDE is also used to add new libraries as well as run the serial
    command/monitor that the user interfaces to the program with. All code is DIY except for most of the
    libraries. The code uses classes extensively.  Program memory space is used to store large constants to avoid
    chewing up RAM with these.  The Arduino by default puts constants in program memory and then transfers them to
    RAM to access them in the code.
    
    Any DIY code uses the MIT software license.
    

## Serial Command Interface

    The user can control the program thru a serial command
    line interface on the USB serial line.
    Multiple commands can be entered on a single line with a semicolon between them.  
    The serial commands are as follows:
    
**ArmPitch _degrees_**  : Sets the Arm pitch servo in degrees

**ArmRoll  _degrees_**  : Sets the Arm roll servo in degrees

**ArmYaw  _degrees_** : Sets the Arm yaw servo in degrees

**AudioBloodCurdlngScream** : Sets the Arm yaw servo in degrees

**AudioDayO** : Plays the MP3 Harry Belafonti Day-O (Banana Boat Song) file

**AudioHissing** : Plays the MP3 AudioHissing file 

**AudioMoreOftenChewing** : Plays the MP3 More Often Chewing file 

**AudioShakeSenora** : Plays the MP3  Harry Belafonti Shake Senora file

**AudioStop** : Stops the MP3 audio player

**AudioWerewolvesLondon** : Plays the MP3 Werewolves Of London file

**BackDown** : Sets the prop back down parallel to the ground

**BackUp** : Sets the prop back straight up 

**DayOPlayerSetup** : Sets up the prop player for the DayO prop sequence

**Delay15SecPlayOnce** : Delays 15 seconds then plays the player once with whatever was setup.

**DelayMsec _time_** : Delays the time in milliseconds before the next command is executed.

**ElbowPitch _degrees_** : Sets the Elbow pitch servo in degrees

**EyesOff** : Turns the prop LED eyes off

**EyesOn** : Turns the prop LED eyes on 

**HeadHorizontal _degrees_** : Sets the Head horizontal rotate servo in degrees

**HeadVertical _degrees_** : Sets the Head vertical (i.e head nod) servo in degrees

**Imu2Calibrate** : : deprecated - Use ImuCalibrate

**Imu2Read** : Currently does nothing.

**ImuCalibrate _ImuId_** _ImuId_ - the ID number of the IMU to display the summary cal data and detailed cal data for.
Displays the system status, self test result, system error status, system Cal State,  gyro Cal State,  accelerometer Cal State,  magnetometer Cal State
The cal states are as described in the Visualize3D command.  If the IMU is not fully calibrated this command indicates this and does not
return any data.

**ImuGetStoredCalibData _ImuId_** _ImuId_ - the ID number of the IMU to get cal data for and set back up in the IMU. 0 = Mouth, 1 = Head, 2 = Arm, 3 = Forearm.

**ImuHeadMouth _periodMsec_ _audioFile_ _audioDelayInPeriods_ _[includeArm]_** : Enables servo movement being synchronized to the corresonding IMUs.
* _periodMsec_ - the period in milliseonds to read the IMUs and update the servos.
* _audioFile_ - the ID number of the audio file to play when the command is exeucted
* _audioDelayInPeriods_ - The delay in number of _periodMsec_ before the audio file is played.  This allows time for the user to get ready 
before the audio plays.
* _includeArm_ - Optional. Indicates if the Arm/Elbow servos are to be synchronzied or left alone.  0 = don't sync 1 = sync

**ImuHeadMouthStop** Stops the servo movement being synchronized to the IMUs.  The servos are left in the position they were at when this 
command was entered.  The ImuHeadMouth operations can also be stopped by pressing a physical button 

**ImuMouthControl** : deprecated - Use ImuHeadMouth

**ImuMouthControlStop** : deprecated - Use ImuHeadMouthStop

**ImuRead _ImuId_** _ImuId_ - the ID number of the IMU to reads and displays the current IMU Yaw, Roll, Pitch angles for.

**ImuSetStoredCalibData  _ImuId_** _ImuId_ - the ID number of the IMU to store its cal data for. 0 = Mouth, 1 = Head, 2 = Arm, 3 = Forearm.
data is stored in the Arduino non volatile memory.

**ImusShowPitchDiff _periodMsec_ _ImuNumber1_ _ImuNumber2_** : Continually displays the difference between the zero based pitch readings of the two IMUs
The initial pitch readings at the time the command is executed are used as the zero based pitches and the 
difference displayed is (pitch1 - pitch2) - (initial pitch 1 - initial pitch 2).
* _periodMsec_ - the period in milliseonds to get the orientation data.
* _ImuNumber1_ - the ID number of the first IMU to use. 0 = Mouth, 1 = Head, 2 = Arm, 3 = Forearm.
* _ImuNumber2_ - the ID number of the second IMU to use.


**ImusShowPitchDiffStop** : Stops displaying the difference between the pitches (stops the ImusShowPitchDiff command operations)

**Mouth _degrees_** : Sets the Mouth servo in degrees

**PlayOnce** : Plays the pop player once.  This runs the previously setup prop sequence.

**PlayStop** : Stops the prop player.

**VampireArmGraspAtPlayerSetup** : Sets up the prop player for the Vampire grasping and hissing at TOTer prop sequence 

**VampirePlayerSetup** : Sets up the prop player for the Vampire chewing leaned over, pops up straight, then screams and hisses then , pops back down  prop sequence  

**Visualize3D _periodMsec_  _sensorNumber_ _format_** - Starts the Visualize 3D process. This process is
used to calibrate the intertial measurement units (IMUs) and output the current IMU orientation data which can also be
used to run the Visualize 3D program on a PC which shows the IMU orientation visually with a token object.
Calibration occurs by the user moving the IMU in different orientations to calibrate it.  Leave the IMU still for a few seconds for the gyro to calibrate.
Then move the IMU around to calibrate the magnetometer.  The accelerometer takes the longest to calibrate and
requires putting the IMU about 45 degrees about each side of the x, y, z axis's of the IMU letting it sit at
least 5 seconds at each orientation or doing figure 8s with it.  Note that the magnetometer can be affected by
nearby magnetic fields generated by laptops, magnets, etc.  So when calibrating the magnetometer keep it away form those sources. 

* _periodMsec_ - the period in milliseonds to get the calibration and orientation data and output it.
* _sensorNumber_ - the ID number of the IMU to use. 0 = Mouth, 1 = Head, 2 = Arm, 3 = Forearm.
* _format_ - The orientation format to get or use.   0 = direct Euler where the Euler angles are read directly
from the IMU, 1 = quaternions converted to Euler where quaternions are read from the IMU and then converted to Euler angles,

The orientation data is output as Yaw, Roll, Pitch in degrees.  The calibration data is output as system cal number, gyro cal number, accelerometer cal number,
magnetometer cal number.  Each calibration (cal) number ranges from 0 to 3 with 0 being not calibrated and 3 being fully calibrated.
Calibration can be speeded up by saving off and restoring the calibrated data using the ImuSetStoredCalibData, and the 
respectively. 

**Visualize3DStop** : Stops Visualize3D operations.

**WerewolvesLondonPlayerSetup** : Sets up the prop player for the Werewolves of London prop sequence
    
    
## Prop Playback Data 
   
    Prop playback data is currently stored as constant arrays in the program itself
    although the future goal is to store it on a separate SD card the Arduino accesses for unlimited playback
    storage. These constants are stored in the PROGMEM2 section of the code, using the PROGMEMSECTION2 macro, so they
    don't take up RAM space, only program code space. 

## Capturing Playback Data and Adding it to the Program 
   
    When using live interactive prop movement operations
    (i.e. command "ImuHeadMouth ...") the large output on the serial monitor that shows the servo positions, etc,
    can be captured by copying and pasting it into a text file. This can then be opened as an Excel file and its contents copied
    to sheet VampireArmCapture of the excel file VampireArmCapture.xlsx. Once that is done the user can copy
    and transpose paste it from sheet VampireArmCapture to sheet 1 in the appropriate spot. At that point copy
    and paste from sheet 1 to the appropriate row in sheet 2.
    Then sheet 2 has the code snippet you can copy and paste into the PropController.ino file for accessing it in the code for playback later on.
    
# Directories and files

\Halloween\PropController\ - Dir that contains the software program.  The Arduino PropController.ino (main file) and its
    supporting user files are contained here.
    
\Halloween\NewAndModedLibraries\ - Dir that contains new or modified libraries.  These are then zipped and imported into the
    Arduino IDE.
    
\Halloween\QuickHeadMouthCaptureCommands.txt  - File that contains serial commands that were commonly used for prop operation on Halloween.

\Halloween\Prop Wiring.docx  - MS Word file that contains the prop wiring information/schematic.

\Halloween\ArmServoAngularAccelCalcs.xlsx - Excel file containing torque and speed calculations for the servos.  Also contains servo
    min,max degree and PWM pulse width calculations used when instantiating servo objects.
    
\Halloween\*.mp3  - mp3 audio files that can be placed on the MP3 SD card renamed as 1.mp3, 2.mp3, etc,
which the prop controller can direct the MP3 module to play.

\Halloween\Lessons Learned.docx -  A lessons learned file along with future enhancements.

There are several other files and directories in \Halloween\ but the significant ones are listed above.
    
# URLs

[Halloween Prop](https://photos.app.goo.gl/th4qkniJdXuoBmHA6) -  contains photos of the
    prop as well as some videos of the prop in action and demos of its range of motion.
    
[Halloween 2018](https://photos.app.goo.gl/2tGpkc9Z9Mq6irJE6) -
    Videos of the prop before arm movement was added.
        
# Contacts

    Greg Gemmer: ghgemmer@gmail.com