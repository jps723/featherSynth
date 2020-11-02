# Feather Synth Build Notes 9/4/20

![The Feather Synth sits on top of a table next to a guitar pedal.  A hand is adjusting a knob on the pedal](https://github.com/jps723/featherSynth/blob/master/images/fullShot.png)

A dual-oscillator polyphonic synthesizer project in collaboration with [Bantam Tools](https://www.bantamtools.com/).  The [project build](https://www.hackster.io/news/create-a-synth-and-sequencer-using-bantam-tools-desktop-cnc-milling-machine-83a0fdb942a3) guide is available on Hackster.

**Design Notes:**

The hardware component of this project is centered around the Adafruit Feather M4 Express.  This board has two 12bit DAC pins allowing for stereo audio synthesis, however this project does not use any stereo effects and delivers a mono signal to a 3.5mm mono audio jack.  

The hardware design has 5 inputs in the form of 4 potentiometers and a tactile button.  There are exposed female headers for an Adafruit Feather M4 Express.  The board will only fit in one direction, with the microUSB port facing to the left.  

If you look at the [pinout](https://learn.adafruit.com/adafruit-feather-m4-express-atsamd51/pinouts) of the M4 Express, you’ll see that we are using analog pin A0 as our DAC/audio output, and A2-A5 as our analog inputs.  Our button connects to digital pin 5.

The base software for the device uses these inputs to control an auto-advancing sequence of notes.  The knobs control the root note, the scale (it comes pre-programmed with the 7 diatonic modes), the probability that the note will play, and the time delay between notes/tempo.  Pressing the button will cycle through different waveforms/oscillator types.

**Synthesizer Design**
The synth is a polyphonic dual-oscillator synthesizer, each with independent bi-quad filters and envelopes.  The envelope settings are static while the filters are set to Low Pass Filters with the frequency cutoff randomly changing between two static values based on probability (math within the software -- this is unrelated to the probability knob).   

**Controls**
Root Note (Tonic)
The note from which the scale begins.  By default the notes to choose from range from A0 to C8

**Scale Selector**
There are a total of seven scales to choose from, beginning with the major scale, and then each mode variant resulting in the 7 diatonic modes in western music.

**Probability**
The probability that the note will be played, as calculated by comparing the knob’s position to a randomly generated number. Ex. 0-100% chance of playing

**Tempo**
The overall tempo of the sequence as determined by delay between each note

**Waveform Selector**
This is a series of oscillator combinations that get cycled through using the button.

## **Code**
The code is broken up into two separate files:  

**featherSynth.ino**
This is our primary code and is broken up into two sections: setup and loop.  Setup runs once, while loop cycles through continuously after the setup code has been executed. All of the code above the setup() function is required to call the library we are using (Audio.h), call our reference file (scales.h), and initialize our global variables. All of the code below the main loop() are functions that are called from either within setup() or loop().

Setup() contains code for setting audio memory allocation, pin assignment, and a function called oscillatorSetup() that is used for setting initial values of our oscillators/envelopes, etc.  These will mostly get overwritten by the loop however we want to define our instrument before the program begins to cycle.  

loop() contains the bulk of our code. We have a function called buttonHandler() that is used for managing what we want to happen when we press the button. If you find this function below, you can add further oscillator combinations.  Our potentiometer readings are assigned to the Feather pins here as well. If you want to change the order of the knobs, do it here.

The nested for() loop is used to populate the rootScaled array.  This determines what notes are in the sequence and the order that they’re arranged in.  There are two arrangements to choose from, either climbing the scale, or random selection.  Only one can be used at a time.

The frequency is calculated using a formula that stems from midi note values which are a standard form of notation for relating to frequency.

The frequency cutoff is currently assigned a 50% chance of being 7000 hz, or 2000 hz.  Experiment with these numbers.

The probabilityOfPlaying variable is compared to a random value between 0 and 100.  Since probabilityOfPlaying is also a value between 0 and 100, this is treated as a percentage.  You can experiment with these values.

playOsc1() and playOsc2() functions take one argument (frequency) which is calculated via the explanation above.  These functions also contain the methods for dictating the ADSR envelope values which are hardcoded and can be adjusted and should be experimented with.  The filter frequency cutoff and delayTime are also embedded in these functions, with delayTime being used to set the time between notes (our tempo).

The buttonHandler function counts the button presses and uses that count to cycle through the 7 different oscillator combinations in the switch statement.



scales.h
scales.h is a reference file where we have all of our different scales stored.  The base code has 7 scales (each of the diatonic modes) spread out across two octaves, with the root note at each octave playing at a 3:1 ratio to everything else.  This results in an 18 note array (an array with 18 indices), which are all a part of another array that contains each of these arrays (a total of 7).  If you were to add an 8th scale with 18 notes, then the scales[][] array should be initialized as scales[8][18].  This would also need to be changed in the .ino sketch in the rootScaled[][] array.  

Currently, if the knob is turned all the way to the left, the Ionian (major) Scale is selected.  As the knob is turned to the right, each scale from the array is played in the order that they are presented in the scales.h file.

## Build Process

**TOP**
Bit: 1/64”
Mill Time: ~3mins

**BOTTOM**
Bit: 1/32”, 1/64”
Mill Time: ~11mins

It’s easiest to solder in this order:
```
1. Vias
2. Resistor
3. Headers
4. Audio jack
5. Tactile button
6. Pots
```

Test

First follow [this guide](https://learn.adafruit.com/adafruit-feather-m4-express-atsamd51) for getting acquainted with the board and setting up your arduino IDE to use it. For the SAMD Board Support (Adafruit version), version 1.5.14 is verified to work.  Version 1.6+ has introduced a problem that will break the code without generating any errors.

Additionally, you will need to install the Adafruit fork of the PJRC Audio Library via the IDE.  

![](https://i.imgur.com/D8f4R7t.png)


And also the following libraries:

```
Adafruit_SPIFlash
Adafruit_Zero_I2S_Library
SDFat-Adafruit Fork
```

Once all of the dependencies have been installed, and you’ve uploaded a trial sketch, upload the code that you’ve downloaded from the repository and have fun!  

![A close up photo of a hand plugging in an audio cable into the 3.5mm audio jack on the Feather Synth](https://github.com/jps723/featherSynth/blob/master/images/closeup.png)
