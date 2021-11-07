Halloween Prop and Controller project

Overview:

This project is for a prop controller and an animated prop for Halloween. The prop is a DIY with a female
vampire head on an approx 4 foot Walgreen's skeleton body. Servos are used to animate the head, mouth and right arm and elbow.
The prop can both emit audio thru a speaker and listen thru a mic and has red LED eyes that can be turned on or off.
The prop can also, thru pneumatics, lean forward parallel to the ground, or sit upright.
The prop has a minature night vision camera on the top front of its head allowing it to see.  The camera is controlled
thru a smartphone, and allows the user to see what the prop is seeing and record it if desired (both audio and video).
The controller for the prop is an Arduino Mega 2560 which can be used to perform both live interactive
sessions or for capture and playback of recorded sessions. Almost all aspects of the prop can be controlled thru
the serial command line interface of the Arduino USB port. The prop can be exactly synchronized to the users
movements thru inertial management units (IMUs) attached to the users head and mouth, and eventually ones
attached to the users arm.  This allows for quick, and effortless choreographing of prop movements by matching the users head,
mouth and arm/forearm movements.  This choreographing can be captured for playback later on.  Currently the captured data
can be stored as a constant array in the software program itself for playback, but the future goal is to use a separate memory
SD card the Arduino accesses to store and retrieve all playback data, thus allowing massive storage capabilities.
There is an MP3 module with SD card the Arduino controls to play audio files.



Hardware:

The head nod, rotate, and mouth are controller by servos and
custom aluminum brackets along with Actobotics brackets that attach to the head and mouth. The head rotate servo is
actually in the body and rotates a PVC pipe that goes up to the head.  The nod servo is in the head as well as
the mouth servo.  The head also has red LED eyes that can be turned on or off although these could instead be
connected to a PWM signal or an analog signal to adjust intensity.  At the top of the head is a Relohas
minature night vision camera (a cube that is 0.79 inches long on each side) with a base that is at the back of the
head and connected to the camera by a thin 8" flat cable.  The base uses Wifi to conenct to a smartphone.  The base
also has a rechargeable battery in it and a USB connector to charge it. The camera can also be powered by the
USB connector which is how it is currently used. 

The skeleton body has the bottoms of the legs bent back on
the ground as if the prop is sitting on its knees and lower leg. The body has an iHome speaker (to talk and emit
audio),  an Adafruit micropone and amplifier module with AGC (to listen), a pneumatic cylinder and 12V solenoid valves to spring the
body with head from a leaning over position (parallel to the ground) to an upright position and vice versa.
The user has a Adafruit 9814 mic and line amp, with AGC disabled, that is connected thru wires to the speaker
that allows the user to talk out of the prop speaker. There is also a MidFly MP3 module that is conencted to
the Arduino and thru wires to the speaker that is used to play mp3 files.  
The body is attached to a base via a bolt hinge that allows it
to swing so it can either be leaning over or upright. The body is pushed/pulled by a pneumatic cylinder
to stand upright or lean over. The pneumatic cylinder is controlled by the solenoid valve which the main controller controls.
Elastic cables and pneuamtic speed controllers are used to slow the pneumatic cylinder as it nears its end
points, either upright or leaning over. The pneumatics have not been used in the past few years as I have been
concentrating on the servo operation. The right skeleton arm has 3 servos at the shoulder to for pitch, yaw,
and roll and one at the elbow to bend the elbow. All servos except the mouth are held in an Actobotics servo
block to withstand lateral forces off the servo axis.
Mostly Actobotics hardware, such as screws, hubs, spacers, brackets, channels, patterns, bearings, etc, are
used to connect the servos blocks to the arm/head.
The servos are run at 6 volts with the exception of the arm pitch servo being run at 7.4 volts to get the needed speed and torque.
GoBilda servos are used for the arm and elbow, while Hitec are used for the head and mouth (see Prop Wiring.docx for detail).
GoBilda servos are dead quiet when holding a position even when under load so are perfect for the application.  
Hitec servos tend to make a high pitched whine when holding a position under load. 
Hitec servos were used when the head was first animated before it was discovered much later on that GoBilda servos would be
better in that case.  Eventually the head nod servo will be replaced with a GoBilda servo as it is the one Hitec servo with the most noticable whine.
All the servos allow a farily fluid/natural/and speedy(when needed) movement of the skeleton head and arm/forearm. 
The clothes on the skeleton body came from an old Halloween costume.

