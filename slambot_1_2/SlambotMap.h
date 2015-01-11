/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/
#include "Arduino.h"
#include <math.h>

// Solves problems if library is imported more than once.
#ifndef SlambotMap_h
  #define SlambotMap_h

struct wallCloud{
  // Holds x,y positions of obstacles, and potentially other data.
  unsigned int x;    // Big enough for a 2150 ft map
  unsigned int y;
  byte confidence = 0;   // Number of times (0-255) this obstacle has been 'seen'
} localMap[1000];

class SlambotMap{
  public:
    SlambotMap();
    SlambotMap(unsigned int size);
    void addCoord(unsigned int ix, unsigned int iy);
    void addPointAtRad(float theta, unsigned int distance);
    void displayMap();
  private:
    unsigned int mapIndex = 0; // 0-65,535 and after that we need to change data types.
};

SlambotMap::SlambotMap(){
  // Constructor, defaults to a 1000 point map.
//  SlambotMap(1000);
}

SlambotMap::SlambotMap(unsigned int size){
  // Specify how large the initial map should be.
//  localMap = new wallCloud[size];
}

void SlambotMap::addCoord(unsigned int iX, unsigned int iY){
  // Adds a barrier to localMap using an (x,y) pair.
  for(int i=0; i<mapIndex; i++){
    if(localMap[i].x == iX && localMap[i].y == iY){
      localMap[i].confidence++;
      return;
    }
  }
  
  localMap[mapIndex].x = iX;
  localMap[mapIndex].y = iY;
  localMap[mapIndex].confidence++;
  mapIndex++;
}

void SlambotMap::addPointAtRad(float theta, unsigned int distance){
  // Adds a barrier to localMap using theta radians and a distance measurement.
  addCoord( distance*cos(theta), distance*sin(theta) );
}

void SlambotMap::displayMap(){
  Serial.print("mapIndex is: ");
  Serial.println(mapIndex);
  // Used for debugging
  char buffer[100];
  for(int i=0; i<mapIndex; i++){
    snprintf(buffer, 100, "(  %d, %d) has been seen %d times.",
        localMap[i].x, localMap[i].y, localMap[i].confidence);
    Serial.println(buffer);
  }
  
}
#endif
