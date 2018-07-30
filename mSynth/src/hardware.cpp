#include "hardware.h"

Hardware::Hardware() {

}

void Hardware::setup(void) {

  Serial.println("Setup mHardware");

  //  button setup
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  //  rotary setup
  pinMode(ROTARY_BUTTON_1, INPUT_PULLUP);

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

    button1.update();
    button2.update();
    rotaryButton.update();

    for( int i = 0; i < HARDWARE_KNOBS; i++) {
      knobs[i].update();
    }

}


void Hardware::state(void) {

  if (button1.fallingEdge()) {
    Serial.println("button1: pushed");
    button1Pressed = true;
  }

  if (button2.fallingEdge()) {
    Serial.println("button2: pushed");
    button2Pressed = true;
  }

  for( int i = 0; i < HARDWARE_KNOBS; i++) {
    if (knobs[i].hasChanged()) {
      Serial.print("pot ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(knobs[i].getValue());
    }
  }

  newPosition = rotary.read();
  if (newPosition != rotaryPosition) {
    Serial.print("rotary: ");
    Serial.println(newPosition);
    rotaryPosition = newPosition;
  }

  if (rotaryButton.fallingEdge()) {
    Serial.println("rotaryButton: pushed");
    rotaryButtonPressed = true;
  }

}
