#include <Arduino.h>

#include "hardware.h"
#include "synth.h"
#include "hardware.h"
#include "parameters.h"
#include "modes.h"

Synth * synth = Synth::getInstance();
Hardware * hardware = Hardware::getInstance();
LiquidCrystal_I2C * display;

//////////////////////////////////
//  INTERFACE VARIABLES
//////////////////////////////////

//  interface bool
bool debug = true;

//  mode setup
const int totalModes = 9;
int currentMode = 0;

//  buttons setup
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool rotaryButtonPressed = false;

//  controls
elapsedMillis controlTimer;
int currentControl = -1;
int controlUpdateable = 0; // -1 = under, 0 = ok, 1 = over
int lastControlValue = -1;

//  rotary
long newPosition;
long rotaryPosition  = -999;


//////////////////////////////////
//  DISPLAY DEFINITION
//////////////////////////////////

//  available display modes
enum DisplayMode {
  IDLE,           //  no display update
  CHANGE_MODE,    //  writes out the new mode name and puts a character on bottom
  UPDATE_CONTROL  //  updates the control and returns to default after 2 seconds
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

void updateControl( int index, int value ) {
    ModeControl control = getControl(index);
}

void getValue( int index ) {
    ModeControl control = getControl(index);
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

  display->clear();

  display->setCursor(0, 0);
  display->print(mode().label);

  for( int i = 0; i < totalModes; i++) {
      display->setCursor(i, 1);
      if (currentMode == i) {
        display->write(FILLED_CHAR);
      } else {
        display->write('-');
      }
  }

}

void displayControlUpdate() {

    ModeControl control = getControl(currentControl);

    //  don't register no parameter updates
    if (control.parameter == Parameter::NONE) {
        return;
    }

    display->clear();

    display->setCursor(0, 0);
    display->print(control.label);

    Serial.println(control.label);


}

//////////////////////////////////
//  INTERFACE UPDATES
//////////////////////////////////

void updateInterface() {

    if (hardware->button1Pressed) {
      previousMode();
      setDisplayMode( DisplayMode::CHANGE_MODE );
      hardware->button1Pressed = false;
    }

    if (hardware->button2Pressed) {
      nextMode();
      setDisplayMode( DisplayMode::CHANGE_MODE );
      hardware->button2Pressed = false;
    }

    for( int k; k < HARDWARE_KNOBS; k++) {
      if (hardware->knobUpdated[k]) {
        updateControl( k + 1, hardware->knobValues[k] ); // first control is knob
        // startControlTimer( k + 1, hardware->knobValues[k] );
        currentControl = k + 1;
        setDisplayMode( DisplayMode::UPDATE_CONTROL );
        hardware->knobUpdated[k] = false;
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

        //  update our display
        if (refreshDisplay) {
          displayCurrentMode();
          refreshDisplay = false;
        }

        if (displayTimer > 5000) {
          setDisplayMode(DisplayMode::IDLE);
        }

        break;
      case DisplayMode::UPDATE_CONTROL:

        //  only start updating control display if we have no control
        if (currentControl == -1) {
          Serial.print("Start controlTimer: ");
          Serial.println(currentControl);

          // ModeControl control = getControl(index);
          // lastControlValue = synth->getValue();
          controlTimer = 0;
          lastControlValue = lastValue;

          if (controlTimer < 10) {
            currentControl = index;
          }

        }

        //  reset the timer if we are on the same control
        if (currentControl == index) {

          Serial.print("Reset controlTimer: ");
          Serial.println(index);

          if (lastControlValue != lastValue) {
            lastControlValue = lastValue;
            refreshDisplay = true;
          }

          controlTimer = 0;

        }

        //  update our display
        if (refreshDisplay) {
          displayControlUpdate();
          refreshDisplay = false;
        }

        if (displayTimer > 5000) {
          currentControl = -1;
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

  display = hardware->display;

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
  //  TESTING
  //////////////////////////////////

  //////////////////////////////////
  //  UPDATE AUDIO
  //////////////////////////////////

  //  pots test
  // if(pot4.hasChanged()) {
  //     mixer1.gain(0, ((float)pot4.getValue() / 1023));
  // }
  // if(pot5.hasChanged()) {
  //     mixer1.gain(1, ((float)pot5.getValue() / 1023));
  // }
  // if(pot6.hasChanged()) {
  //     mixer1.gain(2, ((float)pot6.getValue() / 1023));
  // }

}
