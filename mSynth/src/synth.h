#ifndef mSynth_h
#define mSynth_h

#include "mode.h"
#include "Arduino.h"

  class mSynth {
    public:
      mSynth();
      ~mSynth();
      int _maxModes = 1;
      mMode** modes = new mMode*[1];
      void setup();
      void update();
  };

#endif
