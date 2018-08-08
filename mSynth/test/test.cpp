#include <Arduino.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

#include <Bounce.h>
#include <ResponsiveAnalogRead.h>
#include <Encoder.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//////////////////////////////////
//  INTERFACE SETUP
//////////////////////////////////

//
//  BUTTON SETUP
//

const int BUTTON_1 = 33;
const int BUTTON_2 = 32;

Bounce button1 = Bounce(BUTTON_1, 50);
Bounce button2 = Bounce(BUTTON_2, 50);

//
//  ROTARY SETUP
//

const int ROTARY_COUNT = 7;
const int ROTARY_0_BUTTON = 2;
const int ROTARY_0_DATA_1 = 24;
const int ROTARY_0_DATA_2 = 25;
const int ROTARY_1_BUTTON = 3;
const int ROTARY_1_DATA_1 = 27;
const int ROTARY_1_DATA_2 = 26;
const int ROTARY_2_BUTTON = 4;
const int ROTARY_2_DATA_1 = 29;
const int ROTARY_2_DATA_2 = 28;
const int ROTARY_3_BUTTON = 5;
const int ROTARY_3_DATA_1 = 31;
const int ROTARY_3_DATA_2 = 30;
const int ROTARY_4_BUTTON = 6;
const int ROTARY_4_DATA_1 = 35;
const int ROTARY_4_DATA_2 = 34;
const int ROTARY_5_BUTTON = 7;
const int ROTARY_5_DATA_1 = 37;
const int ROTARY_5_DATA_2 = 36;
const int ROTARY_6_BUTTON = 8;
const int ROTARY_6_DATA_1 = 39;
const int ROTARY_6_DATA_2 = 38;

struct KnobControl {
  Encoder encoder;
  Bounce button;
	int newPosition = 0;
  int currentPosition = -999;
};

struct KnobControl Controls[ROTARY_COUNT] = {
    {
      Encoder(ROTARY_0_DATA_1, ROTARY_0_DATA_2),
      Bounce(ROTARY_0_BUTTON, 50)
    },
    {
      Encoder(ROTARY_1_DATA_1, ROTARY_1_DATA_2),
      Bounce(ROTARY_1_BUTTON, 50)
    },
    {
      Encoder(ROTARY_2_DATA_1, ROTARY_2_DATA_2),
      Bounce(ROTARY_2_BUTTON, 50)
    },
    {
      Encoder(ROTARY_3_DATA_1, ROTARY_3_DATA_2),
      Bounce(ROTARY_3_BUTTON, 50)
    },
    {
      Encoder(ROTARY_4_DATA_1, ROTARY_4_DATA_2),
      Bounce(ROTARY_4_BUTTON, 50)
    },
    {
      Encoder(ROTARY_5_DATA_1, ROTARY_5_DATA_2),
      Bounce(ROTARY_5_BUTTON, 50)
    },
    {
      Encoder(ROTARY_6_DATA_1, ROTARY_6_DATA_2),
      Bounce(ROTARY_6_BUTTON, 50)
    }
  };

//
//  DISPLAY SETUP
//

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////////////
//  SETUP FUNCTION
//////////////////////////////////

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //
  //  BUTTON SETUP
  //

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  //
  //  ROTARY SETUP
  //

  pinMode(ROTARY_0_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_1_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_2_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_3_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_4_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_5_BUTTON, INPUT_PULLUP);
  pinMode(ROTARY_6_BUTTON, INPUT_PULLUP);

  //
  //  LCD SETUP
  //

  lcd.init();                      // initialize the lcd

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);// Set the cursor at line 1, position 3. The second parameter '0' represent line 1.
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("mSynth2 is Live!");// Set the cursor at line 2, position 2.The second parameter '1' represent line 2.

}

//////////////////////////////////
//  LOOP FUNCTIONS
//////////////////////////////////

void loop() {

  //////////////////////////////////
  //  UPDATES
  //////////////////////////////////

  //  update our buttons bounce
  button1.update();
  button2.update();

  //  update our rotary buttons bounce
  for( int i = 0; i < ROTARY_COUNT; i++) {
    Controls[i].button.update();
  }

  //////////////////////////////////
  //  TESTING
  //////////////////////////////////


  //  buttons test
  if (button1.fallingEdge()) {
    Serial.println("button1: pushed");
  }
  if (button2.fallingEdge()) {
    Serial.println("button2: pushed");
  }

  //  update our rotary buttons bounce
  for( int i = 0; i < ROTARY_COUNT; i++) {

    //  rotary position
    Controls[i].newPosition = Controls[i].encoder.read();
    if (Controls[i].newPosition != Controls[i].currentPosition) {
      Serial.print("rotary ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Controls[i].newPosition);
      Controls[i].currentPosition = Controls[i].newPosition;
    }

    //  button position
    if (Controls[i].button.fallingEdge()) {
      Serial.print("rotaryButton ");
      Serial.print(i);
      Serial.println(": pushed ");
    }

  }

}
