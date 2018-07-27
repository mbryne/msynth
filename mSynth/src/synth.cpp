#include "synth.h"

//
//  CONSTRUCTOR
//

Synth::Synth() {

  Serial.println("mSynth");

  //  setup our synth modes


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
  return modes[_mode];
}

void Synth::previousMode(void) {
  setMode(_mode--);
}

void Synth::nextMode(void) {
  setMode(_mode++);
}

void Synth::setMode(int mode) {
  if (mode > TOTAL_MODES - 1) {
      mode = 0;
  }
  if (mode < 0) {
    mode = TOTAL_MODES;
  }
  _mode = mode;
}
