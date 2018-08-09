#include "synth.h"

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// audio memory
#define AMEMORY 50

// gain at oscillator/filter input stage (1:1)
// keep low so filter does not saturate with resonance
#define GAIN_OSC 0.5

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=156.44441986083984,411.0000066757202
AudioSynthWaveform       waveform2; //xy=161.77778244018555,512.2222270965576
AudioSynthWaveform       lfo1;      //xy=165.44441986083984,451.0000066757202
AudioSynthWaveform       lfo2; //xy=170.77778244018555,551.2222270965576
AudioFilterStateVariable filter1;        //xy=295.99997901916504,443.88889598846436
AudioFilterStateVariable filter2; //xy=306.22224044799805,544.0000038146973
AudioMixer4              mixer1;         //xy=437.6666259765625,430.3333435058594
AudioMixer4              mixer2; //xy=442.2222366333008,530.5555782318115
AudioEffectEnvelope      envelope2; //xy=589.7778472900391,553.4444732666016
AudioEffectEnvelope      envelope1;      //xy=592.5555801391602,410.4444274902344
AudioMixer4              envMixer; //xy=740.3333511352539,480.5555076599121
AudioOutputI2S           i2s1;           //xy=1248.2220573425293,477.11112785339355
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(waveform2, 0, filter2, 0);
AudioConnection          patchCord4(waveform2, 0, mixer2, 0);
AudioConnection          patchCord5(lfo1, 0, filter1, 1);
AudioConnection          patchCord6(lfo2, 0, filter2, 1);
AudioConnection          patchCord7(filter1, 0, mixer1, 1);
AudioConnection          patchCord8(filter1, 1, mixer1, 2);
AudioConnection          patchCord9(filter1, 2, mixer1, 3);
AudioConnection          patchCord10(filter2, 0, mixer2, 1);
AudioConnection          patchCord11(filter2, 1, mixer2, 2);
AudioConnection          patchCord12(filter2, 2, mixer2, 3);
AudioConnection          patchCord13(mixer1, envelope1);
AudioConnection          patchCord14(mixer1, 0, envMixer, 0);
AudioConnection          patchCord15(mixer2, envelope2);
AudioConnection          patchCord16(mixer2, 0, envMixer, 2);
AudioConnection          patchCord17(envelope2, 0, envMixer, 3);
AudioConnection          patchCord18(envelope1, 0, envMixer, 1);
AudioConnection          patchCord19(envMixer, 0, i2s1, 0);
AudioConnection          patchCord20(envMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1235.666660308838,1035.3332824707031
// GUItool: end automatically generated code

Synth::Synth() {

}

void Synth::setup() {

  Serial.println("Setup mSynth");

  AudioMemory(50);
  // usbMIDI.setHandleControlChange(myControlChange);

  //  setup our oscillators
  Oscillator oscillator1 = { &waveform1, &lfo1, &filter1, &mixer1, &envelope1 };
  Oscillator oscillator2 = { &waveform2, &lfo2, &filter2, &mixer2, &envelope2 };

  //  enable our sound chip
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  //  set our default values
  resetAll();

  // //  waveform 1
  // waveform1.begin(WAVEFORM_SAWTOOTH);
  // waveform1.amplitude(0.75);
  // waveform1.frequency(82.41);
  // waveform1.pulseWidth(0.15);
  //
  // //  waveform 2
  // waveform2.begin(WAVEFORM_SAWTOOTH);
  // waveform2.amplitude(0.75);
  // waveform2.frequency(123);
  // waveform2.pulseWidth(0.15);
  //
  // //  mixer
  // mixer1.gain(0, 1.0);
  // mixer1.gain(1, 1.0);
  // mixer1.gain(2, 1.0);

}

int Synth::getValue(Parameter parameter) {

  switch (parameter) {
    case Parameter::MASTER_VOLUME:
      return masterVolume*127.;
      break;
    case Parameter::NONE:
      return -1;
      break;
  }

  return -1;

}


void Synth::setValue(Parameter parameter, uint8_t value) {

  switch (parameter) {
    case Parameter::MASTER_VOLUME:
      masterVolume = value/127.;
      break;
    case Parameter::NONE:
      break;
  }


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
  masterVolume = 0.9;
  velocityOn = true;
  pitchBend = 0;
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
