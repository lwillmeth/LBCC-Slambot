/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/
#include "Arduino.h"
#include <math.h>

// Solves problems if library is imported more than once.
#ifndef SlambotMap_h
  #define SlambotMap_h

typedef struct wallCloud{
  // Holds x,y positions of obstacles, and potentially other data.
  unsigned int x;    // Big enough for a 2150 ft map
  unsigned int y;
  byte confidence;   // Number of times (0-255) this obstacle has been 'seen'
};

class SlambotMap{
  public:
    SlambotMap();  // We could allow them to set the map size.. but.. let's not.
    SlambotMap(unsigned int size);
    void addCoord(unsigned int ix, unsigned int iy);
    void addAngle(unsigned int theta, unsigned int distance);
  private:
    wallCloud localMap[1000];
    unsigned int mapIndex = 0; // 0-65,535 and after that we need to change data types.
};

SlambotMap::SlambotMap(){
  // Constructor, empty for now.
}

SlambotMap::SlambotMap(unsigned int size){
  localMap = wallCloud[1000];
}

void SlambotMap::addCoord(unsigned int iX, unsigned int iY){
  // Adds a barrier to localMap using an (x,y) pair.
  localMap[mapIndex].x = iX;
  localMap[mapIndex].y = iY;
  localMap[mapIndex].confidence++;
  mapIndex++;
}

void SlambotMap::addAngle(unsigned int theta, unsigned int distance){
  // Adds a barrier to localMap using theta radians and a distance measurement.
  localMap[mapIndex].x = distance*cos(theta);
  localMap[mapIndex].y = distance*sin(theta);
  localMap[mapIndex].confidence++;
  mapIndex++;
}
#endif
