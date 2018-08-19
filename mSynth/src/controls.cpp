#include "controls.h"

Controls::Controls() {

  String OscWaveforms[4] = {
    "Sine",
    "Square",
    "Triangle",
    "Sawtooth"
  };

  //  MIXER
  controls.insert({ Parameter::MASTER_VOLUME, { "Master Volume", 0, 127 } });


  SynthControl control = SynthControl("Master Volume", 0, 127);
  control.setOptions(OscWaveforms);

}
