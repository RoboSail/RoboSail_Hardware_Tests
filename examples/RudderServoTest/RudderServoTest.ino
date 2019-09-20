/* RudderServoTest rev 7/30/2017
   © 2014-2017 RoboSail
   Test the various rudder positions available by driving the
   rudder servo to positons entered by the user.
   The user types in the desired angle through the Serial Monitor.
   0 means the rudder is fully to port, and 180 means the rudder
   is fully to starboard.
   Note that the Rudder Servo actual center postion is 90

   The Rudder servo is controlled on digital pin 8
   */

#include <Servo.h>
#include <RoboSail_Hardware.h>

Servo rudderServo;  // define servo

const int SERVO_LIMIT_LOW  = 0;
const int SERVO_LIMIT_HIGH = 180;

void driveRudderServo(int servoPos)
{
  // guard against values that are out of range
  if ((servoPos < SERVO_LIMIT_LOW) || (SERVO_LIMIT_HIGH < servoPos)) {
    Serial.print("ERROR - rudder servo position out of range: ");
    Serial.println(servoPos);
    return;
  }

  rudderServo.write(servoPos);

  // print out what was calculated
  int rudderPos = map(servoPos,
                      ROBOSAIL_RUDDER_SERVO_LOW, ROBOSAIL_RUDDER_SERVO_HIGH,
                      ROBOSAIL_RUDDER_ANGLE_LOW, ROBOSAIL_RUDDER_ANGLE_HIGH);
  Serial.print("Command sent to Servo: ");
  Serial.print(servoPos);
  Serial.print("\t Mapped to angle: ");
  Serial.println(rudderPos);
  Serial.println();
}

int getDesiredPosition() {
  Serial.print("Enter desired rudder servo position (");
  Serial.print(SERVO_LIMIT_LOW);
  Serial.print(" to ");
  Serial.print(SERVO_LIMIT_HIGH);
  Serial.print("): ");

  // Block while waiting for input.  Input will not be sent by the terminal
  // until the user presses the enter key
  while (Serial.available() == 0) {}

  // Now that we have input, process all of it.  In case multiple values are
  // sent, we only read the last valid integer
  int enteredValue = -1;
  while (Serial.available() > 0) {
    // Peek at the first byte (to decide whether we will eventually keep it)
    // then read an integer from the input (which consumes the bytes)
    int aByte = Serial.peek();
    int parsedValue = Serial.parseInt();

    if (aByte == 10) {
      // ASCII value 10 means the enter key -- we don't want that input.
      Serial.print("(discarded newline) ");
    } else {
      // convert input to integer and tell the user what it was parsed as
      enteredValue = parsedValue;
      Serial.print("(received ");
      Serial.print(enteredValue);
      Serial.print(") ");
    }
  }
  Serial.println();

  return enteredValue;
}

void setup() {
  // Sets up communication with the serial monitor
  Serial.begin(115200);
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
}

void loop() {
  int servoPos = getDesiredPosition();
  driveRudderServo(servoPos);
}
