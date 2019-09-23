/* RCPassthrough rev 9/21/2019
© 2014-2019 RoboSail
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

When automatic control is implemented, the signals from the RC transmitter can 
be used to send switch signals or other cues to the boat to switch modes of operation.

Rudder and Sail data from the RC receiver are read in on 
digital pins 2 and 3 respectively.

Rudder and sail servos are controlled on digital 
pins 8 and 9 respectively.Pins are configured in RoboSail_Hardware.h
*/

#include <Servo.h>
#include <RoboSail_Hardware.h>

// variables to hold input and output values
int rudderPulseWidth, sailPulseWidth; //inputs 
int rudderDegrees, sailDegrees;       //calculated values
int rudderServoOut, sailServoOut;     //outputs 

//create servo objects
Servo rudderServo;
Servo sailServo;

void setup() 
{
  Serial.begin(115200);
  Serial.println("\nRCPassThrough code - RoboSail");
  declarePins();  // Setup all input and output pins using function below
}

void loop() {
  // Read commanded (manual) values from the RC reciever
  // pulseIn returns the width of the command pulse in microseconds.
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);

  // Calculate the commanded positions in degrees.
  rudderDegrees = map(rudderPulseWidth,
                      ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH,-50, 50);
  sailDegrees = map(sailPulseWidth,
                    ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH, 0, 90);

  // calculate the commanded positions into servo angles on the Robosail boat
  // the Rudder servo motor ranges from 0 to 180 with 90 deg in the center
  // the Sailwinch servo is at ~ 55 deg when full-in, which we think of as 0 deg,
  //  and ~125 deg when full out, which we thnk of as 90 deg
  rudderServoOut = map(rudderDegrees,-90, 90, 0, 180);
  sailServoOut = map(sailDegrees, 0, 90, ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH);

  // Print out the values for debug.
  Serial.print("Sail pulse from receiver: ");
  Serial.print(sailPulseWidth);
  Serial.print("\t Mapped Angle: ");
  Serial.print(sailDegrees);
  
  Serial.print("\t Rudder pulse from receiver: ");
  Serial.print(rudderPulseWidth);
  Serial.print("\t Mapped Angle: ");
  Serial.println(rudderDegrees);


  // Command the servos to move
  rudderServo.write(rudderServoOut);
  sailServo.write(sailServoOut);
}

void declarePins()
{
  // Set RC receiver on digital input pins
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);

  // attach the servos to the proper pins
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}
