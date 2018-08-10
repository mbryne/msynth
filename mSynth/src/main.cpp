
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
String returnValue = "";
bool echoedReturn = false;

//////////////////////////////////
//  DISPLAY DEFINITION
//////////////////////////////////

//  available display modes
enum Screen {
  BOOT,           //  booting
  MODE,           //  changes our current mode
  CONTROL,         //  updates our value
  IDLE            //  no display update
};

//  display setup
bool refreshDisplay = true;
elapsedMillis displayTimer;
int currentScreen = Screen::BOOT;

//  filled character
#define FILLED_CHAR  0xFF

//////////////////////////////////
//  MODE CONTROL
//////////////////////////////////

extern struct Mode InterfaceModes[totalModes];

struct Mode mode(void) {
  return InterfaceModes[currentMode];
}

struct ModeControl getControl(int control) {
  return mode().controls[control];
}

void setValue( int index, uint8_t value ) {
    ModeControl control = getControl(index);
    String newValue = synth->setValue( (Parameter) control.parameter, value );
    if (newValue != "" && newValue != returnValue && index == currentControl) {
      returnValue = newValue;
      echoedReturn = false;
    }
}

uint8_t getValue( int index ) {
    ModeControl control = getControl(index);
    return synth->getValue( (Parameter) control.parameter);
}

