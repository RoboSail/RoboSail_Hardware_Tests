/* RCReader rev rev 7/30/2017
© 2014-2017 RoboSail
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

Rudder and Sail data from the RC receiver are read in on
digital pins 2 and 3 respectively.
*/

#include <Servo.h>
#include <RoboSail_Hardware.h>

// variables to hold input values
int rudderPulseWidth;
int sailPulseWidth;

// variables to hold recorded max and min
int rudderMin;
int rudderMax;
int sailMin;
int sailMax;

void setup() {
  Serial.begin(115200);
  Serial.println("\nRCReader code - RoboSail");
  // Set RC receiver on digital input pins
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);

  // Initialize max and min readings to out of range values
  rudderMin = 2000;
  rudderMax = 0;
  sailMin   = 2000;
  sailMax   = 0;

  // Print the boat's name (as defined in RoboSail_Hardware.h as an
  // explicit check that the settings file is being included properly
  Serial.print("This boat is "); Serial.println(ROBOSAIL_BOAT_NAME);
  Serial.println(__FILE__);  // prints the name (path) of this sketch
}

void loop() {
  // Read commanded (manual) values from the RC reciever
  // pulseIn returns the width of the command pulse in microseconds.
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);

  rudderMin = min(rudderMin, rudderPulseWidth);
  rudderMax = max(rudderMax, rudderPulseWidth);
  sailMin   = min(sailMin, sailPulseWidth);
  sailMax   = max(sailMax, sailPulseWidth);

  // Print out the values for debug.
  // Sail pulse with range (min and max recorded)
  Serial.print("From receiver: Sail Pulse: ");
  Serial.print(sailPulseWidth);
  Serial.print(" ");
  Serial.print(sailMin);
  Serial.print("-");
  Serial.print(sailMax);

  // Sail pulse with range (min and max recorded, with center)
  Serial.print("\t Rudder pulse: ");
  Serial.print(rudderPulseWidth);
  Serial.print(" ");
  Serial.print(rudderMin);
  Serial.print("-");
  Serial.print(rudderMax);
  Serial.print(" ctr ");
  Serial.println((rudderMax + rudderMin) / 2);

}
