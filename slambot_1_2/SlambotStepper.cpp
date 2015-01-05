/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/

#include "Arduino.h"
#include "SlambotStepper.h"
#define dw digitalWrite

SlambotStepper::SlambotStepper(unsigned int maxStep, byte iN1, byte iN2, byte iN3, byte iN4)
{
  // The 28YBJ-48 stepper motor pins should be in a 1-3-2-4 pattern.
  // Example: connect motor N1, N2, N3, N4 to arduino pins 8, 10, 9, 11.
  N1 = iN1;
  N2 = iN2;
  N3 = iN3;
  N4 = iN4;
  stepsPerRev = maxStep;
  
  minDelay = 1200;  // defaults to 1000 microsecond delay
  CW = true;        // defaults to clockwise rotation
  
  // These pins drive the motor, so assign them as outputs
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
}

/*
void SlambotStepper::step(void){
  // Advance the motor position by one step.
  turn(1);
}
*/

void SlambotStepper::step(unsigned int steps){
  // Advance the motor position by ( < 65535) steps.
  Serial.println(minDelay);
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
    pos += CW ? 1 : -1; // Change motor position based on rotation direction
    if (pos > 7) pos %= 8;  // There are only 8 possible motor positions
    currentStep++;
    delayMicroseconds(minDelay); // Don't run too fast or motor will stutter
  } // end while loop
  if(minDelay > 650) minDelay -= 50;
}
