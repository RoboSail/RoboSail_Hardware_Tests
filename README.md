RoboSail Hardware Tests
=======================


Includes folders for each major hardware component, with usage examples inside.

> Note: this repository was formerly the `hardware` folder


Pinout and Interrupts
-----------------------

Pin | Assignment
----|-------------------------
2   | RC receiver rudder
3   | RC receiver sail
8   | Servo rudder
9   | Servo sail

Interrupt | Assignment
----------|-------------------------
0         | RC receiver pulse in rudder
1         | RC receiver pulse in sail


Arduino Pin Code

```c++
// Pin assignments
const int ROBOSAIL_PIN_RUDDER_RC    = 2;
const int ROBOSAIL_PIN_SAIL_RC      = 3;
const int ROBOSAIL_PIN_WIND         = 7;
const int ROBOSAIL_PIN_RUDDER_SERVO = 8;
const int ROBOSAIL_PIN_SAIL_SERVO   = 9;
const int ROBOSAIL_INTERRUPT_SAIL   = 1;
const int ROBOSAIL_INTERRUPT_RUDDER = 0;
```

# New Hardware Setup

This section only applies to people who want to follow along with their own hardware. If you're a RoboSail student you can skip this: it's already been done for you.

* Connections on Grove Seeeduino Mega shield which has servo connectors
* Cut V trace on board for separate power source to servo bus. Grounds stay connected
* Connect receiver to servo slots 11 (rudder STR), 12, (sail THR)
* Connect servos to servo slots 8 (rudder) and 9 (sailWinch).


## Calibration and Tuning

These boat constants will differ slightly for each set of hardware used. Each team should record and save the constants that are unique to their boat.

Variable            | Measured Value
--------------------|------------------
`RC_SAIL_MINIMUM`   |
`RC_SAIL_MAXIMUM`   |
`RC_RUDDER_MINIMUM` |
`RC_RUDDER_MAXIMUM` |
`SAIL_IN`           |
`SAIL_OUT`          |
`RUDDER_RIGHT`      |
`RUDDER_LEFT`       |
`WIND_MINIMUM`      |
`WIND_MAXIMUM`      |

Example values:

Variable            | Measured Value
--------------------|------------------
`RC_SAIL_MINIMUM`   | 1092
`RC_SAIL_MAXIMUM`   | 1892
`RC_RUDDER_MINIMUM` | 1096
`RC_RUDDER_MAXIMUM` | 1924
`SAIL_IN`           | 1200
`SAIL_OUT`          | 1892
`RUDDER_RIGHT`      | 1156
`RUDDER_LEFT`       | 1874
`WIND_MINIMUM`      | 0
`WIND_MAXIMUM`      | 1024

To calculate the values and tune the boat follow these steps:

### Sail Servo

1. Run [RCReader.ino](radiocontrol/RCReader/RCReader.ino) and open a terminal to examine the measured values.
2. Center all trim sliders on the RC transmitter.
3. Move the left stick (the "throttle") all the way down. Record the sail value as `RC_SAIL_MINIMUM`.
4. Move the left stick all the way up. Record the sail value as `RC_SAIL_MAXIMUM`.
5. Next, we will tune the hardware of the sailboat. Make sure you have a hex key tool.
6. Loosen the mainsheet and jibsheet from their booms so that they can slide freely.
7. Run [RCPassthrough.ino](radiocontrol/RCPassthrough/RCPassthrough.ino) and open a terminal to examine the measured values.
8. Move the left stick all the way down so that the sheets are hauled in.
9. Record the RC value as `SAIL_IN`.
10. Fix the mainsheet and jibsheet attachments to their booms so that the sails are on the boat centerline.
11. Gradually move the left stick up until the mainsail is at 90 degrees from the boat.
12. Record the value as `SAIL_OUT`.

### Rudder Servo

