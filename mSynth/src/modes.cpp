#include "modes.h"

//  our control modes
struct Mode InterfaceModes[9] = {
    {
      "MIXER",
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
      "OSCILLATOR 1",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "OSCILLATOR 2",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "SAMPLE",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "NOISE",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "EFFECT 1",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "EFFECT 2",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "PRESETS",
      {
        { Parameters::NONE, "Type" },
        { Parameters::NONE, "Shape" },
        { Parameters::NONE, "Filter" },
        { Parameters::NONE, "Attack" },
        { Parameters::NONE, "Decay" },
        { Parameters::NONE, "Sustain" },
        { Parameters::NONE, "Release" }
      }
    },
    {
      "SETTINGS",
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
