/*
  APDS9960 - Proximity Sensor

  This example reads proximity data from the on-board APDS9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor
  every 100ms.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>
#include <Arduboy2.h>
Arduboy2 arduboy;
BeepPin2 beep;
float frequency = 523.251;
int proximity = 0;
int preprox;
int rectY = 0;
int rectX = WIDTH/2;
int rectSize = 1;
void setup() {
  arduboy.begin();
  beep.begin();
  arduboy.clear();
  PRR0 &= ~_BV(PRTWI);
  APDS.begin();
}

void loop() {
  // check if a proximity reading is available
  if(!arduboy.nextFrame()) return;
  arduboy.clear();
  
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    proximity = APDS.readProximity();
    
    // print value to the Serial Monitor
  }
  rectSize = proximity / 5;
  frequency = proximity;
  beep.tone(beep.freq(frequency));
  if (rectX + rectSize <WIDTH) rectX = proximity/2;
  //rectY = proximity/4;
  //arduboy.print("Proximity: ");
  arduboy.fillRect(rectX, rectY, rectSize, rectSize);
  //arduboy.println(proximity);
  arduboy.display();
  //delay(100);
}
