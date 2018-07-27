#ifndef Synth_h
#define Synth_h

  #include "modes.h"
  #include "Arduino.h"

  class Synth {
    public:
      Synth();
      ~Synth();
      void setup();
      void update();
      struct Mode currentMode();
      void nextMode();
      void previousMode();
      void setMode(int mode);
    private:
      struct Mode modes[TOTAL_MODES];
      int _mode;
  };

#endif
