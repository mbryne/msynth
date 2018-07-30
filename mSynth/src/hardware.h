#ifndef MHARDWARE_H
#define MHARDWARE_H

#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Arduino.h"

#include <Bounce.h>
#include <ResponsiveAnalogRead.h>
#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//////////////////////////////////
//  SETTINGS
//////////////////////////////////

//  knobs
#define POT_1 A14
#define POT_2 A15
#define POT_3 A16
#define POT_4 A17
#define POT_5 A18
#define POT_6 A19

//  buttons
#define BUTTON_1 32
#define BUTTON_2 31

//  rotary
#define ROTARY_BUTTON_1 24
#define ROTARY_DATA_1 25
#define ROTARY_DATA_2 26

//  total number of controls
#define HARDWARE_KNOBS 6
#define HARDWARE_BUTTONS 3
#define HARDWARE_ENCODERS 1

//////////////////////////////////
//  DEFINITION
//////////////////////////////////

class Hardware {
  public:
    //  setup
  	static Hardware* getInstance() {
  		static Hardware Hardware;
  		return &Hardware;
  	};
    void setup();
    void update();
    ResponsiveAnalogRead knobs[HARDWARE_KNOBS] {
      ResponsiveAnalogRead(POT_1, true),
      ResponsiveAnalogRead(POT_2, true),
      ResponsiveAnalogRead(POT_3, true),
      ResponsiveAnalogRead(POT_4, true),
      ResponsiveAnalogRead(POT_5, true),
      ResponsiveAnalogRead(POT_6, true)
    };
    int knobValues[HARDWARE_KNOBS] { -1, -1, -1, -1, -1, -1 };
    Bounce button1 = Bounce(BUTTON_1, 50);
    Bounce button2 = Bounce(BUTTON_1, 50);
    Bounce rotaryButton = Bounce(ROTARY_BUTTON_1, 50);
    Encoder rotary = Encoder(ROTARY_DATA_1, ROTARY_DATA_2);
    LiquidCrystal_I2C * display;
    bool button1Pressed = false;
    bool button2Pressed = false;
    bool rotaryButtonPressed = false;
    long rotaryPosition  = -999;
  private:
  	Hardware();
  	Hardware(Hardware const&); // copy disabled
  	void operator=(Hardware const&); // assigment disabled
    void poll();
    void state();
    long newPosition;
};


#endif
