/* WindSensor rev 9/21/2019
© 2014-2019 RoboSail
This program reads and displays data from the wind sensor, a continuous rotary
magnetic encoder with a 10 bit PWM output. (US Digital MA3-P10-25B)
It is used to verify that the sensor is connected and functioning correctly
and to calibrate the WindSensor position.
The code reads this in using the pulseIn function then maps it to the
desired range of -180 to 180 degrees. Both the pulse value and the
mapped values are displayed to the serial Monitor.

First the PWM signal from the sensor is read in.  Nominal values for
the position are 0 to 1023. Use the code to determine if the actual range
is smaller and if there are "dead spots". You can then change the map function
accordingly.  The input data and the corresponding angle are displayed to the serial monitor.

Calibrate the WindSensor by rotating the encoder body while keeping the windvane
pointing forward.  Tighten the encoder body to the mount when the value reads 0.
You will need a set of pliers and probably several tries.

The Wind Sensor servo is read on digital pin 7*/

#include <RoboSail_Hardware.h> //has pin definition


int windAngle = 0;
int windPulseWidth = 0;

void setup() {
  Serial.begin(115200);

  // Set WindSensor on digital input pins
  pinMode(ROBOSAIL_PIN_WIND, INPUT);
}

void loop() {
  // Read values from the WindSensor
  // pulseIn returns the width of the command pulse in microseconds.
  windPulseWidth = pulseIn(ROBOSAIL_PIN_WIND, HIGH);

  // Convert the wind angle to degrees from PWM values (nominally 1 - 1023) to range -180 to +180
  // Note that the the low value of the angle corresponds to the high value of the sensor
  windAngle = map(windPulseWidth,
                  ROBOSAIL_WIND_SENSOR_LOW, ROBOSAIL_WIND_SENSOR_HIGH, 180, -180);

  // The sensor occasionally returns out of bounds values, so make sure that
  //   it fits within our desired range.
  windAngle = constrain(windAngle, -180, 180);

  // Print out the values for debug.
  Serial.print("Pulse from Encoder: ");
  Serial.print(windPulseWidth);
  Serial.print("\t Mapped Angle: ");
  Serial.print(windAngle);
  Serial.println();

  // add delay to not overwhelm serial monitor (or the user!)
  delay(200);
}
