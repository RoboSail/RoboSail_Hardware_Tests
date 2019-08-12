#ifndef RoboSail_Hardware_h
#define RoboSail_Hardware_h
/*

This file is included by all the hardware tests.
It records the pin assignments and calibration data
specific to one sailboat's hardware

*/

#include <Arduino.h>

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

// Compass hard iron calibration
const float ROBOSAIL_HARDIRON_X = -8.41;
const float ROBOSAIL_HARDIRON_Y = -8.00;
const float ROBOSAIL_HARDIRON_Z = 33.32;

// Compass declination
// Source: http://www.ngdc.noaa.gov/geomag-web/#igrfwmm
const float ROBOSAIL_DECLINATION = -14.6067;

// Rudder limits
const int ROBOSAIL_RUDDER_LOW  = 1100;   //nominal 1000
const int ROBOSAIL_RUDDER_HIGH = 1900;   //nominal 2000

// Sail limits
const int ROBOSAIL_SAIL_LOW  = 1000;    //nominal 1000
const int ROBOSAIL_SAIL_HIGH = 2000;    //nominal 2000

// Wind limits
const int ROBOSAIL_WIND_LOW  = 0;       //nominal 0
const int ROBOSAIL_WIND_HIGH = 1023;    //nominal 1023

#endif