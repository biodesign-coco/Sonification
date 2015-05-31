/* Example: TSL235R
   Collaborative ideas from:
   retrofelty, robtillaart, Gumpy_Mike, and madepablo
   
   Sensor:
   http://www.sparkfun.com/datasheets/Sensors/Imaging/TSL235R-LF.pdf
   
   Wiring:
   TSL235R    Arduino pins
   GND        GND
   Vcc        +5V
   Out        Digital pin 2
   
   Piezo speaker  Arduino Pins 
                  Digital pin 8 
                  GND
  
*/

// Pin definitions
# define TSL235R 2                      // Out of TSL235R connected to Digital pin 2

// Constants
int period = 1000;                     // Miliseconds of each light frecuency measurement
int ScalingFactor = 1;                 // Scaling factor of this sensor


// Variables
unsigned long counter = 0;             // Counter of measurements during the test
unsigned long currentTime = millis();  
unsigned long startTime = currentTime; 
volatile long pulses = 0;              // Counter of measurements of the TSL235R
unsigned long frequency;               // Read the frequency from the digital pin (pulses/second)


//Piezo

#include "pitches.h"

// note
int note = NOTE_C4;

/*
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
*/



void setup() {
  
  Serial.begin(9600);                           // Start and configure the serial port
  attachInterrupt(0, PulseCount, RISING);
  pinMode(TSL235R, INPUT);                    // Declare the pin such as an input of data
  Serial.println("Testing a TSL235R sensor:");  // Splash screen
  Serial.println("-------------------------");
  Serial.println(); 
 
}

 


void loop(){
    
  counter++;                           // Increase the number of measurement
  Serial.print(counter);               // Print the measurement number
  getfrequency();                      // Request to measure the frequency
  Serial.print("  ");
  Serial.print(frequency);             // print the frequency (pulses/second)
  Serial.print(" pulses/second    ");
  Serial.print("  ");
  
  //Piezo
  if (frequency > 200000) {
  // sound tone
  tone(8, note);
  }
  else {
  //turn off sound
  noTone(8);
  }  
  
  pulses = 0;                          // reset the pulses counter
  delay (4000);                        // wait 4 seconds until the next measurement
}


void PulseCount()
{
 pulses++;
}

unsigned long getfrequency () {
  noInterrupts();
  frequency = pulses /(period/1000);    // Calculate the frequency (pulses/second)
  interrupts();
  return (frequency);
}

