/*************************************************** 
  This is an example for the SHTC3 Humidity & Temp Sensor

  Designed specifically to work with the SHTC3 sensor from Adafruit
  ----> https://www.adafruit.com/products/4636

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/

#include "Adafruit_SHTC3.h"
#include <Arduboy2.h>

Arduboy2 arduboy;

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

void setup() {
  arduboy.begin();
  PRR0 &= ~_BV(PRTWI);
  shtc3.begin();
  arduboy.setFrameRate(1);
}


void loop() {
  if(!arduboy.nextFrame()) return;
  arduboy.clear();
  arduboy.setTextSize(2);
  sensors_event_t humidity, temp;
  
  shtc3.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  arduboy.print("T: "); arduboy.print(temp.temperature*1.8 + 32); arduboy.print("\xF8"); 
  arduboy.setCursor(0, 32); arduboy.print("H: "); arduboy.print(humidity.relative_humidity); arduboy.print("%"); 
  arduboy.setTextSize(1);
  arduboy.setCursor(108, 13); arduboy.println("F");
  arduboy.setCursor(110, 45);arduboy.println("rH");
  arduboy.display();
  delay(5000);
}
