/* SailServoTest rev 9/21/2019
   © 2014-2019 RoboSail
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
#include <RoboSail_Hardware.h>  // has pin definition

Servo sailServo;    // define servo

// variable to store the servo position
int position = 0;

void setup() {
  // Sets up communication with the serial monitor
  Serial.begin(115200);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}

void loop() {
  Serial.print("\nEnter desired sail angle (0 to 90): ");
  while (Serial.available() == 0)
  {}
  position = Serial.parseInt();    // convert input to integer
  Serial.println(position);          // print what was entered

  // drive servo to position in variable 'position'
  //call function to do error checking and send command to servo
  driveSailServo(position);
}

void driveSailServo(int sailPos)
{
  if ((sailPos >= 0) && (sailPos <= 90))  // the command in degrees is valid
  {
    sailPos = map(sailPos, 0, 90, 55, 125);
    sailServo.write(sailPos);
        // print the converted value
    Serial.print("Command sent to Servo: ");
    Serial.println(sailPos);
  }
  else 
  {
    Serial.print("ERROR - sail position out of range: ");
    Serial.println(sailPos);
    }
}
