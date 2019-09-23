/* RCReader rev rev 9/21/2019
© 2014-2019 RoboSail
This program puts the Arduino micro-computer in the RC (Radio Control) system
It takes in the control signals coming in from the Receiver and
displays the following to the Serial Monitor:
  - The actual "pulse" coming in from the receiver for each channel
    (typical range of 1000 - 2000)
  - the angle at which the rudder or sail should be positioned
    given that command (in the RoboSail frame of reference)

This program helps the user determine
  - if they are reading good signals from the receiver (range of 1000 - 2000)
  - if the Arduino computer is functioning correctly

When automatic control is implemented, the signals from the RC transmitter can 
be used to send switch signals or other cues to the boat to switch modes of operation.

Rudder and Sail data from the RC receiver are read in on
digital pins 2 and 3 respectively.
*/

#include <RoboSail_Hardware.h> //has pin definitions

// variables to hold input values
int rudderPulseWidth;
int sailPulseWidth;

void setup() {
  Serial.begin(115200);
  Serial.println("\nRCReader code - RoboSail");
  // Set RC receiver on digital input pins
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);
}

void loop() {
  // Read commanded (manual) values from the RC reciever
  // pulseIn returns the width of the command pulse in microseconds.
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);

  // Print out the values for debug.
  Serial.print("Sail pulse from receiver: ");
  Serial.print(sailPulseWidth);

  Serial.print("\t\t Rudder pulse from receiver: ");
  Serial.println(rudderPulseWidth);

}
