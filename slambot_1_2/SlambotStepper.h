/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/
#include "Arduino.h"
//#include <math.h>  # all  I needed was pi, no need to import a library for that.

// Solves problems if library is imported more than once.
#define dw digitalWrite
# define PI 3.141592653589793
#ifndef SlambotStepper_h
  #define SlambotStepper_h

class SlambotStepper{
  public:
    SlambotStepper(unsigned int maxStep, byte iN1, byte iN2, byte iN3, byte iN4);
    void step(void);
    void step(unsigned int steps);
    void step(unsigned int steps, boolean clockwise);
    void moveToRad(float target);
    void moveRadCW(float target);
    void moveRadCCW(float target);
    
    float getTheta();
    
    unsigned int stepsPerRev;
    float radsPerStep;
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

SlambotStepper::SlambotStepper(unsigned int maxStep, byte iN1, byte iN2, byte iN3, byte iN4)
{
  // The 28YBJ-48 stepper motor pins should be in a 1-3-2-4 pattern.
  // Example: connect motor N1, N2, N3, N4 to arduino pins 8, 10, 9, 11.
  N1 = iN1;
  N2 = iN2;
  N3 = iN3;
  N4 = iN4;
  stepsPerRev = maxStep;
  radsPerStep = 2*PI / stepsPerRev;
  
  minDelay = 1200;  // defaults to 1000 microsecond delay
  CW = true;        // defaults to clockwise rotation
  
  // These pins drive the motor, so we must assign them as outputs
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
}

void SlambotStepper::step(void){
  // Advance the motor position by one step.
  step(1);
}

void SlambotStepper::step(unsigned int steps){
  // Overloaded function uses saved rotation direction
  step(steps, CW);
}

void SlambotStepper::step(unsigned int steps, boolean clockwise){
  // Advance the motor position by ( < 65535) steps.
  while(steps--){
    switch(pos){
      case 0:
        dw(N4, HIGH);
        dw(N3, LOW);
        dw(N2, LOW);
        dw(N1, LOW);
        break;
      case 1:
        dw(N4, HIGH);
        dw(N3, HIGH);
        dw(N2, LOW);
        dw(N1, LOW);
        break;
      case 2:
        dw(N4, LOW);
        dw(N3, HIGH);
        dw(N2, LOW);
        dw(N1, LOW);
        break;
      case 3:
        dw(N4, LOW);
        dw(N3, HIGH);
        dw(N2, HIGH);
        dw(N1, LOW);
        break;
      case 4:
        dw(N4, LOW);
        dw(N3, LOW);
        dw(N2, HIGH);
        dw(N1, LOW);
        break;
      case 5:
        dw(N4, LOW);
        dw(N3, LOW);
        dw(N2, HIGH);
        dw(N1, HIGH);
        break;
      case 6:
        dw(N4, LOW);
        dw(N3, LOW);
        dw(N2, LOW);
        dw(N1, HIGH);
        break;
      case 7:
        dw(N4, HIGH);
        dw(N3, LOW);
        dw(N2, LOW);
        dw(N1, HIGH);
        break;
    } // end switch
    pos += clockwise ? 1 : -1; // Change motor position based on rotation direction
    if (pos > 7) pos %= 8;  // There are only 8 possible motor positions
    currentStep++;
    delayMicroseconds(minDelay); // Don't run too fast or motor will stutter
  } // end while loop
  // Can go as low as 600, but begins becoming unreliable below 1200.
  //  if(minDelay > 1000) minDelay -= 50;
}

void SlambotStepper::moveToRad(float target){
  // Moves to <target> radians by rotating the shortest distance.
  
}

void SlambotStepper::moveRadCW(float target){
  /* Moves <target> radians in a clockwise direction.
  Calculate number of steps needed using: target / radsPerStep
  This may round, but we can't be any more accurate due to physical gearing.
  */
  step(int(target / radsPerStep), true);
}

void SlambotStepper::moveRadCCW(float target){
  /* Moves <target> radians in a counter-clockwise direction.
  Calculate number of steps needed using: target / radsPerStep
  This may round, but we can't be any more accurate due to physical gearing.
  */
  step(int(target / radsPerStep), false);
}

float SlambotStepper::getTheta(){
  // Returns the current angle as a float, in radians
  currentStep %= stepsPerRev;        // No point in theta going over 2*PI rads
  return (currentStep * radsPerStep);
}

#endif