To easily allow a user to naturally manipulate the prop for live interactive sessions as well as catpure for playback,
Adafruit BNO055 Inertial Measurment Units (IMUs) are attached to the user and the servos can be synchronized to the movements of
the user thru software. Currently 1 IMU is used on the top of the head (using a ball cap),  1 on the mouth
(using a mouth guard),
and two on a simulated arm/forearm in the interim until I can get them to work on an actual arm.
The Arduino I2C interface is used to access these IMUs.


The controller is an Arduino Mega 2560.  
Arduino Interfaces used:
    - 7 of its 12 PWM outputs are used for jitter free control of the 7 servos.  
    - 1 digital output is used to control the pneumatic relay control to set the pneumatic cylinder either fully extended or 
        fully retracted.  This output goes to a transistor circuit with fly back diode then to the pneumatic relay control in the prop.
    - 1 digital output is used to turn the Eye LEDs on or off through a resistor.
    - The USB connection on the Arduino is used to both program the Arduino and communciate with the running program thru serial commands
      and responses
    - The I2C bus is used to interface to an I2C switch which interfaces to 2 IMUs
      on one channel and 2 on another channel to resolve I2C address bus conflicts as the IMUs can only have
      one of two I2C addresses.
    - 1 TTL serial interface to control an MP3 module to generate audio and play audio files from an SD card on the MP3 module.  The audio output
    of that MP3 goes to the speaker
    - 1 digital input pulled up to 5 volts and used to read a button.
      
Software:
    The program is written in Arduino C++ and uses several libraries (some new DIY, some existing).  All code except for most of 
    the libraries was DIY. The user can control the program thru a serial command line interface on the USB
    serial line.  See \Halloween\PropController\PropController.ino for the commands. 
    Prop movement, LED, and back movement playback data is stored as constant arrays in the program itself
    although the future goal is to store it in a separate SD card the Arduino accesses for unlimited playback
    storage. These constants are stored in the PROGMEM2 section so they don't take up RAM space, only program code space.
    When using live interactive prop movement operations (command "ImuHeadMouth ...") the large output on the
    serial monitor that shows the servo positions, etc, can be captured by copying and pasting it into a text
    file then opening it as an Excel file and copying it to sheet VampireArmCapture of the excel file
    VampireArmCapture.xlsx. Once that is done the user can copy and transpose paste it from sheet
    VampireArmCapture to sheet 1 in the appropriate spot. At that point copy and paste from sheet 1 to the
    appropriate row in sheet 2.
    Then sheet 2 has the code snippet you can copy and paste into the PropController.ino file for playback later on.
    
Directories/files:

    \Halloween\PropController\ - Dir that contains the software program.  The Arduino PropController.ino (main file) and its
        supporting user files are contained here.
    \Halloween\NewAndModedLibraries\ - Dir that contains new or modified libraries.  These then zipped and imported into the
        Arduino IDE.
    \Halloween\QuickHeadMouthCaptureCommands.txt  - File that contains serial commands that were commonly used for prop operation on Halloween.
    \Halloween\Prop Wiring.docx  - MS Word file that contains the prop wiring information/schematic.
    \Halloween\ArmServoAngularAccelCalcs.xlsx - Excel file containing torque and speed calculations for the servos.  Also contains servo
        min,max degree and PWM pulse width calculations used when instantiating servo objects.
    \Halloween\*.mp3  - mp3 audio files that can be placed on the MP3 SD card renamed as 1.mp3, 2.mp3, etc,
    which the prop controller can direct the MP3 module to play.
    \Halloween\Lessons Learned.docx -  A lessons learned file along with future enhancements.
    
    There are several other files and directories in \Halloween\ but the significant ones are listed above.
    
URLs:
    Halloween Prop  https://photos.app.goo.gl/th4qkniJdXuoBmHA6 -  contains photos of the
        prop as well as some videos of the prop in action and demos of its range of motion.
    Halloween 2018  https://photos.app.goo.gl/2tGpkc9Z9Mq6irJE6 -
        Videos of the prop before arm movement was added.
Contacts:
    Greg Gemmer ghgemmer@gmail.com