1. Run [RCReader.ino](radiocontrol/RCReader/RCReader.ino) and open a terminal to examine the measured values.
2. Center all trim sliders on the RC transmitter.
3. Move the right stick (the "steering") all the way right. Record the rudder value as `RC_RUDDER_MINIMUM`.
4. Move the right stick all the way left. Record the rudder value as `RC_RUDDER_MAXIMUM`.
5. Next, we will tune the hardware of the sailboat. You do not need any tools.
6. Run [RCPassthrough.ino](radiocontrol/RCPassthrough/RCPassthrough.ino) and open a terminal to examine the measured values.
7. Move the right stick right until the rudder is at it's maximum deflection. Record the rudder value as `RUDDER_RIGHT`.
8. Move the right stick left until the rudder is at it's maximum deflection. Record the rudder value as `RUDDER_LEFT`.

### Wind Sensor

1. Run [WindSensor.ino](wind/WindSensor/WindSensor.ino) and open a terminal to examine the measured values.
2. Next, we will tune the hardware of the sailboat.
3. Rotate the wind vane until the rollover point is found (eg, from 0 to 1024).
4. Loosen the wind vane sensor, and rotate it until the rollover point is set directly forward.
5. Fix the wind vane sensor in place.
6. Measure the minimum value of the wind sensor. Record this value as `WIND_MINIMUM`.
7. Measure the maximum value of the wind sensor. Record this value as `WIND_MAXIMUM`.

#  VARIABLES defined as Absolute and Relative

What is meant by Relative and Absolute

Relative is relative to the boat. Wind at the nose is 0 degrees, and it goes from 0-180 on the starboard side and 0 to -180 on the port side. A relative boat direction of 90 means turning the boat 90 degrees to starboard

Absolute is relative to the world. East is 0, and it increases in the counter clockwise direction. If the boat is at (0, 0) and the next waypoint is (-20, 20), the next waypoint is at an absolute heading of 135 degrees, regardless of which direction the boat is pointing at the moment

# Technical Notes

## Parts of a sailboat

![source: sailfree.com](sailboat.htm_txt_parts.gif)


## Characterize the Servos
Use the programs Rudderservotest and Sailservotest to find the servo limits and intermediate positions of the Servos.  The program asks for a position to send the motors to, the user enters it, then the program send the motor to that position.
The Rudder servo typically runs from 40 (full CW) to 140 (full CCW), center 90. Start with positions around 90 and move up/down from there.

The Sailwinch servo typically runs from 90 (full in) to 180 (full out).  Start with positions around 135 and move up/down from there
Record your values and use them in creating sailing algorithms.

## Reading and Checking the RC Transmitter/Receiver

The 2-channel RadioControl (RC) Transmitter/Receiver pair come with the sailboat.
The signals are originally used to directly control the servos. When the RoboSail
control system is installed, the signals from the Receiver are routed through the
Arduino, then processed before getting to the servo motors.

Use the example program `RCPassThrough` to check this communication.

To make automatic control, the outputs to the servo motors are based on the sensor
inputs, not the user inputs.  When automatic control is implemented, the signals from the RC transmitter can be used to send switch signals or other cues to the boat to switch modes of operation.

The Arduino Computer goes between the RC Transmitter/Receiver and the Servo Motors.
The signal that is read in from the receiver is a pulse read in with the pulseIn function. It typically goes from 1000 to 2000.   That number is mapped to the degrees that we define for the servo motion: The Rudder ranges -80 to +80 degrees with 0 at the center.  1000 maps to -80 while 2000 maps to +80 degrees. The Sailservo is a multiturn winch that we only use in 1 direction (so the line does not rewind in the other direction after unwinding). We define 0 degrees as the line (and the sail) is fully wound in and at 90 degrees the line (and the sail) is fully out. 1000 maps to 0 while 2000 maps to 90 degrees.

