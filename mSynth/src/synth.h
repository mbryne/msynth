#ifndef Synth_h
#define Synth_h

  #define TOTAL_CONTROLS 7
  #define TOTAL_MODES 3

  #include "Arduino.h"

  enum struct Parameters {
      MASTER_VOLUME,
      NONE
  };

  struct ModeControl {
    Parameters parameter;
    char label[16];
  	int min = 0;
    int max = 127;
  };

  struct Mode {
    char label[16];
    struct ModeControl controls[TOTAL_CONTROLS]; // 1 encoder, 6 pots
  };

  struct SynthControl {
    Parameters parameter;
    int currentValue;
    int updatedValue;
    char label[16];
    bool isLatched = false;
  };

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
      bool updateControl(int index, SynthControl control);
    private:
      int _mode;
  };

#endif
