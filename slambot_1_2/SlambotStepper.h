/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/
#include "Arduino.h"
// Solves problems if library is imported more than once.
#ifndef SlambotStepper_h
  #define SlambotStepper_h

class SlambotStepper{
  public:
    SlambotStepper(unsigned int maxStep, byte iN1, byte iN2, byte iN3, byte iN4);

    void step(void);
    void step(unsigned int steps);
    
    unsigned int stepsPerRev;
    unsigned int currentStep;
    unsigned int minDelay;
    boolean CW;

  private:
    byte N1;
    byte N2;
    byte N3;
    byte N4;
    byte pos;
};

#endif
