#ifndef mModes_h
#define mModes_h

#include "Arduino.h"

#define TOTAL_CONTROLS 7
#define TOTAL_MODES 2

enum struct Parameters {
    MASTER_VOLUME,
    NONE
};

struct ModeControl {
  Parameters parameter;
  char label[16];
	int min = 0;
  int max = 127;
};

struct Mode
{
  char label[16];
  struct ModeControl controls[TOTAL_CONTROLS]; // 1 encoder, 6 pots
};

#endif
