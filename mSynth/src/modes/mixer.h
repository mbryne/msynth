#include "mode.h"

class mModeMixer: public mMode {
  public:
    mModeMixer( void );
    ~mModeMixer();
    void setup();
    void loop();
};
