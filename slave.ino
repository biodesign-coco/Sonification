// Wire Slave Receiver and Sender when request from Master

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006


#include <SD.h> //supply the correct protocols for reading and parsing the micro SD card ->obligatory for Musicplayer
#include <SPI.h> //serial peripheral interface, what sends data between your Arduino and the Mmusic shield using the pins ->obligatory for Musicplayer
#include <arduino.h> // Arduino set of instructions -> obligatory to use arduino
#include <MusicPlayer.h> // to code up in keywords rather than having to scratch code for the SPI, SD and the VS1053B chip


#include <Wire.h>

//creation of a Music Player
MusicPlayer myplayer;

//booleen to know if it is the end of the song
bool endOfSong = false;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event to be called when slave receive a transmission from master
  Wire.onRequest(requestEvent); // register a function when master request data from this slave
  Serial.begin(9600);           // start serial for output

  myplayer.begin();  //will initialize the hardware and set default mode to be normal.
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  char c = Wire.read(); // receive byte as a character
  if (c == 'c')
  {
    Serial.println("counting...");
    myplayer.playOne("waiting.mp3");
  }
  else if (c == 'l')
  {
    Serial.println("low freq");
    myplayer.playOne("OK.mp3");
  }
  else if (c == 'h')
  {
    Serial.println("high freq");
    myplayer.playOne("alert.mp3");
  }

  myplayer.play();
}

void requestEvent()
{
  Serial.print("is it the end of the song: ");
  Serial.println(endOfSong);
  Serial.print("recording state: ");
  Serial.println(myplayer.getRecordingState());
  //==> problem: is never = 3 (always = 0) --> try to find another way to find the end of the song
  if ( myplayer.getRecordingState() == 3) // if it is the end of the song.....how to know???
  {
    endOfSong = true;
    Serial.println("end of song.....true");
  }
  //si est à la fin de la chanson
  if (endOfSong)
  {
    Serial.println("The end of the song!");
    Wire.write(1);
  } else {
    Wire.write(0);
    }
}
