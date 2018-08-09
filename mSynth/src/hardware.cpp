#include "hardware.h"

Hardware::Hardware() {

}

void Hardware::setup(void) {

  Serial.println("Setup mHardware");

  //  button setup
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  //  ENCODER setup
  pinMode(ENCODER_0_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_1_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_2_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_3_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_4_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_5_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_6_BUTTON, INPUT_PULLUP);

  //  display setup
  display = new LiquidCrystal_I2C(0x27,16,2);
  display->init();
  display->backlight();

  //  graph setup
  graph = new LcdBarGraphX(display, 16, 0, 1);
  graph->begin();

}

void Hardware::update(void) {
    poll();
    state();
}

void Hardware::poll(void) {

    for( int b = 0; b < BUTTON_COUNT; b++) {
      buttons[b].button.update();
    }

    for( int k = 0; k < ENCODER_COUNT; k++) {
      encoders[k].button.update();
    }

}

void Hardware::setEncoder(int i, int value) {
  encoders[i].newPosition = value;
  encoders[i].currentPosition = value;
  encoders[i].encoder.write(value);
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

  for( int i = 0; i < ENCODER_COUNT; i++) {

      //  ENCODER position
      encoders[i].newPosition = encoders[i].encoder.read();
      if (encoders[i].newPosition != encoders[i].currentPosition) {

        //  constrain value
        if (encoders[i].newPosition > 127 ) {
          encoders[i].encoder.write(127);
          encoders[i].newPosition = 127;
        }
        if (encoders[i].newPosition < 0 ) {
          encoders[i].encoder.write(0);
          encoders[i].newPosition = 0;
        }

        Serial.print("encoder ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(encoders[i].newPosition);
        encoders[i].currentPosition = encoders[i].newPosition;
        encoders[i].updated = true;
      }

      //  button position
      if (encoders[i].button.fallingEdge()) {
        Serial.print("encoderButton ");
        Serial.print(i);
        Serial.println(": pushed ");
        encoders[i].pressed = true;
      }

  }

}
