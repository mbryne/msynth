#include "modes.h"

struct Mode modes[2] = {

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
      }

};
