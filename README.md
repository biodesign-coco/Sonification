# Sonification
Arsenic sonification in Biodesign for a real world

Unzip Music_Box.zip and open the MusicBox.ino file in the Arduino Software
Branch the USB cable of the Arduino to your computer. 
Click on Verify and Upload on the Arduino software and read the following instructions : 

HOW TO USE IT

1) A blue LED means the device is ready to be started.

2) Press one of the button. There are two buttons, one round RED and one squared GREEN. The two are giving rise to different melodies. 
The device starts counting light intensity. The LED will turn white.
You will hear a specific music while the device is counting.

2) When it is done counting, a different music is being played depending on the measured
light intensity:
- If the number of counts is over 900000, the LED is turned RED and 
the music being played is stressful (if there is a strong light intensity, it
should mean in the final prototype that the arsenic concentration is too high in the sample).
- If the number of counts is below 900000, the LED is turned GREEN and the music
being played sounds less stressful. It means that the arsenic concentration is below
the dangerous threshold.

3) After hearing the second music, you can push one of the button and the counting
will start again. The LED will be BLUE again.

4) You can also turn the potentiometers :
- to increase or decrease the volume of the piezo speaker 
- to increase or decrease the speed of the music
(only for the music when the prototype is counting).

note: if you want to test a strong light intensity, you have to add a source
of light in front of the light-to-frequency converter (from your mobile phone for example).

