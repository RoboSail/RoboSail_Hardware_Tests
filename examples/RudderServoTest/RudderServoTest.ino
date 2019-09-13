/* RudderServoTest rev 7/30/2017
   © 2014-2017 RoboSail
   Test the various rudder positions available by driving the
   rudder servo to positons entered by the user.
   The user types in the desired angle through the Serial Monitor.
   -50 means the rudder is fully to port, and +50 means the rudder
   is fully to starboard.
   Note that the Rudder Servo actual center postion is 90, so
   the user's desired angles must be mapped in the code to these values.

   The Rudder servo is controlled on digital pin 8
   */

#include <Servo.h>
#include <RoboSail_Hardware.h>

Servo rudderServo;  // define servo

// variable to store the servo position
int position = 0;

void driveRudderServo(int rudderPos)
{
  if ((rudderPos >= ROBOSAIL_RUDDER_ANGLE_LOW) && (rudderPos <= ROBOSAIL_RUDDER_ANGLE_HIGH))
  {
    int servoPos = map(rudderPos,
                       ROBOSAIL_RUDDER_ANGLE_LOW, ROBOSAIL_RUDDER_ANGLE_HIGH,
                       ROBOSAIL_RUDDER_SERVO_LOW, ROBOSAIL_RUDDER_SERVO_HIGH);
    rudderServo.write(servoPos);

    // print out what was calculated
    Serial.print("Command sent to Servo: ");
    Serial.println(servoPos);
    Serial.println();
  }
  else
  {
    Serial.print("ERROR - rudder position out of range: ");
    Serial.println(rudderPos);
  }
}

void setup() {
  // Sets up communication with the serial monitor
  Serial.begin(115200);
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
}

void loop() {
  Serial.print("Enter desired rudder angle (");
  Serial.print(ROBOSAIL_RUDDER_ANGLE_LOW);
  Serial.print(" to ");
  Serial.print(ROBOSAIL_RUDDER_ANGLE_HIGH);
  Serial.print("): ");
  while (Serial.available() == 0)
  {}
  position = Serial.parseInt();   // convert input to integer
  Serial.println(position);      // print what was entered

  // drive servo to position in variable 'position'
  //call function to do error checking and send command to servo
  driveRudderServo(position);
}
