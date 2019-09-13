
/* RCPassthrough rev 4/8/2016

© 2014-2016 RoboSail
This program puts the Arduino micro-computer in the RC (Radio Control) system
It takes in the control signals coming in from the Receiver and
pass them back to the Rudder and Sail servo motors on the boat.
It also displays several values to the Serial Monitor:
  - The actual "pulse" coming in from the receiver for each channel
    (typical range of 1000 - 2000)
  - the angle at which the rudder or sail should be positioned
    given that command (in the RoboSail frame of reference)

This program helps the user determine
  - if they are reading good signals from the receiver (range of 1000 - 2000)
  - if the servos are functioning correctly and moving to the expected positions
  - if the Arduino computer is functioning correctly

Pins are configured in RoboSail_Hardware.h

*/

#include <Servo.h>
#include <RoboSail_Hardware.h>

// variables to hold input and output values
int rudderPulseWidth;
int rudderDegrees;
int rudderServoOut;
int sailPulseWidth;
int sailDegrees;
int sailServoOut;

//create servo objects
Servo rudderServo;
Servo sailServo;

void declarePins()
{
  // Set RC receiver on digital input pins
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);

  // attach the servos to the proper pins
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nRCPassThrough code - RoboSail");
    // Set RC receiver and WindSensor on digital input pins
    declarePins();
}

void loop() {
  // Read commanded (manual) values from the RC reciever
  // pulseIn returns the width of the command pulse in microseconds.
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);

  // Calculate the commanded positions in degrees.
  rudderDegrees = map(rudderPulseWidth,
                      ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH,
                      ROBOSAIL_RUDDER_ANGLE_LOW, ROBOSAIL_RUDDER_ANGLE_HIGH);
  sailDegrees = map(sailPulseWidth,
                    ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH,
                    ROBOSAIL_SAIL_ANGLE_LOW, ROBOSAIL_SAIL_ANGLE_HIGH);

  // calculate the commanded positions into servo angles on the Robosail boat
  // the Rudder servo motor ranges from 0 to 180 with 90 deg in the center
  // the Sailwinch servo is at ~ 55 deg when full-in, which we think of as 0 deg,
  //  and ~125 deg when full out, which we thnk of as 90 deg
  rudderServoOut = map(rudderPulseWidth,
                       ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH,
                       ROBOSAIL_RUDDER_SERVO_LOW, ROBOSAIL_RUDDER_SERVO_HIGH);
  sailServoOut = map(sailPulseWidth,
                    ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH,
                    ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH);


  // Print out the values for debug.
  Serial.print("Rudder pulse from receiver: ");
  Serial.print(rudderPulseWidth);
  Serial.print("\t Mapped Angle: ");
  Serial.print(rudderDegrees);

  Serial.print("\t Sail pulse from receiver: ");
  Serial.print(sailPulseWidth);
  Serial.print("\t Mapped Angle: ");
  Serial.println(sailDegrees);

  // Command the servos to move
  rudderServo.write(rudderServoOut);
  sailServo.write(sailServoOut);

}
