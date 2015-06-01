// Wire Master Writer

// This example code is in the public domain.
#include <math.h>
#include <stdlib.h>
#include "Counter.h"

#include <Wire.h>

#define TIMER_LENGTH 3000

// Pins used
int TSL235R = 5; //Out of TSL235R connected to Digital pin 5

// Counter function
HardwareCounter hwc(TSL235R, TIMER_LENGTH); //assign a pin and a delay to the counter


bool readyToCount = true;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);

  // Declare the pin such as an input of data
  pinMode(TSL235R, INPUT);
  Serial.println("Testing a TSL235R sensor and sound:");  // Splash screen
  Serial.println("-------------------------");
  Serial.println();

  // Set up the counter for the first time
  hwc.start(); //starts counting start_time = millis()
}

void loop()
{
  if(readyToCount)
  {
    readyToCount = false;
    Serial.println("Start \n");
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write('c');
    Wire.endTransmission();
  }

  delay(5000);
  Wire.requestFrom(4, 1);    //request one byte from slave 4
  while (Wire.available() > 0) // when data is received from slave to master
  {
    byte c = Wire.read();    //receive one byte from slave and assign to variable c
    //if c is 1
    Serial.print("c is equal to: ");
    Serial.println(c);
    if (c == 1)
    {
      if (hwc.available()) //if the counter is over : returns (now - _start_time >= _delay);
      {
        long count = hwc.count(); //get count the result
        Serial.print("Count: ");
        Serial.println(count);
        Wire.beginTransmission(4); // transmit to device #4
        if (count < 900000)
        {
          Wire.write('l');        // sends five bytes
        } else
        {
          Wire.write('h');
        }
        Wire.endTransmission();    // stop transmitting

        Wire.requestFrom(4, 1);    //request one byte from slave 4
        while (Wire.available() > 0) // when data is received from slave to master
        {
          byte d = Wire.read();    //receive one byte from slave and assign to variable d
          Serial.print("d is equal to: ");
          Serial.println(d);
          //if d is 1, restard the counter
          if (d == 0)
          {
            //reset the counter for next counting
            hwc.start(); //starts counting start_time = millis()
            readyToCount = true;
          }
        }
      }
    }
 }
}
