#ifndef MHARDWARE_H
#define MHARDWARE_H

#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Arduino.h"

#include <Bounce.h>
#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdBarGraphX.h>

//////////////////////////////////
//  SETTINGS
//////////////////////////////////

#define BUTTON_COUNT 2
#define ENCODER_COUNT 7

//  buttons
const int BUTTON_1 = 33;
const int BUTTON_2 = 32;

//  rotaries
const int ENCODER_0_BUTTON = 2;
const int ENCODER_0_DATA_1 = 24;
const int ENCODER_0_DATA_2 = 25;
const int ENCODER_1_BUTTON = 5;
const int ENCODER_1_DATA_1 = 31;
const int ENCODER_1_DATA_2 = 30;
const int ENCODER_2_BUTTON = 4;
const int ENCODER_2_DATA_1 = 29;
const int ENCODER_2_DATA_2 = 28;
const int ENCODER_3_BUTTON = 3;
const int ENCODER_3_DATA_1 = 27;
const int ENCODER_3_DATA_2 = 26;
const int ENCODER_4_BUTTON = 8;
const int ENCODER_4_DATA_1 = 39;
const int ENCODER_4_DATA_2 = 38;
const int ENCODER_5_BUTTON = 7;
const int ENCODER_5_DATA_1 = 37;
const int ENCODER_5_DATA_2 = 36;
const int ENCODER_6_BUTTON = 6;
const int ENCODER_6_DATA_1 = 35;
const int ENCODER_6_DATA_2 = 34;

//////////////////////////////////
//  STRUCTS
//////////////////////////////////

struct EncoderControl {
  Encoder encoder;
  Bounce button;
	int newPosition = 0;
  int currentPosition = 0;
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
    struct EncoderControl encoders[ENCODER_COUNT] = {
      { Encoder(ENCODER_0_DATA_1, ENCODER_0_DATA_2), Bounce(ENCODER_0_BUTTON, 50) },
      { Encoder(ENCODER_1_DATA_1, ENCODER_1_DATA_2), Bounce(ENCODER_1_BUTTON, 50) },
      { Encoder(ENCODER_2_DATA_1, ENCODER_2_DATA_2), Bounce(ENCODER_2_BUTTON, 50) },
      { Encoder(ENCODER_3_DATA_1, ENCODER_3_DATA_2), Bounce(ENCODER_3_BUTTON, 50) },
      { Encoder(ENCODER_4_DATA_1, ENCODER_4_DATA_2), Bounce(ENCODER_4_BUTTON, 50) },
      { Encoder(ENCODER_5_DATA_1, ENCODER_5_DATA_2), Bounce(ENCODER_5_BUTTON, 50) },
      { Encoder(ENCODER_6_DATA_1, ENCODER_6_DATA_2), Bounce(ENCODER_6_BUTTON, 50) }
    };
    void setEncoder( int index, int value );
    LiquidCrystal_I2C * display;
    LcdBarGraphX * graph;
  private:
  	Hardware();
  	Hardware(Hardware const&); // copy disabled
  	void operator=(Hardware const&); // assigment disabled
    void poll();
    void state();
};


#endif
