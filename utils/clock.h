/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __CLOCK_H_666_
#define __CLOCK_H_666_

#include <string>
#include <time.h>

//returns current time in SECONDS

//this is time since commencement of program
double getCurTimeRealSec();



const std::string getAsciiTime();//nicely formatted string

bool leftTimeEarlier(const std::string& asciitime_a, const std::string& asciitime_b);

time_t getSecsSince1970();//hehe

#endif //__CLOCK_H_666_