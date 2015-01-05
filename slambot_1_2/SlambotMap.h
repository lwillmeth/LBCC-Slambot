/*
A library written for the LBCC Slambot on Jan 1, 2015, by Levi Willmeth.
*/
#include "Arduino.h"
// Solves problems if library is imported more than once.
#ifndef SlambotMap_h
  #define SlambotMap_h

class SlambotMap{
  public:
    SlambotMap();  // We could allow them to set the map size.. but.. let's not.
    void addPoint(unsigned long ix, unsigned long iy);

  private:
    mapPoint _allMaps;
    unsigned int mapIndex; // 0-65,535 and after that we need to change data types.
};

SlambotMap::SlambotMap(){
  _allMaps = mapPoint[1000];    // 1,000 readings should create a fairly large map.
  unsigned int mapIndex = 0;    // redundant
}

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

#endif
