#ifndef MHARDWARE_H
#define MHARDWARE_H

#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Arduino.h"

#include <Bounce.h>
#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//////////////////////////////////
//  SETTINGS
//////////////////////////////////

#define BUTTON_COUNT 2
#define ROTARY_COUNT 7

//  buttons
const int BUTTON_1 = 33;
const int BUTTON_2 = 32;

//  rotaries
const int ROTARY_0_BUTTON = 2;
const int ROTARY_0_DATA_1 = 24;
const int ROTARY_0_DATA_2 = 25;
const int ROTARY_1_BUTTON = 5;
const int ROTARY_1_DATA_1 = 31;
const int ROTARY_1_DATA_2 = 30;
const int ROTARY_2_BUTTON = 4;
const int ROTARY_2_DATA_1 = 29;
const int ROTARY_2_DATA_2 = 28;
const int ROTARY_3_BUTTON = 3;
const int ROTARY_3_DATA_1 = 27;
const int ROTARY_3_DATA_2 = 26;
const int ROTARY_4_BUTTON = 8;
const int ROTARY_4_DATA_1 = 39;
const int ROTARY_4_DATA_2 = 38;
const int ROTARY_5_BUTTON = 7;
const int ROTARY_5_DATA_1 = 37;
const int ROTARY_5_DATA_2 = 36;
const int ROTARY_6_BUTTON = 6;
const int ROTARY_6_DATA_1 = 35;
const int ROTARY_6_DATA_2 = 34;

//////////////////////////////////
//  STRUCTS
//////////////////////////////////

struct RotaryControl {
  Encoder encoder;
  Bounce button;
	int newPosition = 0;
  int currentPosition = -999;
  bool pressed = false;
  bool updated = false;
};

struct ButtonControl {
  Bounce button;
  bool pressed = false;
};

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
    struct ButtonControl buttons[BUTTON_COUNT] = {
      { Bounce(BUTTON_1, 50)  },
      { Bounce(BUTTON_2, 50) }
    };
    struct RotaryControl rotary[ROTARY_COUNT] = {
      { Encoder(ROTARY_0_DATA_1, ROTARY_0_DATA_2), Bounce(ROTARY_0_BUTTON, 50) },
      { Encoder(ROTARY_1_DATA_1, ROTARY_1_DATA_2), Bounce(ROTARY_1_BUTTON, 50) },
      { Encoder(ROTARY_2_DATA_1, ROTARY_2_DATA_2), Bounce(ROTARY_2_BUTTON, 50) },
      { Encoder(ROTARY_3_DATA_1, ROTARY_3_DATA_2), Bounce(ROTARY_3_BUTTON, 50) },
      { Encoder(ROTARY_4_DATA_1, ROTARY_4_DATA_2), Bounce(ROTARY_4_BUTTON, 50) },
      { Encoder(ROTARY_5_DATA_1, ROTARY_5_DATA_2), Bounce(ROTARY_5_BUTTON, 50) },
      { Encoder(ROTARY_6_DATA_1, ROTARY_6_DATA_2), Bounce(ROTARY_6_BUTTON, 50) }
    };
    LiquidCrystal_I2C * display;
  private:
  	Hardware();
  	Hardware(Hardware const&); // copy disabled
  	void operator=(Hardware const&); // assigment disabled
    void poll();
    void state();
};


#endif
