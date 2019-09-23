/* RudderServoTest rev 7/21/2019
   © 2014-2019 RoboSail
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
#include <RoboSail_Hardware.h>  // has pin definition

Servo rudderServo;  // define servo

// variable to store the servo position
int position = 0;

void setup() {
  // Sets up communication with the serial monitor
  Serial.begin(115200);
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
}

void loop() {
  Serial.print("\nEnter desired rudder angle (-50 to 50): ");
  while (Serial.available() == 0)
  {}
  position = Serial.parseInt();   // convert input to integer
  Serial.println(position);      // print what was entered

  // drive servo to position in variable 'position'
  //call function to do error checking and send command to servo
  driveRudderServo(position);
}
void driveRudderServo(int rudderPos)
{
  if ((rudderPos >= -50) && (rudderPos <= 50))
  {     //rudder centers on 90 on a standard 0-180 servo
    rudderPos = map(rudderPos, -90, 90, 0, 180); 
    rudderServo.write(rudderPos);
        // print out what was calculated
    Serial.print("Command sent to Servo: ");
    Serial.println(rudderPos);
  }
  else 
    {
    Serial.print("ERROR - rudder position out of range: ");
    Serial.println(rudderPos);
    }
}
