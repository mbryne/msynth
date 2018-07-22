#include "Arduino.h"
#include "synth.h"
#include "modes/mixer.h"
#include <array>

mSynth::mSynth() {

  //  setup our available modes
  modes[0] = new mModeMixer();

}

mSynth::~mSynth()
{
    Serial.println("mSynth");
}

void mSynth::setup(void) {

  Serial.println("Setup mSynth");

  for( int i = 0; i < _maxModes; i++ ) {
    modes[i]->setup();
  }

}


void mSynth::update(void) {

  Serial.print("Update mSynth");
  Serial.println(millis());

  for( int i = 0; i < _maxModes; i++ ) {
    modes[i]->update();
  }

  delay(1000);

}
