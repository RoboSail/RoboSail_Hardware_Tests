/* CompassTest rev 7/22/2015
© 2014-2016 RoboSail
Tilt-compensated compass with hard-iron correction.
Uses the Orientation library created for roboSail
Standard compass headings range from 0 to 360 degrees.
A heading of 0 degrees is pointing towards True North.
A heading of 90 degrees is pointing East, 180 is South, 270 is West.

For RoboSail we change to a different frame of reference where East is 0 deg,
North is 90 deg, West ia 180 deg, and South is 270 deg. To get this do
RoboSailHeading = (360 - heading) + 90

We also use roll to find the heel of the boat.
We define Positive roll as leaning to Port and Negative roll as leaning to Starboard.
To get this simply negate roll.  RoboSailRoll = -1 * roll

Because of the way the calculations are done, the heading will not be
accurate if the pitch approaches 90 or -90, but that shouldn't be a
problem (unless the boat is sinking it shouldn't be pointing straight up
or down). We found the compass readings are accurate to about +-5% even if the
boat is heeling at angles it would see in normal sailing.
This accuracy sounds good, but realize that on 360 deg, it is up to +-18 deg.

*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Orientation.h>
#include <RoboSail_Hardware.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Orientation compass;
float roll;
float pitch;
float yaw;
float heading;
float robosailHeading;

void displayToScreen() // Display the results
{
  Serial.print("Roll: "); Serial.print(roll);
  Serial.print(", Pitch: "); Serial.print(pitch);
  Serial.print(", Yaw: "); Serial.print(yaw);
  Serial.print(",   Compass Heading: "); Serial.print(heading); Serial.print(" °");
  Serial.print(",   RoboSail Heading: "); Serial.print(robosailHeading); Serial.println(" °");
}


void setup() {
  Serial.begin(115200);

  // Print the boat's name (as defined in RoboSail_Hardware.h as an
  // explicit check that the settings file is being included properly
  Serial.print("This boat is "); Serial.println(ROBOSAIL_BOAT_NAME);
  Serial.println(__FILE__);  // prints the name (path) of this sketch

  while (!mag.begin() || !accel.begin())
  {
    Serial.println("no LSM303 detected ... Check the wiring");
    delay(2000); // wait and try again
  }

  Serial.print("Your hardiron values are");
  Serial.print("  X: "); Serial.print(ROBOSAIL_HARDIRON_X);
  Serial.print("  Y: "); Serial.print(ROBOSAIL_HARDIRON_Y);
  Serial.print("  Z: "); Serial.print(ROBOSAIL_HARDIRON_Z);
  Serial.println();
  Serial.println();

  // Set the calibration parameters
  compass.setParameters(&accel, &mag, ROBOSAIL_DECLINATION, ROBOSAIL_HARDIRON_X, ROBOSAIL_HARDIRON_Y, ROBOSAIL_HARDIRON_Z);
}

void loop() {
  // Get a compass reading
  compass.calculate(roll, pitch, yaw, heading);
  robosailHeading = (360 - heading) + 90;   //change from standard compass reading to RoboSail frame of ref
  if (robosailHeading >= 360) {robosailHeading -= 360;}

  displayToScreen();
  delay(300);
}
