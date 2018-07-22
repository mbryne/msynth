#ifndef mModeMixer_h
#define mModeMixer_h

#include <Arduino.h>
#include "../mode.h"

class mModeMixer: public mMode {
  public:
    mModeMixer( void );
    ~mModeMixer();
    void setup();
    void update();
};

#endif
