/*

This code demonstrates the conversion between GPS lat/lon and UTM.

It does the calculation once and then halts.

*/

#include <RoboSail_Hardware_Tests.h>

float pos[2];
float lat = 42.36;
float lon = -71.06;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Call the calculator object
  atLonToUTM(lat, lon, pos);
  Serial.print("Pos x: ");  Serial.println(pos[0]);
  Serial.print("Pos y: ");  Serial.println(pos[1]);
  delay(500);
}
