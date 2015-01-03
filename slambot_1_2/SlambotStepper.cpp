/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/

#include "Arduino.h"
#include "SlambotStepper.h""
#define dw digitalWrite

unsigned int currentStep = 0;

byte _N1;
byte _N2;
byte _N3;
byte _N4;
byte _pos = 0;

SlambotStepper::SlambotStepper(int iN1, int iN2, int iN3, int iN4,
        unsigned long iMaxStep, unsigned long iDelay, boolean iCW)
{
  // The 28YBJ-48 stepper motor pins should be in a 1-3-2-4 pattern.
  // Like 8, 10, 9, 11.
  _N1 = iN1;
  _N2 = iN2;
  _N3 = iN3;
  _N4 = iN4;
  stepsPerRev = iMaxStep;
  delay = iDelay;
  CW = iCW;

  // These pins drive the motor, so assign them as outputs
  pinMode(_N1, OUTPUT);
  pinMode(_N2, OUTPUT);
  pinMode(_N3, OUTPUT);
  pinMode(_N4, OUTPUT);
}

void SlambotStepper::turn(void){
  // Advance the motor position by one step.
  turn(1);
}

void SlambotStepper::turn(unsigned int steps){
  // Advance the motor position by some number of steps.
  while(steps--){
    switch(_pos){
      case 0:
        dw(_N4, HIGH);
        dw(_N3, LOW);
        dw(_N2, LOW);
        dw(_N1, LOW);
        break;
      case 1:
        dw(_N4, HIGH);
        dw(_N3, HIGH);
        dw(_N2, LOW);
        dw(_N1, LOW);
        break;
      case 2:
        dw(_N4, LOW);
        dw(_N3, HIGH);
        dw(_N2, LOW);
        dw(_N1, LOW);
        break;
      case 3:
        dw(_N4, LOW);
        dw(_N3, HIGH);
        dw(_N2, HIGH);
        dw(_N1, LOW);
        break;
      case 4:
        dw(_N4, LOW);
        dw(_N3, LOW);
        dw(_N2, HIGH);
        dw(_N1, LOW);
        break;
      case 5:
        dw(_N4, LOW);
        dw(_N3, LOW);
        dw(_N2, HIGH);
        dw(_N1, HIGH);
        break;
      case 6:
        dw(_N4, LOW);
        dw(_N3, LOW);
        dw(_N2, LOW);
        dw(_N1, HIGH);
        break;
      case 7:
        dw(_N4, HIGH);
        dw(_N3, LOW);
        dw(_N2, LOW);
        dw(_N1, HIGH);
        break;
    }
    _pos += CW ? 1 : -1; // Change motor position based on rotation direction
    if (_pos > 7) _pos %= 8;  // There are only 8 possible motor positions
    delayMicroseconds(delay); // Don't run too fast or motor will stutter
  }
}
