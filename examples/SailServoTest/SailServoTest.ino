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

const int SERVO_LIMIT_LOW  = 0;
const int SERVO_LIMIT_HIGH = 180;

void driveSailServo(int servoPos)
{
  // guard against values that are out of range
  if ((servoPos < SERVO_LIMIT_LOW) || (SERVO_LIMIT_HIGH < servoPos)) {
    Serial.print("ERROR - sail servo position out of range: ");
    Serial.println(servoPos);
    return;
  }

  sailServo.write(servoPos);

  // print out what was calculated
  int sailPos = map(servoPos,
                    ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH,
                    ROBOSAIL_SAIL_ANGLE_LOW, ROBOSAIL_SAIL_ANGLE_HIGH);
  Serial.print("Command sent to Servo: ");
  Serial.print(servoPos);
  Serial.print("\t Mapped to angle: ");
  Serial.println(sailPos);
  Serial.println();
}

int getDesiredPosition() {
  Serial.print("Enter desired sail servo position (");
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
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}

void loop() {
  int servoPos = getDesiredPosition();
  driveSailServo(servoPos);
}
