
#ifndef MSTRUTS_H
#define MSTRUTS_H

#include <Arduino.h>

//////////////////////////////////
//  STRUCTS
//////////////////////////////////

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

struct Mode {
  char label[16];
  struct ModeControl controls[7]; // 1 encoder, 6 pots
};

#endif
