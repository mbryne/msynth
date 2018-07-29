#include "synth.h"

//
//  CONSTRUCTOR
//

Synth::Synth() {

}

//
//  SETUP
//
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
//
// void Synth::update(void) {
//
//   Serial.print("Update mSynth");
//   Serial.println(millis());
//
//   // for( int i = 0; i < _maxModes; i++ ) {
//     // modes[i]->update();
//   // }
//
//   delay(1000);
//
// }

//
//  MODE SELECTION
//
//
// struct Mode Synth::currentMode(void) {
//   return SynthModes[_mode];
// }
//
// void Synth::previousMode(void) {
//   setMode(_mode - 1);
// }
//
// void Synth::nextMode(void) {
//   setMode(_mode + 1);
// }
//
// void Synth::setMode(int mode) {
//
//   if (mode > TOTAL_MODES - 1) {
//       mode = 0;
//   }
//   if (mode < 0) {
//     mode = TOTAL_MODES - 1;
//   }
//
//   _mode = mode;
//
// }
