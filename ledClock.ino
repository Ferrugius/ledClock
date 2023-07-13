#include <Bitmap.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x12.h>
#include <ESP8266WiFi.h>

//wifi setup
const char* ssid = "your_ssid";  //wifi ssid
const char* password = "your_pass";   //wifi password

//display setup
#define DISPLAYS_WIDE 1 // Panel columns
#define DISPLAYS_HIGH 1 // Panel rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Number of P10 Panels used (COLUMN,ROWS)

//----------------------------------------------------------------------
// SETUP

void setup() {

  //wifi setup
  WiFi.begin(ssid, password);

  //time setup
  configTime("CET-1CEST,M3.5.0,M10.5.0/3", "tempus1.gum.gov.pl", "pl.pool.ntp.org");

  // display setup
  Disp.start(); // Run the DMDESP library
  Disp.setBrightness(100); // Brightness level
  Disp.setFont(ElektronMart6x12); // Specify a font
  
}



//----------------------------------------------------------------------
// LOOP

void loop() {

  Disp.loop(); // Run the Disp loop to refresh the LED

  //get and format raw time
  time_t rawTime;
  struct tm* timeinfo;
  time (&rawTime);
  timeinfo = localtime ( &rawTime );

  String dispTime = String(asctime(timeinfo)).substring(11,16);

  Disp.drawText(1,2, dispTime); // display the time

  //lower brightness between 19:00 and 8:00
  if (timeinfo->tm_hour+1 >= 19 || timeinfo->tm_hour+1 <= 8 ) {
    Disp.setBrightness(20); // Brightness level
  }
  else {
    Disp.setBrightness(100); // Brightness level
  }
}