There is an additional step to create the proper command for the servo.  We need to create servo positions that correspond to the degree positions that we want.  Servos usually run from 0 to 180 degrees, however there may be physical limits that prevent full movement.  In this case, the rudder is a bit limited at the ends of its travel by the connecting rods.  The rudder servo has its center point at roughly 90 degrees.  The sail servo is at 90 when fully in, 90 when fully out, and 90 to 180 is not used as it would rewind the line.

Once the correct servo positions are calculated, they are output to the servos by on-board PWM facilities.


### `pulseIn()` vs ISR

The issue with `pulseIn()` is that sometimes it misses the start of the pulse, which makes the resultant output very twitchy:

`pulseIn()`
```
...
rudder, pulse: 1523	angle: 94
rudder, pulse: 1517	angle: 93
rudder, pulse: 1517	angle: 93
rudder, pulse: 1523	angle: 94
rudder, pulse: 1517	angle: 93
rudder, pulse: 1502	angle: 90
rudder, pulse: 1484	angle: 87
rudder, pulse: 1523	angle: 94
rudder, pulse: 1517	angle: 93
rudder, pulse: 1523	angle: 94
rudder, pulse: 1517	angle: 93
rudder, pulse: 1525	angle: 94
rudder, pulse: 1517	angle: 93
rudder, pulse: 1523	angle: 94
rudder, pulse: 1525	angle: 94
rudder, pulse: 1496	angle: 89
rudder, pulse: 1492	angle: 88
rudder, pulse: 1495	angle: 89
rudder, pulse: 1523	angle: 94
rudder, pulse: 1517	angle: 93
...
```

