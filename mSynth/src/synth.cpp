#include "Arduino.h"
#include "synth.h"
#include "modes/mixer.h"

mSynth::mSynth() {
  mMode * modes;
  modes[0] = mModeMixer();
}

mSynth::~mSynth()
{

}
