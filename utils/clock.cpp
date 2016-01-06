/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#include "clock.h"
									
#include <windows.h>
#include <assert.h>
//#include <time.h>

//returns current time in seconds
double getCurTimeRealSec()
{
	static LARGE_INTEGER li_net;
	memset(&li_net, 0, sizeof(li_net));
	BOOL b = QueryPerformanceCounter( &li_net ); 
	assert(b);


	static LARGE_INTEGER freq;
	memset(&freq, 0, sizeof(freq));
	b = QueryPerformanceFrequency(&freq);
	assert(b);


  return (double)(li_net.QuadPart) / (double)(freq.QuadPart);
}






const std::string getAsciiTime()
{
	time_t currenttime;

	time(&currenttime);                 
	
	struct tm *newtime = localtime(&currenttime);
	//NOTE: check for mem leak here
                                   
	std::string s = asctime(newtime);

	if(!s.empty() && s[(int)s.size() - 1] == '\n')
		s = s.substr(0, (int)s.size() - 1);

	return s;
}


time_t getSecsSince1970()
{
	return time(NULL);                 
}

bool leftTimeEarlier(const std::string& time_a, const std::string& time_b)
{


	return true;
}

