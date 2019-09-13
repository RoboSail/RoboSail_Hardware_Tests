/* SailServoTest rev 7/30/2017
   © 2014-2017 RoboSail
   Test the various sail positions available by driving the
   sail servo to positons entered by the user.
   The user types in the desired angle through the Serial Monitor.
   0 means the sail is fully in, and 90 means the sail is
   fully out (at 90 degrees).
   Note that the Sail Servo actual positions for full in and out
   (ROBOSAIL_SAIL_SERVO_LOW and ROBOSAIL_SAIL_SERVO_HIGH respectively)
   for 1 boat are approx 55 and 125, and they may vary for other boats.
   Use this code to check these values and adjust as necessary.
   Then map the user's desired angles to these values.

   The Sail servo is controlled on digital pin 9
*/

#include <Servo.h>
#include <RoboSail_Hardware.h>

Servo sailServo;    // define servo

// variable to store the servo position
int position = 0;

void driveSailServo(int sailPos)
{
  if ((sailPos >= ROBOSAIL_SAIL_ANGLE_LOW) && (sailPos <= ROBOSAIL_SAIL_ANGLE_HIGH))  // the command in degrees is valid
  {
    int servoPos = map(sailPos,
                       ROBOSAIL_SAIL_ANGLE_LOW, ROBOSAIL_SAIL_ANGLE_HIGH,
                       ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH);
    sailServo.write(servoPos);

    // print the converted value
    Serial.print("Comand sent to Servo: ");
    Serial.println(servoPos);
    Serial.println();
  }
  else
  {
    Serial.print("ERROR - sail position out of range: ");
    Serial.println(sailPos);
  }
}

void setup() {
  // Sets up communication with the serial monitor
  Serial.begin(115200);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}

void loop() {
  Serial.print("Enter desired sail angle (");
  Serial.print(ROBOSAIL_SAIL_ANGLE_LOW);
  Serial.print(" to ");
  Serial.print(ROBOSAIL_SAIL_ANGLE_HIGH);
  Serial.print("): ");
  while (Serial.available() == 0)
  {}
  position = Serial.parseInt();    // convert input to integer
  Serial.println(position);          // print what was entered

  // drive servo to position in variable 'position'
  //call function to do error checking and send command to servo
  driveSailServo(position);
}
