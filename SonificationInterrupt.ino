/*
  Be carefull this code is not working as expected.
  We used a Shield V2.0:
  http://www.seeedstudio.com/wiki/Music_Shield_V2.0
  The aim wass to produce a music while counting and then depending on a treshold, play a specific music.
*/

#include <math.h>
#include <stdlib.h>
#include "InterruptCounter.h"

#include <SD.h> //supply the correct protocols for reading and parsing the micro SD card ->obligatory for Musicplayer
#include <SPI.h> //serial peripheral interface, what sends data between your Arduino and the Mmusic shield using the pins ->obligatory for Musicplayer
#include <arduino.h> // Arduino set of instructions -> obligatory to use arduino
#include <MusicPlayer.h> // to code up in keywords rather than having to scratch code for the SPI, SD and the VS1053B chip

#define TIMER_LENGTH 3000

// Pins used
int TSL235R = 3; //Out of TSL235R connected to Digital pin 3 (besoin de cette pin car Interrupt)

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
  myplayer.begin();  //will initialize the hardware and set default mode to be normal.

  // Set up the interrupt for the first time
  interruptCounterSetup(1, 10); //1 for the pin 3
}

// Loop function that is continuously executed
void loop()
{
  Serial.print("Start \n");

  //song while counting
  myplayer.playOne("waiting.mp3");
  myplayer.play();

  delay(3000);

  if (interruptCounterAvailable()) //if the counter is over
  {

    long count = interruptCounterCount(); //get count the result
    Serial.print("Count: ");
    Serial.println(count);

    if (count < 1900)
    {
      //song for low intensity
      myplayer.playOne("OK.mp3");

    } else
    {
      //song for high intensity
      myplayer.playOne("alert.mp3");
    }
  }
  myplayer.play();

  //reset the interruptCounter for next counting
  interruptCounterReset();

  // Wait before we start the next counting
  delay(3000);
}

