/* GPSTest rev 4/22/2016
© 2014-2016 RoboSail

This program reads the GPS module through the Arduino Mega.
It also test the libraries that convert the GPS latitude/longitude data (in degrees)
into x,y coordinates (in meters).
The user can determine the information that is printed to the Serial Monitor
by setting variables in the code to true or false.

Use the code to see that the wiring and the code libraries are set up correctly.
When the GPS first gets a "fix" on position, that position is defined as the 0,0.
Future positions are relative to (0,0) as on an x,y plane.
To change the (0,0) take the GPS to another spot and press the reset button  to a new (Need to rdefine the  on the Uno) control signals coming in from the Receiver and

Set Board to "Arduino Mega" for this code to compile
To run this code with the Arduino Uno, change "Serial1" to "Serial"

*/


#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <RoboSail_Hardware_Tests.h>
#include <UsefulCalcs.h>

Adafruit_GPS GPS(ROBOSAIL_SERIALPORT_GPS);

// set to 'true' if you want to print the raw GPS sentences to Serial console
bool print_raw_gps = false;

// set to 'true' if you want to print the parsed GPS info to Serial console
bool print_parsed_gps = true;

// this will be false until GPS fix is found and starting position saved
bool start_pos_found = false;

// once GPS fix is found, these variables will be updated
float startPositionX = 0;
float startPositionY = 0;
float relPositionX = 0;
float relPositionY = 0;
float pos[2];
float angleFromStart = 0;

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  GPS.read(); // reads char (if available) into internal buffer in GPS object
}

// function to enable TIMER0 interrupt
void enableInterrupt() {
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

// function to print the GPS state
void PrintGPSInfo()
{
  Serial.print("\nTime: ");
  Serial.print(GPS.hour, DEC); Serial.print(':');
  Serial.print(GPS.minute, DEC); Serial.print(':');
  Serial.print(GPS.seconds, DEC); Serial.print('.');
  Serial.println(GPS.milliseconds);
  Serial.print("Date: ");
  Serial.print(GPS.month, DEC); Serial.print('/');
  Serial.print(GPS.day, DEC); Serial.print("/20");
  Serial.println(GPS.year, DEC);
  Serial.print("Fix: "); Serial.print((int)GPS.fix);
  Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
  if (GPS.fix)
  {
    Serial.print("Location: ");
    Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
    Serial.print(", ");
    Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
    Serial.print("Location (in degrees, works with Google Maps): ");
    Serial.print(GPS.latitudeDegrees, 4);
    Serial.print(", ");
    Serial.println(GPS.longitudeDegrees, 4);
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    Serial.print("GPS Angle: "); Serial.println(GPS.angle);
    Serial.print("Altitude: "); Serial.println(GPS.altitude);
    Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
  }
}

// function to get the position
void getposition()
{
  if (!start_pos_found)
  {
    // take in lat/lon degree values and return (x,y) in meters in pos array
    latLonToUTM(GPS.latitudeDegrees, GPS.longitudeDegrees, pos);
    startPositionX = pos[0];
    startPositionY = pos[1];

    Serial.println("Starting position found!");
    Serial.print("x = "); Serial.print(startPositionX);
    Serial.print("   y = "); Serial.println(startPositionY);
    Serial.print("  angle from start = "); Serial.println(angleFromStart);
    Serial.println();

    start_pos_found = true;
  }
  else // starting position was found
  {
    // take in lat/lon degree values and return (x,y) in meters in pos array
    latLonToUTM(GPS.latitudeDegrees, GPS.longitudeDegrees, pos);

    // calculate the boat position relative to where it was started
    relPositionX = pos[0] - startPositionX;
    relPositionY = pos[1] - startPositionY;
    angleFromStart = atan2(relPositionY, relPositionX) * 180 / 3.14;
    while (angleFromStart < 0){ angleFromStart += 360; }
    while (angleFromStart > 360){ angleFromStart -= 360; }

    Serial.print("x = "); Serial.print(relPositionX);
    Serial.print("   y = "); Serial.println(relPositionY);
  }
}

void setup()
{
  // initialize Serial console
  Serial.begin(115200);
  Serial.println("GPS test code");
  Serial.println();

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's
  GPS.begin(9600);

  // turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Set the update rate to 1 Hz
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // activate TIMER0 interrupt which goes off every 1 millisecond
  enableInterrupt();
}

void loop() // run over and over again
{
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived())
  {
    char* LastNMEA; // pointer to GPS data
    LastNMEA = GPS.lastNMEA(); // read the string and set the newNMEAreceived() flag to false
    if (!GPS.parse(LastNMEA)) {return; } // failed to parse a sentence; just wait for another

    if (print_raw_gps) {Serial.println(LastNMEA);}
    if (print_parsed_gps) {PrintGPSInfo();}

    if (GPS.fix)
    {
      getposition();
    }
  }

  // wait 2 seconds before repeating loop
  delay(2000);

}


