#include "synth.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=405.00000762939453,377.5000057220459
AudioSynthWaveform       waveform1;      //xy=409.00000762939453,318.0000057220459
AudioSynthNoisePink      pink1;          //xy=417.50000762939453,428.7500066757202
AudioMixer4              mixer1;         //xy=600.0000114440918,378.75000381469727
AudioOutputI2S           i2s1;           //xy=747,377
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=588,480
// GUItool: end automatically generated code

Synth::Synth() {

}

void Synth::setup() {

  Serial.println("Setup mSynth");

  AudioMemory(50);
  // usbMIDI.setHandleControlChange(myControlChange);

  //  enable our sound chip
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  //  waveform 1
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  //  waveform 2
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(0.75);
  waveform2.frequency(123);
  waveform2.pulseWidth(0.15);

  //  pink noise
  pink1.amplitude(1.0);

  //  mixer
  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);

}

void Synth::update(void) {

  Serial.print("Update mSynth");
  Serial.println(millis());

  delay(1000);

}
