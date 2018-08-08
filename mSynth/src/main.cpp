
#include <Arduino.h>

#include "hardware.h"
#include "synth.h"
#include "parameters.h"
#include "modes.h"

Synth * synth = Synth::getInstance();
Hardware * hardware = Hardware::getInstance();

//////////////////////////////////
//  INTERFACE VARIABLES
//////////////////////////////////

//  interface bool
bool debug = true;

//  mode setup
const int totalModes = 10;
int currentMode = 0;

//  controls
elapsedMillis controlTimer;
int updatedControl = -1;
int currentControl = -1;
int controlUpdateable = 0; // -1 = under, 0 = ok, 1 = over
int lastControlValue = -1;

//////////////////////////////////
//  DISPLAY DEFINITION
//////////////////////////////////

//  available display modes
enum DisplayMode {
  IDLE,           //  no display update
  CHANGE_MODE,    //  writes out the new mode name and puts a character on bottom
  UPDATE_CONTROL  //  updates the control and returns to default after 1 seconds
};

//  display setup
elapsedMillis displayTimer;
bool refreshDisplay = true;
int currentDisplay = DisplayMode::IDLE;

//  filled character
#define FILLED_CHAR  0xFF

//////////////////////////////////
//  MODE CONTROL
//////////////////////////////////

extern struct Mode InterfaceModes[totalModes];

struct Mode mode(void) {
  return InterfaceModes[currentMode];
}

void setMode(int newMode) {
  if (newMode > totalModes - 1) {
      newMode = 0;
  }
  if (newMode < 0) {
    newMode = totalModes - 1;
  }
  currentMode = newMode;
}

void previousMode(void) {
  setMode(currentMode - 1);
}

void nextMode(void) {
  setMode(currentMode + 1);
}

//////////////////////////////////
//  SYNTH CONTROL
//////////////////////////////////

struct ModeControl getControl(int control) {
  return mode().controls[currentControl];
}

void setValue( int index, int value ) {
    ModeControl control = getControl(index);
    synth->setValue( (Parameter) control.parameter, value );
}

int getValue( int index ) {
    ModeControl control = getControl(index);
    return synth->getValue( (Parameter) control.parameter);
}

//////////////////////////////////
//  DISPLAY CONTROL
//////////////////////////////////

void setDisplayMode(int newMode) {
  if (debug) {
    Serial.print("Changing Mode: ");
    Serial.println(newMode);
  }
  currentDisplay = newMode;
  refreshDisplay = true;
  displayTimer = 0;
}

void displayCurrentMode() {

  hardware->display->clear();

  hardware->display->setCursor(0, 0);
  hardware->display->print(mode().label);

  for( int i = 0; i < totalModes; i++) {
      hardware->display->setCursor(i, 1);
      if (currentMode == i) {
        hardware->display->write(FILLED_CHAR);
      } else {
        hardware->display->write('-');
      }
  }

}

void displayControlUpdate() {

    ModeControl control = getControl(currentControl);

    Serial.print((int)control.parameter);
    Serial.print(": ");
    Serial.println(control.label);

    //  don't register no parameter updates
    if (control.parameter == Parameter::NONE) {
        return;
    }

    hardware->display->clear();

    hardware->display->setCursor(0, 0);
    hardware->display->print(control.label);

    Serial.println(control.label);


}

//////////////////////////////////
//  INTERFACE UPDATES
//////////////////////////////////

void startControlTimer() {

}

void updateInterface() {

    if (hardware->buttons[0].pressed) {
      previousMode();
      setDisplayMode( DisplayMode::CHANGE_MODE );
      hardware->buttons[0].pressed = false;
    }

    if (hardware->buttons[1].pressed) {
      nextMode();
      setDisplayMode( DisplayMode::CHANGE_MODE );
      hardware->buttons[1].pressed = false;
    }

    for( int k = 0; k < ROTARY_COUNT; k++) {

      if (hardware->rotary[k].updated) {
        setValue( k, hardware->rotary[k].currentPosition );
        hardware->rotary[k].updated = false;
        if (currentDisplay == DisplayMode::IDLE ) {
          updatedControl = k;
          setDisplayMode( DisplayMode::UPDATE_CONTROL );
        }
      }

      if (hardware->rotary[k].pressed) {
        hardware->rotary[k].pressed = false;
        if (currentDisplay == DisplayMode::IDLE ) {
          updatedControl = k;
          setDisplayMode( DisplayMode::UPDATE_CONTROL );
        }
      }

    }

}

void updateDisplay() {

    switch (currentDisplay)
    {
      case DisplayMode::IDLE:

        //  update our display
        if (refreshDisplay) {
          displayCurrentMode();
          refreshDisplay = false;
        }

        break;
      case DisplayMode::CHANGE_MODE:
        //
        // //  update our display
        // if (refreshDisplay) {
        //   displayCurrentMode();
        //   refreshDisplay = false;
        // }

        // if (displayTimer > 1000) {
          refreshDisplay = true;
          setDisplayMode(DisplayMode::IDLE);
        // }

        break;
      case DisplayMode::UPDATE_CONTROL:

        //  only start updating control display if we have no control
        if (currentControl == -1) {
          Serial.print("Start controlTimer: ");
          Serial.println(updatedControl);
          lastControlValue = getValue(updatedControl);
          controlTimer = 0;
          currentControl = updatedControl;
          updatedControl = -1;
        }

        //  reset the timer if we are on the same control
        if (currentControl == updatedControl && controlTimer > 100) {
          Serial.print("Reset controlTimer: ");
          Serial.println(currentControl);
          lastControlValue = getValue(updatedControl);
          // refreshDisplay = true;
          controlTimer = 0;
        }

        if (refreshDisplay) {
          displayControlUpdate();
          refreshDisplay = false;
        }

        if (displayTimer > 1000) {
          currentControl = -1;
          updatedControl = -1;
          setDisplayMode(DisplayMode::IDLE);
        }

        break;
    }


}

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  Serial.begin(9600);

  hardware->setup();
  synth->setup();

}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  hardware->update();
  synth->update();

  updateInterface();
  updateDisplay();

  //////////////////////////////////
  //  AUDIO
  //////////////////////////////////

}
