#ifndef MSYNTH_H
#define MSYNTH_H

#include "Arduino.h"
#include "parameters.h"

//  audio libraries
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

struct Oscillator {
  AudioSynthWaveform*       waveform;
  AudioSynthWaveform*       lfo;
  AudioFilterStateVariable* filter;
  AudioMixer4*              mixer;
  AudioEffectEnvelope*      envelope;
  uint8_t type = WAVEFORM_SAWTOOTH;
  float amplitude = 0.75;
  float frequency = 123;
  float pulseWidth = 0.15;
  int8_t  note = -1;
  uint8_t velocity = 0;
};

class Synth {
  public:
  	// static method to get the instance
  	static Synth* getInstance() {
  		static Synth synth;
  		return &synth;
  	};
    void setup();
    void update();
    int getValue( Parameter parameter );
    String setValue( Parameter parameter, uint8_t value );
    float noteToFrequency(float note);
    void resetAll();
    void dump();
    void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
    void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
    String typeName(uint8_t type);
    //  synth variables
    Oscillator oscillator1;
    Oscillator oscillator2;
    float masterVolume;
    float pitchBend;  // -1/+1 oct
    bool  velocityOn;

  private:
  	Synth();
  	Synth(Synth const&); // copy disabled
  	void operator=(Synth const&); // assigment disabled
};

#endif
