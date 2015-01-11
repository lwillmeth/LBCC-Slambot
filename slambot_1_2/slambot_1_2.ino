/*
First draft of the software controlling the LBCC SlamBot.
See https://github.com/lo9key/LBCC-Slambot for commit history, bug notes, etc.
*/
# define PI 3.141592653589793  // Close enough..?
#include "SlambotStepper.h"
#include "SlambotMap.h"

// Prepare LIDAR turret
// The 28YBJ-48 stepper motor pins must be in a 1-3-2-4 pattern, so use pins 8, 10, 9, 11.
// This stepper has 32 steps and a 1:64 gear ratio, so a total of 2048 positions.
SlambotStepper turret(4096, 8, 10, 9, 11);

// Prepare local map object
SlambotMap walls;

void setup() {
  Serial.begin(9600);        // Initialize serial port
  // Prepare LIDAR sensor
  pinMode(2, OUTPUT);        // Set pin 2 as trigger pin
  pinMode(3, INPUT);         // Set pin 3 as monitor pin
  digitalWrite(3, LOW);      // Set trigger LOW  
//  turret.step(4096);
  turret.minDelay = 1500;
  Serial.println("\nSetup complete.");
}

void loop() {
  float theta;
  unsigned int lidar_distance;
  unsigned long rev_start_time = millis();

  // For test purposes, we're using 16 measurements per rotation.
  for(int i=0; i<16; i++){
    lidar_distance = pulseIn(3, HIGH)/10;
    theta = turret.getTheta();
    walls.addPointAtRad(theta, lidar_distance);
    turret.step(256);
  }
  Serial.print("\nOne rev completed in ");
  Serial.print( (millis() - rev_start_time)/1000.0);
  Serial.println(" seconds.");
  walls.displayMap();
  Serial.println();
}
