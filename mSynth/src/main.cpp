#include <Arduino.h>

//  total number of knobs
#define SYNTH_KNOBS 6

//  total number of knobs
#define SYNTH_BUTTONS 2

//////////////////////////////////
//  LIBRARIES
//////////////////////////////////

//  msynth libraries
#include "synth.h"

//  interface libraries
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Bounce.h>
#include <ResponsiveAnalogRead.h>
#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//  audio libraries
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//////////////////////////////////
//  SYNTH SETUP
//////////////////////////////////

Synth synth = Synth();

//////////////////////////////////
//  INTERFACE SETUP
//////////////////////////////////

const int POT_1 = A14;
const int POT_2 = A15;
const int POT_3 = A16;
const int POT_4 = A17;
const int POT_5 = A18;
const int POT_6 = A19;
const int BUTTON_1 = 32;
const int BUTTON_2 = 31;
const int ROTARY_BUTTON_1 = 24;
const int ROTARY_DATA_1 = 25;
const int ROTARY_DATA_2 = 26;

//  pots setup
ResponsiveAnalogRead knobs[SYNTH_KNOBS] {
  ResponsiveAnalogRead(POT_1, true),
  ResponsiveAnalogRead(POT_2, true),
  ResponsiveAnalogRead(POT_3, true),
  ResponsiveAnalogRead(POT_4, true),
  ResponsiveAnalogRead(POT_5, true),
  ResponsiveAnalogRead(POT_6, true)
};

//  button setup
Bounce button1 = Bounce(BUTTON_1, 50);
Bounce button2 = Bounce(BUTTON_2, 50);

//  rotary setup
Bounce rotaryButton = Bounce(ROTARY_BUTTON_1, 25);
Encoder rotary(ROTARY_DATA_1, ROTARY_DATA_2);

//  display setup
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////////////
//  AUDIO SETUP
//////////////////////////////////

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=405.00000762939453,377.5000057220459
AudioSynthWaveform       waveform1;      //xy=409.00000762939453,318.0000057220459
AudioSynthNoisePink      pink1;          //xy=417.50000762939453,428.7500066757202
AudioMixer4              mixer1;         //xy=600.0000114440918,378.75000381469727
AudioOutputI2S           i2s1;           //xy=747,377
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=588,480
// GUItool: end automatically generated code

//////////////////////////////////
//  INTERFACE VARIABLES
//////////////////////////////////


//  buttons setup
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool rotaryButtonPressed = false;

//  rotary
long newPosition;
long rotaryPosition  = -999;

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //
  //  INTERFACE SETUP
  //

  //  button setup
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  //  rotary setup
  pinMode(ROTARY_BUTTON_1, INPUT_PULLUP);

  //  lcd setup
  lcd.init();

  // print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);// Set the cursor at line 1, position 3. The second parameter '0' represent line 1.
  lcd.print("Hello, world!");
  lcd.setCursor(1,1);
  lcd.print("mSynth is Live!");// Set the cursor at line 2, position 2.The second parameter '1' represent line 2.

  //
  //  AUDIO SETUP
  //

  AudioMemory(20);
  // usbMIDI.setHandleControlChange(myControlChange);

  //  enable our sound chip
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  //  waveform 1
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  //  waveform 2
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(0.75);
  waveform2.frequency(123);
  waveform2.pulseWidth(0.15);

  //  pink noise
  pink1.amplitude(1.0);

  //  mixer
  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);

}

//////////////////////////////////
//  INTERFACE UPDATES
//////////////////////////////////

void updateInterface() {

    //
    //  POLLING UPDATES
    //

    //  update our pots bounce
    for( int i = 0; i < SYNTH_KNOBS; i++) {
      knobs[i].update();
    }

    //  update our buttons bounce
    button1.update();
    button2.update();

    //  update our rotary bounce
    rotaryButton.update();

    //
    //  SOMETHINGS HAPPENED
    //

    //  pots test
    for( int i = 0; i < SYNTH_KNOBS; i++) {
      if (knobs[i].hasChanged()) {
          Serial.print("pot ");
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.println(knobs[i].getValue());
      }
    }

    //  buttons test
    if (button1.fallingEdge()) {
      leftButtonPressed = true;
      Serial.println("button1: pushed");
    }
    if (button2.fallingEdge()) {
      rightButtonPressed = true;
      Serial.println("button2: pushed");
    }

    //  rotary position test
    newPosition = rotary.read();
    if (newPosition != rotaryPosition) {
      Serial.print("rotary: ");
      Serial.println(newPosition);
      rotaryPosition = newPosition;
    }

    //  rotary buttons test
    if (rotaryButton.fallingEdge()) {
      rotaryButtonPressed = true;
      Serial.println("rotaryButton: pushed");
    }



}

void updateSynth() {

    if (leftButtonPressed) {
      synth.previousMode();
      leftButtonPressed = false;
      Serial.print("Previous Mode: ");
      Serial.println(synth.currentMode().label);
    }

    if (rightButtonPressed) {
      synth.nextMode();
      rightButtonPressed = false;
      Serial.print("Next Mode: ");
      Serial.println(synth.currentMode().label);
    }

}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {
  updateInterface();
  updateSynth();

  //////////////////////////////////
  //  TESTING
  //////////////////////////////////

  //////////////////////////////////
  //  UPDATE AUDIO
  //////////////////////////////////

  //  pots test
  // if(pot4.hasChanged()) {
  //     mixer1.gain(0, ((float)pot4.getValue() / 1023));
  // }
  // if(pot5.hasChanged()) {
  //     mixer1.gain(1, ((float)pot5.getValue() / 1023));
  // }
  // if(pot6.hasChanged()) {
  //     mixer1.gain(2, ((float)pot6.getValue() / 1023));
  // }

}
