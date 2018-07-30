#include <Arduino.h>

#include "hardware.h"
#include "synth.h"
#include "hardware.h"
#include "parameters.h"

Synth * synth = Synth::getInstance();
Hardware * hardware = Hardware::getInstance();

//////////////////////////////////
//  INTERFACE VARIABLES
//////////////////////////////////

//  interface bool
bool debug = true;

//  mode setup
const int totalModes = 3;
int currentMode = 0;

//  buttons setup
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool rotaryButtonPressed = false;

//  rotary
long newPosition;
long rotaryPosition  = -999;

//////////////////////////////////
//  MODE DEFINITION
//////////////////////////////////

struct ModeControl {
  Parameters parameter;
  char label[16];
	int min = 0;
  int max = 127;
};

struct Mode {
  char label[16];
  struct ModeControl controls[7]; // 1 encoder, 6 pots
};

//  our control modes
struct Mode InterfaceModes[totalModes] = {

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


//////////////////////////////////
//  MODE SELEKTOR
//////////////////////////////////

struct Mode mode(void) {
  return InterfaceModes[currentMode];
}

void setMode(int mode) {
  if (mode > totalModes - 1) {
      mode = 0;
  }
  if (mode < 0) {
    mode = totalModes - 1;
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
//  INTERFACE UPDATES
//////////////////////////////////

void updateInterface() {

    if (hardware->button1Pressed) {
      previousMode();
      hardware->button1Pressed = false;
    }

    if (hardware->button2Pressed) {
      nextMode();
      hardware->button2Pressed = false;
    }

}

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  Serial.begin(9600);

  hardware->setup();
  synth->setup();

}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  hardware->update();
  synth->update();

  updateInterface();

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
