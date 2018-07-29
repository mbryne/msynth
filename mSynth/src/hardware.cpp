#include "hardware.h"

Hardware::Hardware() {

    //  button setup
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);

    //  rotary setup
    pinMode(ROTARY_BUTTON_1, INPUT_PULLUP);

}

void Hardware::setup(void) {

  Serial.println("Setup mHardware");

}

void Hardware::update(void) {

  for( int i = 0; i < HARDWARE_KNOBS; i++) {
    knobs[i].update();
  }
  
  for( int i = 0; i < HARDWARE_BUTTONS; i++) {
    buttons[i].update();
  }

}
