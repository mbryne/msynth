#include "synth.h"

struct Mode SynthModes[TOTAL_MODES] = {

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

//
//  CONSTRUCTOR
//

Synth::Synth() {

  Serial.println("mSynth");

  //  initial synth mode
  setMode(0);

}

Synth::~Synth()
{
}

//
//  SETUP
//

void Synth::setup(void) {

  Serial.println("Setup mSynth");

  // for( int i = 0; i < _maxModes; i++ ) {
    // modes[i]->setup();
  // }

}

//
//  UPDATE
//

void Synth::update(void) {

  Serial.print("Update mSynth");
  Serial.println(millis());

  // for( int i = 0; i < _maxModes; i++ ) {
    // modes[i]->update();
  // }

  delay(1000);

}

//
//  MODE SELECTION
//

struct Mode Synth::currentMode(void) {
  return SynthModes[_mode];
}

void Synth::previousMode(void) {
  setMode(_mode - 1);
}

void Synth::nextMode(void) {
  setMode(_mode + 1);
}

void Synth::setMode(int mode) {

  if (mode > TOTAL_MODES - 1) {
      mode = 0;
  }
  if (mode < 0) {
    mode = TOTAL_MODES - 1;
  }

  _mode = mode;

}
