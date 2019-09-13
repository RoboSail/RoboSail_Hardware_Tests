#ifndef RoboSail_Hardware_h
#define RoboSail_Hardware_h
/*

This file is included by all the hardware tests.
It records the pin assignments and calibration data
specific to one sailboat's hardware

*/

#include <Arduino.h>

// To ensure that settings are being read from this file, you can
// print the boat name in your setup() function as follows:
//   Serial.print("This boat is "); Serial.println(ROBOSAIL_BOAT_NAME);
const String ROBOSAIL_BOAT_NAME = "My Example Boat";

/********************** DEVICE INPUT AND OUTPUT ******************************/

// input pins from receiver
const int ROBOSAIL_PIN_RUDDER_RC    = 2;
const int ROBOSAIL_PIN_SAIL_RC      = 3;

// Output pins to the servos
const int ROBOSAIL_PIN_RUDDER_SERVO = 8;
const int ROBOSAIL_PIN_SAIL_SERVO   = 9;

// Wind sensor is on an input pin
const int ROBOSAIL_PIN_WIND         = 7;

// The compass / accelerometer is an I2C device, attached to the I2C pins
//  and requires no special configuration here.

// The GPS is attached to a serial port, but that port depends on the board.
// Luckily, we can detect the board and set this appropriately.
// A good source of board names that are known by the preprocessor is:
//   https://arduino.stackexchange.com/a/21257/42393
#if defined(ARDUINO_AVR_MEGA)
  HardwareSerial* const ROBOSAIL_SERIALPORT_GPS = &Serial1;
#elif defined(ARDUINO_AVR_UNO)
  HardwareSerial* const ROBOSAIL_SERIALPORT_GPS = &Serial;
#else
  HardwareSerial* const ROBOSAIL_SERIALPORT_GPS = &Serial;
#endif

// Interrupts
const int ROBOSAIL_INTERRUPT_RUDDER = 0;
const int ROBOSAIL_INTERRUPT_SAIL   = 1;

/*************************** CALIBRATION DATA *******************************/

// Fill in these values based on the results of hardware testing

// Compass hard iron calibration using compassCalibration sketch
const float ROBOSAIL_HARDIRON_X = -8.41;
const float ROBOSAIL_HARDIRON_Y = -8.00;
const float ROBOSAIL_HARDIRON_Z = 33.32;

// Compass declination
// Source: http://www.ngdc.noaa.gov/geomag-web/#igrfwmm
const float ROBOSAIL_DECLINATION = -14.6067;

// Rudder limits using RCReader sketch
const int ROBOSAIL_RUDDER_RC_LOW  = 1100;   // nominal 1000
const int ROBOSAIL_RUDDER_RC_HIGH = 1900;   // nominal 2000

// Sail limits using RCReader sketch
const int ROBOSAIL_SAIL_RC_LOW  = 1090;    // nominal 1000
const int ROBOSAIL_SAIL_RC_HIGH = 1900;    // nominal 2000

// Wind limits using WindSensorTest sketch
// NOTE: these are the low and high values returned by the sensor itself.
//       But the highest value of the sensor corresponds to the lowest value
//       of the sail angle!  Be sure to negate this measurement if you map
//       to a wind angle.
const int ROBOSAIL_WIND_SENSOR_LOW  = 0;       // nominal 0
const int ROBOSAIL_WIND_SENSOR_HIGH = 1023;    // nominal 1023

// Rudder servo limits
const int ROBOSAIL_RUDDER_SERVO_LOW  = 0;      // nominal 0
const int ROBOSAIL_RUDDER_SERVO_HIGH = 180;    // nominal 180

// Sail servo limits
const int ROBOSAIL_SAIL_SERVO_LOW  = 55;       // nominal 55
const int ROBOSAIL_SAIL_SERVO_HIGH = 125;      // nominal 125

/*************************** HUMAN VALUES ************************************/

// Rudder angle range -- values a human understands
const int ROBOSAIL_RUDDER_ANGLE_LOW = -90;
const int ROBOSAIL_RUDDER_ANGLE_HIGH = 90;

// Sail angle range
const int ROBOSAIL_SAIL_ANGLE_LOW = 0;
const int ROBOSAIL_SAIL_ANGLE_HIGH = 90;

// Wind angle range
// As above, note that the range of the angle is inverted with respect to the
// range of the wind sensor itself
const int ROBOSAIL_WIND_ANGLE_LOW = -180;
const int ROBOSAIL_WIND_ANGLE_HIGH = 180;

/*************************** HARDWARE FUNCTIONS ******************************/


#endif
