/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/

//#include "Arduino.h"

// Solves problems if library is imported more than once.
#ifndef SlambotStepper_h
  #define SlambotStepper_h

class SlambotStepper{
  public:
    SlambotStepper(int N1, int N2, int N3, int N4,
        unsigned long iMaxStep, unsigned long iDelay, boolean iCW);
    void turn(void);
    void turn(unsigned int steps);
    unsigned int stepsPerRev;
    unsigned int currentStep;
    unsigned int delay;
    boolean CW;

  private:
    byte _N1;
    byte _N2;
    byte _N3;
    byte _N4;
    byte _pos;
};

#endif
