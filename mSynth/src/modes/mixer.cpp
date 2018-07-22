#include "mixer.h"

mModeMixer::mModeMixer() {
}

mModeMixer::~mModeMixer()
{

}

void mModeMixer::setup() {
  Serial.println('Setup mModeMixer');
}

void mModeMixer::update() {

    Serial.print("Update mModeMixer");
    Serial.println(millis());

}
