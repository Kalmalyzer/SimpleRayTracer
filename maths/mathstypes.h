/*===================================================================

  
  digital liberation front 2001
  
  _______    ______      _______
 /______/\  |______|    /\______\  
|       \ \ |      |   / /       |    
|	      \| |      |  |/         |  
|_____    \ |      |_ /    ______|       
 ____|    | |      |_||    |_____          
     |____| |________||____|                
           



Code by Nicholas Chapman
nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may not use this code for any commercial project.
====================================================================*/
#ifndef __MATHSTYPES_H__
#define __MATHSTYPES_H__

#include <math.h>

const float NICKMATHS_EPSILON = 0.00001f;

//from Ipion
const float NICKMATHS_PI = 3.14159265358979323846f;

const float NICKMATHS_2PI = NICKMATHS_PI * 2;

const float NICKMATHS_PI_2 = NICKMATHS_PI / 2;
const float NICKMATHS_PI_4 = NICKMATHS_PI / 4;

inline bool epsEqual(float a, float b)
{
	//NOTE: this could be much better
 	const float absdif = (float)fabs(a - b);

	if(absdif <= NICKMATHS_EPSILON)
		return true;
	else
		return false;
}

inline bool epsEqual(float a, float b, float epsilon)
{
	//NOTE: this could be much better
 	const float absdif = (float)fabs(a - b);

	if(absdif <= epsilon)
		return true;
	else
		return false;
}

inline float radToDegree(float rad)
{
	return rad * 180.0f / NICKMATHS_PI;	
}

inline float degreeToRad(float degree)
{
	return degree * NICKMATHS_PI / 180.0f;
}


inline float absoluteVal(float x)
{
	if(x < 0)
		return -x;
	else
		return x;
}


inline float raiseBy2toN(float x, int n)
{
	//-----------------------------------------------------------------
	//isolate exponent bits
	//-----------------------------------------------------------------
	unsigned int exponent_bits = *((int*)&x) & 0x7F400000;

	//-----------------------------------------------------------------
	//bitshift them
	//-----------------------------------------------------------------
	exponent_bits >>= n;

	//-----------------------------------------------------------------
	//blank out old bits
	//-----------------------------------------------------------------
	*((int*)&x) &= 0x8001FFFF;

	//-----------------------------------------------------------------
	//copy new bits in
	//-----------------------------------------------------------------
	*((int*)&x) &= exponent_bits;

	return x;
}





// Fast reciprocal square root
//posted by DarkWIng on Flipcode

__inline float RSqrt( float number ) 
{
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = number * 0.5f;
	y  = number;
	i  = * (long *) &y;			// evil floating point bit level hacking
	i  = 0x5f3759df - (i >> 1);             // what the f..k?
	y  = * (float *) &i;
	y  = y * (threehalfs - (x2 * y * y));   // 1st iteration

	return y;
}



#endif //__MATHSTYPES_H__