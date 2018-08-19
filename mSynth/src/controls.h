#ifndef MPARAMETERS_H
#define MPARAMETERS_H

#include "Arduino.h"
#include <unordered_map>
#include <vector>

enum struct Parameter {

  //  MIXER
  MASTER_VOLUME,

  //  OSC 1
  OSC_1_WAVEFORM,
  OSC_1_FREQUENCY,
  OSC_1_PULSEWIDTH,

  //  OSC 1

  OSC_2_WAVEFORM,
  OSC_2_FREQUENCY,
  OSC_2_PULSEWIDTH,

  //  OTHER

  NONE
};

class SynthControl {
  public:
    SynthControl( String inputLabel )
      : label (inputLabel)
    {
    };
    SynthControl( String inputLabel, int inputMin, int inputMax )
      : label (inputLabel), min (inputMin), max (inputMax)
    {
    };
    SynthControl( String inputLabel, int inputMin, int inputMax, String newOptions[] )
      : label (inputLabel), min (inputMin), max (inputMax)
    {
      setOptions(newOptions);
    };
    // Control( String label, int min = 0, int max = 127, String options[] ) {
    //     label = label;
    //     min = min;
    //     max = max;
    //     options = options;
    // };
    // Parameter parameter;
    String label;
    int min = 0;
    int max = 127;
    float divider = 1;
    bool isDirty;
    int currentValue;
    int newValue;
    void setOptions( String newOptions[] ) {
      divider = 4;
      hasOptions = true;
      int numberofelements = sizeof(newOptions)/sizeof(newOptions[0]);
      options.assign(newOptions, newOptions +  numberofelements);
    }
  private:
    bool hasOptions = false;
    std::vector <String> options;
};

#endif
