#include "synth.h"

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// audio memory
#define AMEMORY 50

// gain at oscillator/filter input stage (1:1)
// keep low so filter does not saturate with resonance
#define GAIN_OSC 0.5

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=156.44441986083984,411.0000066757202
AudioSynthWaveform       waveform2; //xy=161.77778244018555,512.2222270965576
AudioSynthWaveform       lfo1;      //xy=165.44441986083984,451.0000066757202
AudioSynthWaveform       lfo2; //xy=170.77778244018555,551.2222270965576
AudioFilterStateVariable filter1;        //xy=295.99997901916504,443.88889598846436
AudioFilterStateVariable filter2; //xy=306.22224044799805,544.0000038146973
AudioMixer4              mixer1;         //xy=437.6666259765625,430.3333435058594
AudioMixer4              mixer2; //xy=442.2222366333008,530.5555782318115
AudioEffectEnvelope      envelope2; //xy=593.77783203125,548.4444580078125
AudioEffectEnvelope      envelope1;      //xy=596.5556030273438,456.4444274902344
AudioMixer4              envMixer1; //xy=752.3333740234375,428.5555114746094
AudioMixer4              envMixer2; //xy=755,529
AudioMixer4              mainMixer;         //xy=1030.750015258789,701.2500076293945
AudioOutputI2S           i2s1;           //xy=1241.9720649719238,703.3611211776733
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform1, 0, mainMixer, 0);
AudioConnection          patchCord3(waveform2, 0, filter2, 0);
AudioConnection          patchCord4(waveform2, 0, mainMixer, 1);
AudioConnection          patchCord5(lfo1, 0, filter1, 1);
AudioConnection          patchCord6(lfo2, 0, filter2, 1);
AudioConnection          patchCord7(filter1, 0, mixer1, 1);
AudioConnection          patchCord8(filter1, 1, mixer1, 2);
AudioConnection          patchCord9(filter1, 2, mixer1, 3);
AudioConnection          patchCord10(filter2, 0, mixer2, 1);
AudioConnection          patchCord11(filter2, 1, mixer2, 2);
AudioConnection          patchCord12(filter2, 2, mixer2, 3);
AudioConnection          patchCord13(mixer1, envelope1);
AudioConnection          patchCord14(mixer1, 0, envMixer1, 0);
AudioConnection          patchCord15(mixer2, envelope2);
AudioConnection          patchCord16(mixer2, 0, envMixer2, 0);
AudioConnection          patchCord17(envelope2, 0, envMixer2, 1);
AudioConnection          patchCord18(envelope1, 0, envMixer1, 1);
AudioConnection          patchCord19(mainMixer, 0, i2s1, 0);
AudioConnection          patchCord20(mainMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1235.666660308838,1035.3332824707031
// GUItool: end automatically generated code

uint8_t waveforms[6] = {
  WAVEFORM_SINE,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_PULSE
};

enum FilterMode_t {
  LOWPASS,
  BANDPASS,
  HIGHPASS,
  FILTEROFF,
  FILTERMODE_N,
};

Synth::Synth() {

}

void Synth::setup() {

  Serial.println("Setup mSynth");

  AudioMemory(50);
  // usbMIDI.setHandleControlChange(myControlChange);

  //  setup our oscillators
  oscillator1 = { &waveform1, &lfo1, &filter1, &mixer1, &envelope1 };
  oscillator2 = { &waveform2, &lfo2, &filter2, &mixer2, &envelope2 };

  //  enable our sound chip
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  //  set our default values
  resetAll();

}

int Synth::getValue(Parameter parameter) {

  switch (parameter) {
    case Parameter::MASTER_VOLUME:
      return masterVolume*127.;
      break;
    case Parameter::OSC_1_WAVEFORM:
      return oscillator1.type;
      break;
    case Parameter::OSC_2_WAVEFORM:
      return oscillator2.type;
      break;
    case Parameter::NONE:
      return -1;
      break;
  }

  return -1;

}


String Synth::setValue(Parameter parameter, uint8_t value) {

  int roundedValue;
  switch (parameter) {
    case Parameter::MASTER_VOLUME:
      masterVolume = value/127.;
      break;
    case Parameter::OSC_1_WAVEFORM:
      roundedValue = map(value, 0, 127, 0, 5 );
      oscillator1.type = value;
      oscillator1.waveform->begin(waveforms[roundedValue]);
      return typeName(roundedValue);
      break;
    case Parameter::OSC_2_WAVEFORM:
      roundedValue = map(value, 0, 127, 0, 5 );
      oscillator2.type = value;
      oscillator2.waveform->begin(waveforms[roundedValue]);
      return typeName(roundedValue);
      break;
    case Parameter::NONE:
      break;
  }
  return "";

}

String Synth::typeName(uint8_t type) {
  switch( type ) {
    case 0: return "Sine";
    case 1: return "Square";
    case 2: return "Triangle";
    case 3: return "Sawtooth";
    case 4: return "Sawtooth Rev";
    case 5: return "Pulse";
  }
  return "";
}

void Synth::update(void) {

  // Serial.print("Update mSynth");
  // Serial.println(millis());

  // delay(1000);

}

//////////////////////////////////
//  NOTE FUNCTIONS
//////////////////////////////////

float Synth::noteToFrequency(float note) {
  return SYNTH_TUNING*pow(2,(note - 69)/12.+pitchBend);
}

void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {

    // float v = velocityOn ? velocity/127. : 1;
    // if (osc.note!=note) {
    //   osc.wf->frequency(noteToFreq(note));
    //   notesAdd(notesOn,note);
    //   if (envOn && !osc.velocity) osc.env->noteOn();
    //   osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    //   osc.velocity = velocity;
    //   osc.note = note;
    // } else if (velocity > osc.velocity) {
    //   osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    //   osc.velocity = velocity;
    // }

}

inline void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  // if (envOn) osc.env->noteOff();
  // else       osc.wf->amplitude(0);
  // notesDel(notesOn,osc.note);
  // osc.note = -1;
  // osc.velocity = 0;
}

inline void allOff() {
  // Oscillator *o=oscs,*end=oscs+NVOICES;
  // do {
  //   oscOff(*o);
  //   o->wf->amplitude(0);
  //   o->env->noteOff();
  // } while(++o < end);
  // notesReset(notesOn);
}

//////////////////////////////////
//  STATE FUNCTIONS
//////////////////////////////////

void Synth::resetAll() {

  //  master values
  masterVolume = 0.9;
  velocityOn = true;
  pitchBend = 0;

  // //  oscillator1
  oscillator1.waveform->begin(WAVEFORM_SAWTOOTH);
  oscillator1.waveform->amplitude(0.75);
  oscillator1.waveform->frequency(82.41);
  oscillator1.waveform->pulseWidth(0.15);

  //  oscillator2
  oscillator1.waveform->begin(WAVEFORM_SAWTOOTH);
  oscillator1.waveform->amplitude(0.75);
  oscillator1.waveform->frequency(123);
  oscillator1.waveform->pulseWidth(0.15);

  // mainMixer.gain(0, 0.5);
  // mainMixer.gain(1, 0.5);

}

//////////////////////////////////
//  DEBUG FUNCTIONS
//////////////////////////////////

void Synth::dump() {
  Serial.println();
  Serial.println("===================================");
  Serial.println("= DUMP");
  Serial.println("===================================");
  Serial.println();
  Serial.print("Master Volume:        ");
  Serial.println(masterVolume);
  Serial.println(getValue(Parameter::MASTER_VOLUME));
  Serial.println("===================================");
  Serial.println();
}
