/*
First draft of the software controlling the LBCC SlamBot.
See https://github.com/lo9key/LBCC-Slambot for commit history, bug notes, etc.
*/
#include "SlambotStepper.h"
#include "SlambotMap.h"

// Prepare LIDAR turret
// The 28YBJ-48 stepper motor pins must be in a 1-3-2-4 pattern, so use pins 8, 10, 9, 11.
// 64 gear teeth * 32 steps in full step mode = 2048 positions
SlambotStepper turret(2048, 8, 10, 9, 11);

unsigned long rev_start_time;
// Prepare LIDAR sensor
unsigned int lidar_distance;

void setup() {
  Serial.begin(9600);        // Initialize serial port
  pinMode(2, OUTPUT);        // Set pin 2 as trigger pin
  pinMode(3, INPUT);         // Set pin 3 as monitor pin
  digitalWrite(3, LOW);      // Set trigger LOW
  
  Serial.println("\nSetup complete.");
}

void loop() {
  rev_start_time = millis();
//  while(turret.step())
  turret.step(2048);
  Serial.print("\nOne rev completed in ");
  Serial.print( (millis() - rev_start_time)/1000.0);
  Serial.print(" seconds.");
}
