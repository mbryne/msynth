#ifndef MMODES_H
#define MMODES_H

#include "controls.h"

struct ModeControl {
  Parameter parameter;
  char label[16];
	int min = 0;
  int max = 127;
};

struct Mode {
  char label[16];
  struct ModeControl controls[7]; // 1 encoder, 6 pots
};

#endif
