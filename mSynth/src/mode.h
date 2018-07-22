#ifndef mMode_h
#define mMode_h

  class mMode {
    public:
      mMode( void );
      ~mMode();
      virtual void setup() = 0;
      virtual void loop() = 0;
  };

#endif