void updateControls() {
  Serial.print("updateControls(): ");
  Serial.println(mode().label);
  for( int k = 0; k < ENCODER_COUNT; k++) {
    ModeControl control = getControl(k);
    uint8_t newValue = getValue(k);
    hardware->setEncoder(k, newValue);
    Serial.print("Set Control ");
    Serial.print(control.label);
    Serial.print(": ");
    Serial.println(newValue);
    Serial.print("min: ");
    Serial.print(control.min);
    Serial.print(", max: ");
    Serial.println(control.max);
  }
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

//////////////////////////////////
//  DISPLAY CONTROL
//////////////////////////////////

void setScreen(int newScreen, bool refresh = true) {
  if (debug) {
    Serial.print("Changing Screen: ");
    switch( newScreen ) {
      case 0: Serial.println("BOOT"); break;
      case 1: Serial.println("MODE"); break;
      case 2: Serial.println("CONTROL"); break;
      case 3: Serial.println("IDLE"); break;
    }
  }
  if (refresh) {
    refreshDisplay = true;
  }
  currentScreen = newScreen;
  displayTimer = 0;
}

void displaySplashScreen() {
  hardware->display->clear();
  hardware->display->setCursor(0, 0);
  hardware->display->print("BOOTING...");
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

    Serial.print(control.label);
    Serial.print(": ");
    Serial.println((int)control.parameter);

    hardware->display->clear();

    //  don't register no parameter updates
    if (control.parameter == Parameter::NONE) {
        return;
    }

    hardware->display->setCursor(0, 0);
    hardware->display->print(control.label);
    hardware->display->setCursor(0, 1);
    hardware->display->print("                ");
}

void displayControlValue() {
  if (!echoedReturn && returnValue != "") {
      hardware->display->setCursor(0, 1);
      hardware->display->print("                ");
      // delay(10);
      hardware->display->setCursor(0, 1);
      hardware->display->print(returnValue);
      echoedReturn = true;
  } else if (returnValue == "") {
      hardware->graph->drawValue( getValue(currentControl), 127);
  }
}

//////////////////////////////////
//  INTERFACE UPDATES
//////////////////////////////////

void startControlTimer() {

}

void updateInterface() {

  if (currentScreen == Screen::BOOT ) {
    return;
  }

  if (hardware->buttons[0].pressed) {
    setMode( currentMode - 1 );
    setScreen( Screen::MODE );
    hardware->buttons[0].pressed = false;
  }

  if (hardware->buttons[1].pressed) {
    setMode( currentMode + 1 );
    setScreen( Screen::MODE );
    hardware->buttons[1].pressed = false;
  }

  for( int k = 0; k < ENCODER_COUNT; k++) {

    if (hardware->encoders[k].updated) {
      if ( currentScreen > 1 ) {
        updatedControl = k;
        setValue( k, hardware->encoders[k].currentPosition );
        setScreen( Screen::CONTROL, (currentScreen != Screen::CONTROL ) );
      }
      hardware->encoders[k].updated = false;
    }

    if (hardware->encoders[k].pressed) {
      if (currentScreen > 1 ) {
        updatedControl = k;
        setScreen( Screen::CONTROL );
        if (k == 0) {
          synth->dump();
        }
      }
      hardware->encoders[k].pressed = false;
    }

  }

}

void updateState() {

    switch (currentScreen)
    {
      case Screen::BOOT:

        if (displayTimer > 3000) {
          setScreen(Screen::IDLE);
        }

      break;
      case Screen::MODE:

        if (displayTimer > 1000) {
          Serial.print("Changing Interface Mode: ");
          Serial.println(mode().label);
          updateControls();
          setScreen(Screen::IDLE, false);
        }

      break;
      case Screen::CONTROL:

        //  only start updating control display if we have no control
        if (currentControl == -1) {
          Serial.print("Start controlTimer: ");
          Serial.println(updatedControl);
          controlTimer = 0;
          currentControl = updatedControl;
          updatedControl = -1;
        }

        //  reset the timer if we are on the same control
        if (currentControl == updatedControl && controlTimer > 100) {
          Serial.print("Reset controlTimer: ");
          Serial.println(updatedControl);
          controlTimer = 0;
          updatedControl = -1;
          // setScreen(Screen::CONTROL, false);
        }

        //  reset the display and update if it doesn't match our last control
        if (updatedControl != -1 && currentControl != updatedControl && controlTimer > 1000) {
            Serial.print("Change controlTimer: ");
            Serial.println(updatedControl);
            controlTimer = 0;
            currentControl = updatedControl;
            updatedControl = -1;
            returnValue = "";
            setScreen(Screen::CONTROL);
        }

        if (displayTimer > 3000) {
          currentControl = -1;
          updatedControl = -1;
          returnValue = "";
          setScreen(Screen::IDLE);
        }

      break;
      case Screen::IDLE:

        //  do nothing

      break;
    }

}

void updateDisplay() {

  if (refreshDisplay) {

      switch (currentScreen)
      {
        case Screen::BOOT:
          displaySplashScreen();
        break;
        case Screen::MODE:
          displayCurrentMode();
        break;
        case Screen::CONTROL:
          displayControlUpdate();
        break;
        case Screen::IDLE:
          displayCurrentMode();
        break;
      }

      refreshDisplay = false;

  }

  if (currentScreen == Screen::CONTROL) {
    displayControlValue();
  }

}
//
// void updateInterface2() {
//
//   if (currentDisplay == DisplayMode::BOOT ) {
//     return;
//   }
//
//   if (hardware->buttons[0].pressed) {
//     refreshDisplay = true;
//     previousMode();
//     setDisplayMode( DisplayMode::CHANGE_MODE );
//     hardware->buttons[0].pressed = false;
//   }
//
//   if (hardware->buttons[1].pressed) {
//     refreshDisplay = true;
//     nextMode();
//     setDisplayMode( DisplayMode::CHANGE_MODE );
//     hardware->buttons[1].pressed = false;
//   }
//
//   for( int k = 0; k < ENCODER_COUNT; k++) {
//
//     if (hardware->encoders[k].updated) {
//       hardware->encoders[k].updated = false;
//
//       //  don't update our value when we are changing modes
//       if (currentDisplay != DisplayMode::CHANGE_MODE ) {
//         setValue( k, hardware->encoders[k].currentPosition );
//         updatedControl = k;
//         setDisplayMode( DisplayMode::UPDATE_CONTROL );
//       }
//
//     }
//
//     if (hardware->encoders[k].pressed) {
//       hardware->encoders[k].pressed = false;
//       if (currentDisplay != DisplayMode::CHANGE_MODE ) {
//         updatedControl = k;
//         setDisplayMode( DisplayMode::UPDATE_CONTROL );
//         if (k == 0) {
//           synth->dump();
//         }
//       }
//     }
//
//   }
//
// }
//
// void updateDisplay2() {
//
//     switch (currentDisplay)
//     {
//       case DisplayMode::BOOT:
//
//         //  update our display
//         if (refreshDisplay) {
//           displaySplashScreen();
//           refreshDisplay = false;
//         }
//
//         if (displayTimer > 2000) {
//           refreshDisplay = true;
//           setDisplayMode(DisplayMode::IDLE);
//         }
//
//       break;
//       case DisplayMode::IDLE:
//
//           //  update our display
//           if (refreshDisplay) {
//             displayCurrentMode();
//             refreshDisplay = false;
//           }
//
//           break;
//       case DisplayMode::CHANGE_MODE:
//
//         // //  update our display
//         if (refreshDisplay) {
//           displayCurrentMode();
//           refreshDisplay = false;
//         }
//
//         if (displayTimer > 1000) {
//           refreshDisplay = true;
//           setDisplayMode(DisplayMode::IDLE);
//         }
//
//         break;
//       case DisplayMode::UPDATE_CONTROL:
//
//         //  only start updating control display if we have no control
//         if (currentControl == -1) {
//           Serial.print("Start controlTimer: ");
//           Serial.println(updatedControl);
//           lastControlValue = getValue(updatedControl);
//           controlTimer = 0;
//           currentControl = updatedControl;
//           updatedControl = -1;
//           refreshDisplay = true;
//         }
//
//         //  reset the timer if we are on the same control
//         if (currentControl == updatedControl && controlTimer > 100) {
//           Serial.print("Reset controlTimer: ");
//           Serial.println(currentControl);
//           lastControlValue = getValue(updatedControl);
//           refreshDisplay = true;
//           controlTimer = 0;
//           updatedControl = -1;
//         }
//
//         if (refreshDisplay) {
//           displayControlUpdate();
//           refreshDisplay = false;
//         }
//
//         if (displayTimer > 1000) {
//           currentControl = -1;
//           updatedControl = -1;
//           refreshDisplay = true;
//           setDisplayMode(DisplayMode::IDLE);
//         }
//
//         break;
//     }
//
// }

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  Serial.begin(9600);

  hardware->setup();
  // interface->setup();
  // midi->setup();
  synth->setup();


  // usbMIDI.setHandleNoteOff(OnNoteOff);
  // usbMIDI.setHandleNoteOn(OnNoteOn);
//   usbMIDI.setHandleVelocityChange(OnAfterTouchPoly);
//   usbMIDI.setHandleControlChange(OnControlChange);
// //  usbMIDI.setHandlePitchChange(OnPitchChangeUSB);
//   usbMIDI.setHandleProgramChange(OnProgramChange);
//   usbMIDI.setHandleAfterTouch(OnAfterTouch);
//   usbMIDI.setHandleSysEx(OnSysEx);
//   //usbMIDI.setHandleRealTimeSystem(OnRealTimeSystem);
//   usbMIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);
}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  hardware->update();
  // interface->update();
  // midi->update();
  synth->update();

  updateInterface();
  updateState();
  updateDisplay();

  //////////////////////////////////
  //  AUDIO
  //////////////////////////////////

}
