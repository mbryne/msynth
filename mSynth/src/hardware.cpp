#include "hardware.h"

Hardware::Hardware() {

}

void Hardware::setup(void) {

  Serial.println("Setup mHardware");

  //  button setup
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  //  rotary setup
  pinMode(ROTARY_0_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_1_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_2_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_3_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_4_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_5_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_6_BUTTON, INPUT_PULLUP);

  //  display setup
  display = new LiquidCrystal_I2C(0x27,16,2);
  display->init();
  display->backlight();

}

void Hardware::update(void) {
    poll();
    state();
}

void Hardware::poll(void) {

    for( int b = 0; b < BUTTON_COUNT; b++) {
      buttons[b].button.update();
    }

    for( int k = 0; k < ROTARY_COUNT; k++) {
      rotary[k].button.update();
    }

}

void Hardware::state(void) {

  for( int b = 0; b < BUTTON_COUNT; b++) {
    if (buttons[b].button.fallingEdge()) {
      Serial.print("button");
      Serial.print(b);
      Serial.println(": pushed");
      buttons[b].pressed = true;
    }
  }

  for( int i = 0; i < ROTARY_COUNT; i++) {

      //  rotary position
      rotary[i].newPosition = rotary[i].encoder.read();
      if (rotary[i].newPosition != rotary[i].currentPosition) {
        Serial.print("rotary ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(rotary[i].newPosition);
        rotary[i].currentPosition = rotary[i].newPosition;
        rotary[i].updated = true;
      }

      //  button position
      if (rotary[i].button.fallingEdge()) {
        Serial.print("rotaryButton ");
        Serial.print(i);
        Serial.println(": pushed ");
        rotary[i].pressed = true;
      }

  }

}
