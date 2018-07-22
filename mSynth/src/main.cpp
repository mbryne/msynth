#include <Arduino.h>

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

mSynth synth;

//////////////////////////////////
//  INTERFACE SETUP
//////////////////////////////////

//
//  POTS SETUP
//

const int POT_1 = A14;
const int POT_2 = A15;
const int POT_3 = A16;
const int POT_4 = A17;
const int POT_5 = A18;
const int POT_6 = A19;

ResponsiveAnalogRead pot1(POT_1, true);
ResponsiveAnalogRead pot2(POT_2, true);
ResponsiveAnalogRead pot3(POT_3, true);
ResponsiveAnalogRead pot4(POT_4, true);
ResponsiveAnalogRead pot5(POT_5, true);
ResponsiveAnalogRead pot6(POT_6, true);

//
//  BUTTON SETUP
//

const int BUTTON_1 = 31;
const int BUTTON_2 = 32;

Bounce button1 = Bounce(BUTTON_1, 25);
Bounce button2 = Bounce(BUTTON_2, 25);

//
//  ROTARY SETUP
//

const int ROTARY_BUTTON_1 = 24;
const int ROTARY_DATA_1 = 25;
const int ROTARY_DATA_2 = 26;

Bounce rotaryButton = Bounce(ROTARY_BUTTON_1, 25);

Encoder rotary(ROTARY_DATA_1, ROTARY_DATA_2);

long newPosition;
long rotaryPosition  = -999;

//
//  DISPLAY SETUP
//

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
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //
  //  SYNTH SETUP
  //

  synth.setup();

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
  //  INTERFACE SETUP
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
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  synth.update();

  //////////////////////////////////
  //  UPDATES
  //////////////////////////////////

  //  update our buttons bounce
  button1.update();
  button2.update();

  //  update our pots bounce
  pot1.update();
  pot2.update();
  pot3.update();
  pot4.update();
  pot5.update();
  pot6.update();

  //  update our rotary bounce
  rotaryButton.update();

  //////////////////////////////////
  //  TESTING
  //////////////////////////////////

  //  pots test
  if(pot1.hasChanged()) {
    Serial.print("pot1: ");
    Serial.println(pot1.getValue() / 4);
  }
  if(pot2.hasChanged()) {
    Serial.print("pot2: ");
    Serial.println(pot2.getValue() / 4);
  }
  if(pot3.hasChanged()) {
    Serial.print("pot3: ");
    Serial.println(pot3.getValue() / 4);
  }
  if(pot4.hasChanged()) {
    Serial.print("pot4: ");
    Serial.println(pot4.getValue() / 4);
  }
  if(pot5.hasChanged()) {
    Serial.print("pot5: ");
    Serial.println(pot5.getValue() / 4);
  }
  if(pot6.hasChanged()) {
    Serial.print("pot6: ");
    Serial.println(pot6.getValue() / 4);
  }

  //  buttons test
  if (button1.fallingEdge()) {
    Serial.println("button1: pushed");
  }
  if (button2.fallingEdge()) {
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
    Serial.println("rotaryButton: pushed");
  }

  //////////////////////////////////
  //  UPDATE AUDIO
  //////////////////////////////////

  //  pots test
  if(pot4.hasChanged()) {
      mixer1.gain(0, ((float)pot4.getValue() / 1023));
  }
  if(pot5.hasChanged()) {
      mixer1.gain(1, ((float)pot5.getValue() / 1023));
  }
  if(pot6.hasChanged()) {
      mixer1.gain(2, ((float)pot6.getValue() / 1023));
  }

}
