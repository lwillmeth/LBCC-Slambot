/*
First draft of the software controlling the LBCC SlamBot.
See https://github.com/lo9key/LBCC-Slambot for commit history, bug notes, etc.
*/
#include <Stepper.h>
//#include <AccelStepper.h>

typedef struct mapPoint{
  /*
  Holds x,y positions of obstacles, and potentially other data.
  More thought needs to go into mapping wifi signals:
    One option is to store the wifi node's mac address here.
    Another, probably better, option is to make a seperate map just for wifi.
  */
  unsigned int x;
  unsigned int y;
  byte confidence;  // Number of times this obstacle has been 'seen'
};

// Prepare a blank array to hold (temporary) local map values
mapPoint localMap[1000];    // 1,000 readings should create a fairly large map.
unsigned int mapIndex = 0;  // 0-65,535, after that we need to change data types.

// Prepare LIDAR turret
const int stepsPerRev = 64*32;    // 64 gear teeth * 32 steps in full step mode = 2048 positions
unsigned long current_step = 0;  // Start out at 0 deg
int numSteps = 1;
unsigned int speed = 1;
// The 28YBJ-48 stepper motor pins must be in a 1-3-2-4 pattern, so use pins 8, 10, 9, 11.
Stepper turret(stepsPerRev, 8, 10, 9, 11);
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
  current_step = 0;
  //  turret.setSpeed(++speed);
  
  while(current_step <= stepsPerRev){
    turret.step(numSteps); // number of steps to move
    current_step += numSteps;
    //  turret.runSpeed();
    /*
    lidar_distance = pulseIn(3, HIGH)/10;  // Determine how long monitor pin was high, 10 usec = ~1 cm
    Serial.print(lidar_distance);
    Serial.print(", ");
    */
  }
  numSteps *= -1;
  
  Serial.print("\nOne rev completed in ");
  Serial.print( (millis() - rev_start_time)/1000);
  Serial.print(" seconds at speed ");
  Serial.println(speed);
}

