#ifndef MSYNTH_H
#define MSYNTH_H

#include "Arduino.h"

//  audio libraries
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class Synth {
  public:
  	// static method to get the instance
  	static Synth* getInstance() {
  		static Synth synth;
  		return &synth;
  	};
    void setup();
    void update();
  private:
  	Synth();
  	Synth(Synth const&); // copy disabled
  	void operator=(Synth const&); // assigment disabled
};

#endif
