/*
  Be carefull this code is not working as expected.
  We used a Shield V2.0:
  http://www.seeedstudio.com/wiki/Music_Shield_V2.0
  The aim wass to produce a music while counting and then depending on a treshold, play a specific music.
*/
#include <math.h>
#include <stdlib.h>
#include "Counter.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include <NewSPI.h>
#include <arduino.h>
#include "pins_config.h"
#include "vs10xx.h"
#include "newSDLib.h"
#include "MusicPlayer.h"

#define TIMER_LENGTH 3000

// Pins used
int TSL235R = 5; //Out of TSL235R connected to Digital pin 5

// Counter function
HardwareCounter hwc(TSL235R, TIMER_LENGTH); //assign a pin and a delay to the counter

//creation of a Music Player
MusicPlayer myplayer;

// Setup of the system
void setup()
{
  Serial.begin(9600);

  // Declare the pin such as an input of data
  pinMode(TSL235R, INPUT);
  Serial.println("Testing a TSL235R sensor and sound:");  // Splash screen
  Serial.println("-------------------------");
  Serial.println();

  //initialize player
  myplayer.begin();


  // Set up the counter for the first time
  hwc.start(); //starts counting start_time = millis()
}

// Loop function that is continuously executed
void loop()
{
  Serial.print("Start \n");

  //song while counting
  myplayer.addToPlaylist("waiting.mp3");

  if (hwc.available()) //if the counter is over : returns (now - _start_time >= _delay);
  {

    long count = hwc.count(); //get count the result
    Serial.print("Count: ");
    Serial.println(count);
    if (count < 900000) // Depending on the intensity of the light, play a different music
    {
      //song
      myplayer.addToPlaylist("OK.mp3");

    } else
    {
      //song
      myplayer.addToPlaylist("alert.mp3");


    }
    //reset the counter for next counting
    hwc.start(); //starts counting start_time = millis()
  }
  myplayer.playList();
  while (1);

}

