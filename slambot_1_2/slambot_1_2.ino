/*
First draft of the software controlling the LBCC SlamBot.
See https://github.com/lo9key/LBCC-Slambot for commit history, bug notes, etc.
*/
//#include <Stepper.h>
//#include <AccelStepper.h>
#include "SlambotStepper.h"

typedef struct mapPoint{
  /*
  Holds x,y positions of obstacles, and potentially other data.
  More thought needs to go into mapping wifi signals:
    One option is to store the wifi node's mac address here.
    Another, probably better, option is to make a seperate map just for wifi.
  */
  unsigned int x;
  unsigned int y;
  byte confidence;  // Number of times (0-255) this obstacle has been 'seen'
};

// Prepare a blank array to hold (temporary) local map values
mapPoint localMap[1000];    // 1,000 readings should create a fairly large map.
unsigned int mapIndex = 0;  // 0-65,535 and after that we need to change data types.

// Prepare LIDAR turret
// The 28YBJ-48 stepper motor pins must be in a 1-3-2-4 pattern, so use pins 8, 10, 9, 11.
// 64 gear teeth * 32 steps in full step mode = 2048 positions
SlambotStepper turret(2048, 8, 10, 9, 11);
//Stepper turret(stepsPerRev, 8, 10, 9, 11);
//AccelStepper turret(stepsPerRev, 8, 10, 9, 11);  // A halfstep stepper on pins 8-11 inc

unsigned long rev_start_time;

// Prepare LIDAR sensor
unsigned long lidar_distance;

void setup() {
  Serial.begin(9600);        // Initialize serial port
  
//  turret.setMaxSpeed(10);    // Max speed
//  turret.setSpeed(5);        // Current speed
//  turret.moveTo(20000);    // Sets goal

  pinMode(2, OUTPUT);        // Set pin 2 as trigger pin
  pinMode(3, INPUT);         // Set pin 3 as monitor pin
  digitalWrite(3, LOW);      // Set trigger LOW
  
  Serial.println("\nSetup complete.");
}

void loop() {
  rev_start_time = millis();
  turret.step(2048);
  Serial.print("\nOne rev completed in ");
  Serial.print( (millis() - rev_start_time)/1000.0);
  Serial.print(" seconds.");
}

