LBCC-Slambot
============

Forum discussions for LBCC Students can be found at http://elearning.linnbenton.edu/mod/forum/discuss.php?d=118306

This repo will organize code for the LBCC Slambot, a Simultaneous Location And Mapping robot (SLAM robot) which we are building over the 2015 Winter and Spring semesters.  The project will be broken into 3 phases:

**Phase 1: Stationary 2d Mapping**

Keeping our robot in one place will simplify troubleshooting by allowing repeatable tests and eliminating errors introduced by changing the position of our robot.  It will allow us to use predetermined and repeatable distances to test the accuracy of our sensors.

We’ll start out by mounting our laser rangefinder on a spinning platform on top of a table, to create a 2d overhead (x,y) map of the distance to every obstacle in the room.  These distances can be stored as an array and treated as a grid, which can be visualized and debugged.

Using a stationary position will allow us to more easily place obstacles at known distances and confirm the sensor places them correctly into our grid.

 

**Phase 2: Mapping on the Move**

Moving our robot around adds a lot of functionality, but even more complexity.  In phase 2 we will mount our sensor to a remote controlled chassis and move it around, using wheel encoders and sensor data to create a real-time map of the places it’s been.

One major challenge here will be accuracy.  As the robot moves, it will need to update it’s position on the map using wheel encoders, while facing problems like loss of traction or inaccuracies in the wheel movement algorithms.  We will need to be vigilant against even small errors because they will add up over time.

During this phase, the Slambot will NOT attempt to find it’s position on the map, and will create a new, blank map each time it starts up.  These maps may be saved, but never loaded.  This is done because finding a position on a map is quite difficult, and deserves it's own phase.

 

**Phase 3: Persistent Mapping**

By now, we should be able to create accurate maps on the move.  The next challenge is using the maps we’re generating, to find out where our robot is.  This will not be easy.  When the robot starts up, it has no idea where it is and must find it's position based on cues from the environment, such as distances between walls and corners, lengths of hallways, and other sensor inputs.

We plan to create a blank map on startup, as before.  As the robot moves and generates the map, it will compare it against a previously recorded ‘master’ map.  By comparing distances and angles the robot should be able to eliminate poor matches, until a certain threshold of confidence is reached.

At that point, when the robot is reasonably sure it’s temporary map matches the master, it can merge the temporary map into master and begin updating the permanent map directly.
