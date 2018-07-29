#include <Arduino.h>
#include "synth.h"
#include "hardware.h"
#include "structs.h"

Synth * synth = Synth::getInstance();
Hardware * hardware = Hardware::getInstance();

//////////////////////////////////
//  INTERFACE SETUP
//////////////////////////////////

//  pots setup
ResponsiveAnalogRead knobs[HARDWARE_KNOBS] {
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

//  mode setup
int currentMode = 0;

//  buttons setup
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool rotaryButtonPressed = false;

//  rotary
long newPosition;
long rotaryPosition  = -999;

//////////////////////////////////
//  MODE SELEKTOR
//////////////////////////////////

#define TOTAL_MODES 3

//  our control modes
struct Mode InterfaceModes[TOTAL_MODES] = {

    {
      "Mixer",
      {
        { Parameters::MASTER_VOLUME, "Master Volume" },
        { Parameters::NONE, "" },
        { Parameters::NONE, "Oscillator 1" },
        { Parameters::NONE, "Sample" },
        { Parameters::NONE, "" },
        { Parameters::NONE, "Oscillator 2" },
        { Parameters::NONE, "Noise" }
      }
    },
    {
      "Oscillator 1",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "Oscillator 2",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    }

};

struct Mode mode(void) {
  return InterfaceModes[currentMode];
}

void setMode(int mode) {
  if (mode > TOTAL_MODES - 1) {
      mode = 0;
  }
  if (mode < 0) {
    mode = TOTAL_MODES - 1;
  }
  currentMode = mode;
}

void previousMode(void) {
  setMode(currentMode - 1);
}

void nextMode(void) {
  setMode(currentMode + 1);
}

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  Serial.begin(9600);

  synth->setup();
  hardware->setup();

  //
  //  INTERFACE SETUP
  //

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
    //  SOMETHINGS HAPPENED
    //

    //  pots test
    for( int i = 0; i < HARDWARE_KNOBS; i++) {
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
      // synth.previousMode();
      // leftButtonPressed = false;
      // Serial.print("Previous Mode: ");
      // Serial.println(synth.currentMode().label);
    }

    if (rightButtonPressed) {
      // synth.nextMode();
      // rightButtonPressed = false;
      // Serial.print("Next Mode: ");
      // Serial.println(synth.currentMode().label);
    }

}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  hardware->update();
  //
  // updateInterface();
  // updateSynth();

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
