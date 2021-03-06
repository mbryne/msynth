#include "modes.h"

//  our control modes
struct Mode InterfaceModes[10] = {
    {
      "MIXER",
      {
        { Parameter::MASTER_VOLUME, "Master Volume" },    // 0
        { Parameter::NONE, "" },                          // 1
        { Parameter::OSC_1_WAVEFORM, "Oscillator 1" },     // 2
        { Parameter::OSC_2_WAVEFORM, "Oscillator 2" },     // 3
        { Parameter::NONE, "" },                          // 4
        { Parameter::MASTER_VOLUME, "Sample" },           // 5
        { Parameter::MASTER_VOLUME, "Noise" }             // 6
      }
    },
    {
      "SEQUENCER",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "OSCILLATOR 1",
      {
        { Parameter::OSC_1_WAVEFORM, "Type", 1, 6 },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "OSCILLATOR 2",
      {
        { Parameter::OSC_2_WAVEFORM, "Type", 1, 6 },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "SAMPLE",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "NOISE",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "EFFECT 1",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "EFFECT 2",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "PRESETS",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    },
    {
      "SETTINGS",
      {
        { Parameter::NONE, "Type" },
        { Parameter::NONE, "Shape" },
        { Parameter::NONE, "Filter" },
        { Parameter::NONE, "Attack" },
        { Parameter::NONE, "Decay" },
        { Parameter::NONE, "Sustain" },
        { Parameter::NONE, "Release" }
      }
    }

};
