//for help look at: https://github.com/Starmbi/hp_BH1750/wiki
#include <Arduino.h>
#include <hp_BH1750.h>  //inlude the library
hp_BH1750 BH1750;       //create the sensor object
#include <Arduboy2.h>

Arduboy2 arduboy;

float lux = 0.00;
void setup()
{
  // put your setup code here, to run once:
  arduboy.begin();
  PRR0 &= ~_BV(PRTWI); 
  //Serial.begin(9600);
 
  bool avail = BH1750.begin(BH1750_TO_GROUND);   // will be false no sensor found
                                                 // use BH1750_TO_GROUND or BH1750_TO_VCC depending how you wired the address pin of the sensor.
  
  // BH1750.calibrateTiming();  //uncomment this line if you want to speed up your sensor
  BH1750.start();               //start the first measurement in setup
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame()) return;
  arduboy.clear();
  if (BH1750.hasValue() == true) {    // non blocking reading
    lux = BH1750.getLux();
    BH1750.start();
  }
  arduboy.setTextSize(2);
  arduboy.fillRect(0, 32, lux, 15);
  arduboy.print(lux);
  arduboy.print(" Lux");
  arduboy.display();
  //  do a lot of other stuff here, while sensor is waiting for the result...
}