An interrupt service routine (ISR) solves this problem by using built-in [interrupts](http://arduino.cc/en/Reference/AttachInterrupt) to more accurately monitor the pulses from the RC receiver.

ISR
```
...
rudder, pulse: 1508	angle: 91		sail, pulse: 1364	angle: 65
rudder, pulse: 1508	angle: 91		sail, pulse: 1364	angle: 65
rudder, pulse: 1508	angle: 91		sail, pulse: 1364	angle: 65
rudder, pulse: 1508	angle: 91		sail, pulse: 1364	angle: 65
rudder, pulse: 1504	angle: 91		sail, pulse: 1372	angle: 65
rudder, pulse: 1504	angle: 90		sail, pulse: 1372	angle: 66
rudder, pulse: 1504	angle: 90		sail, pulse: 1372	angle: 66
rudder, pulse: 1504	angle: 90		sail, pulse: 1372	angle: 66
rudder, pulse: 1504	angle: 90		sail, pulse: 1372	angle: 66
rudder, pulse: 1508	angle: 91		sail, pulse: 1364	angle: 65
...
```

Notice that now we've gone from +-39 to +-4. Much better!

It's still not perfect, so a final solution might have a low pass filter that rejects small changes. Eg, something like:

```
if (abs((newValue - oldValue)) > 8) {
   // Only assign if the difference is greater than 8 units.
   result = newValue;
}
```


### Testing

Things to check when testing:

1. What is the minimum and maximum RC angle for the sail channel? rudder channel?
2. How does the RC transmitter trim affect the readings, for sail? for rudder?
3. How does the RC transmitter ST Rate knob affect the readings, for sail? for rudder?

### Credits

PWM modified from [here](http://www.camelsoftware.com/firetail/blog/radio/reading-pwm-signals-from-a-remote-control-receiver-with-arduino/)


## Calibrate the Wind Sensor

Our wind sensor is attached to the top of the mast and will return a value from -180 to 180.

It uses a 10-bit magnetic digital encoder that creates a digital pulse, the length of which corresponds to its rotary position. The code reads this in using the pulseIn function then maps it to the desired range of -180 to 180 degrees. Both the pulse value and the mapped values are displayed to the serial Monitor.

Nominal values for the position are 0 to 1023. Use the code to determine if the actual range is smaller and there are "dead spots".  You can then change the map function accordingly.

## Compass: Calibrate and Read
For Compass Heading there is an electronic magnetometer board that also includes a 3-axis accelerometer - Adafruit LSM-303DLHC. A magnetometer can be calibrated and will work fine on flat surfaces away from magnetic fields, however, a boat heels significantly. Therefore a compass need to be tilt-compensated. Information from the boards 3-axis magnetometer and 3-axis accelerometer are combined in some tricky software to give a compass reading within +-5°.

Hardiron calibration must be performed. The process is simple:

1. Mount the magnetometer in the location that you intend to use it at
2. Rotate the body through all possible orientations
3. Record the minimum and maximum for each axis of the magnetometer
4. Average the minimum and maximum for each axis. This will give you your hardiron x,y,z offsets.

(Need more data here about tilt-compensation)


### How to use Adafruit LSM303 3-axis magnetometer and 3-axis accelerometer for RoboSail Boats

Find these programs in the "hardware --> compass" folder and use in this order:

1. compassBasic - verify hardware and connections prints raw accelerometer and magnetometer readings to the screen
2. compassCalibration - Code to use to determine hard iron calibration values for other the programs
3. compassBasicwithCalibration - same as CompassBasic with hardiron correction
4. compassTest - Tilt-compensated compass with hard-iron correction.  Uses the Orientation library
5. compassBasicwithCalibrationandTilt - same as CompassTest, but does the tilt-compensation in the code and does NOT require the Orientation library

Find Orientation libraries in the folder Libraries --> Orientation:
	Orientation.cpp - Library for tilt calibrated compass readings
	Orientation.h - Header file for library

The roll, pitch, yaw, and headings all use the standard (Aircraft)
orientations:
https://en.wikipedia.org/wiki/Aircraft_principal_axes

* A positive roll angle lifts the left wing and lowers the right wing.
* A positive pitch angle raises the nose and lowers the tail.
* A positive yaw, or heading angle, moves the nose to the right.
* A yaw of 0 degrees is pointing towards Magnetic North.
* Heading ranges from 0 to 360 degrees.
* A heading of 0 degrees is pointing towards True North.
* A heading of 90 degrees is pointing East, 180 is South, 270 is West.

For RoboSail we change to a different frame of reference where East is 0 deg,
North is 90 deg, West ia 180 deg, and South is 270 deg. To get this do
RoboSailHeading = (360 - heading) + 90
We also use roll to find the heel of the boat.
We define Positive roll as leaning to Port and Negative roll as leaning to Starboard.
To get this simply negate roll.  RoboSailRoll = -1 * roll

Because of the way the calculations are done, the heading will not be
accurate if the pitch approaches 90 or -90, but that shouldn't be a
problem (unless the boat is sinking it shouldn't be pointing straight up
or down). We found the compass readings are accurate to about +-5% even if the
boat is heeling at angles it would see in normal sailing.
This accuracy sounds good, but realize that on 360 deg, it is up to +-18 deg.

Thanks to:
Benjamin Kraus, ben@kraus.info
Cody Lewis, srlm@srlmproductions.com

### Example outputs

CompassCalibration code startup
![CompassCalibration code startup](CompassCalibrationStartup.png)

CompassCalibration operation, after rotating the compass to calibrate
![CompassCalibration operation](CompassCalibrationOperation.png)


## GPS: Read

The GPS sensor can be mounted inside or outside the boat in such a way that it has a clear view of the sky with nothing shielding its view. The GPS provides location information in degrees latitude and longitude and updates this information every second.  To do this it must have a "clear view of the sky" and so it can get a fix from 3 satellites, (though it can work with only 1).  An additional antenna is used to  improve reception.  It must be mounted horizontal, but can be in the hull of the boat.

Latitude and Longitude are read in degrees and minutes and cover the entire world.  Software has been provided (in the UsefulCalcs library) that converts the latitude and longitude degrees into a simple x, y grid using a method called UTM (Universal Transverse Mercator).  The accuracy is still only +-2 meters, but the numbers are much easier to use.

Need GPS part data and connections info.
