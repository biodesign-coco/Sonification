#include <math.h>
#include <stdlib.h>
#include "Counter.h"
#include "pitches.h"

// note
int note = NOTE_C4;
int autreNote = NOTE_AS6;

//melody alerte

int alerte[] = {NOTE_G5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5};
int DurationAlert[] = {8, 8, 8, 8, 8};

//melody itsok

int itsok[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int DurationItsok[] = {4, 8, 8, 4, 4, 4, 4, 4 };

//melody counting

int melody[] = {
  NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_A3, 0, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_A3, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_A3
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 3, 1, 2, 2, 2, 2, 3, 1, 2, 2, 8, 1, 1, 3, 1, 2, 2, 2, 2, 3, 1, 2, 4, 1, 1, 2, 2, 2, 2, 2, 2, 3, 1, 2, 4, 1, 1, 6
};


#define TIMER_LENGTH 3000



// Pins used
int TSL235R = 5; //Out of TSL235R connected to Digital pin 5
int noiseMaker = 8; //Out of the piezo connected to Digital pin 8


// Counter function
HardwareCounter hwc(TSL235R, TIMER_LENGTH); //assign a pin and a delay to the counter


// Setup of the system
void setup()
{
  Serial.begin(9600);
  // Declare the pin such as an input of data
  pinMode(TSL235R, INPUT);
  Serial.println("Testing a TSL235R sensor and sound:");  // Splash screen
  Serial.println("-------------------------");
  Serial.println();
}


// Loop function that is continuously executed
void loop()
{
  Serial.print("Start \n");

  // Set up the counter
  hwc.start(); //starts counting start_time = millis()

  //delay(TIMER_LENGTH); //time between start of the counter and print

  //tone( do a melody while counting

  for (int thisNote = 0; thisNote < 52; thisNote++) {

    int noteDuration = noteDurations[thisNote] * 95;
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8);
  }

  if (hwc.available()) //if the counter is over : returns (now - _start_time >= _delay); 
  {
    long count = hwc.count(); //get count the result
    Serial.print("Count: ");
    Serial.print(count);
    Serial.print("\n"); //jump to next line
    if (count < 900000)
    {
      //tone(noiseMaker, autreNote, 20000);

      for (int thisNote = 0; thisNote < 8; thisNote++) {

        int noteDuration = 1000 / DurationItsok[thisNote];
        tone(8, itsok[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(8);
      }


    } else
    {
      //tone(noiseMaker, note, 20000);

      for (int thisNote = 0; thisNote < 5; thisNote++) {

        int noteDuration = 1000 / DurationAlert[thisNote];
        tone(8, alerte[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(8);
      }

    }
  }
  // Wait before we start the next counting
  delay(3000);
}

