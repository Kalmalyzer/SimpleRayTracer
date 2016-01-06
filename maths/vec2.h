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
#ifndef __Vec2_H__
#define __Vec2_H__



/*=================================================================
2 component vector class
------------------------
Coded by NIck Chapman in the year 2000
=================================================================*/

#include <math.h>

#ifdef CYBERSPACE
#include "../cyberspace/mystream.h"
#endif


//#pragma warning (disable:4244)
//disable "conversion from 'double' to 'float', possible loss of data"


class Vec2
{
public:

	inline Vec2()
	{}

	inline ~Vec2()
	{}

	inline Vec2(float x_, float y_)
	:	x(x_),
		y(y_)
	{}

	inline Vec2(const Vec2& rhs)
	:	x(rhs.x),
		y(rhs.y)
	{}

	inline void set(float newx, float newy)
	{
		x = newx;
		y = newy;
	}

	inline const Vec2 operator + (const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	inline const Vec2 operator - (const Vec2& rhs) const
	{	
		return Vec2(x - rhs.x, y - rhs.y);
	}

	inline Vec2& operator += (const Vec2& rhs)
	{		
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	inline Vec2& operator -= (const Vec2& rhs)
	{	
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	inline Vec2& operator = (const Vec2& rhs)
	{	
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	inline bool operator == (const Vec2& rhs) const
	{
		return ( (x == rhs.x) && (y == rhs.y) );
	}

		//for sorting Vec2's
	inline bool operator < (const Vec2& rhs) const
	{
		if(x < rhs.x)
			return true;
		else if(x > rhs.x)
			return false;
		else	//else if x == rhs.x
		{
			return y < rhs.y;
		}
	}

	inline void normalise()
	{
		if(!x && !y)
			return;

		const float inverselength = 1.0f / length();

		x *= inverselength;
		y *= inverselength;
	}

	inline float normalise_ret_length()
	{
		if(!x && !y)
			return 0.0f;

		const float len = length();

		const float inverselength = 1.0f / len;

		x *= inverselength;
		y *= inverselength;

		return len;
	}

	inline float length() const
	{
		return (float)sqrt(x*x + y*y);
	}

	inline float length2() const
	{
		return (x*x + y*y);
	}

	inline void setLength(float newlength)
	{
		const float current_len = length();

		if(!current_len)
			return;

		scale(newlength / current_len);
	}

	inline float getDist2(const Vec2& other) const
	{
		const Vec2 dif = other - *this;
		return dif.length2();
	}

	inline float getDist(const Vec2& other) const
	{
		const Vec2 dif = other - *this;
		return dif.length();
	}

	inline void scale(float factor)
	{
		x *= factor;
		y *= factor;
	}

	inline Vec2& operator *= (float factor)
	{
		x *= factor;
		y *= factor;
		return *this;
	}

	inline Vec2& operator /= (float divisor)
	{
		*this *= (1.0f / divisor);
		return *this;
	}

	inline const Vec2 operator * (float factor) const
	{
		return Vec2(x * factor, y * factor);
	}

	inline const Vec2 operator / (float divisor) const
	{
		const float inverse_d = (1.0f / divisor);

		return Vec2(x * inverse_d, y * inverse_d);
	}

	inline void zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	void print() const;

	const static Vec2 zerovector;	//(0,0,)
	const static Vec2 i;			//(1,0,)
	const static Vec2 j;			//(0,1,0)

	float x,y;

	float dotProduct(const Vec2& rhs) const
	{
		return x*rhs.x + y*rhs.y;
	}

	float dot(const Vec2& rhs) const
	{
		return dotProduct(rhs);
	}

	static const Vec2 randomVec(float component_lowbound, float component_highbound);

	inline const float* data() const { return (float*)this; }

	inline void sub(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
	}

};





inline float dotProduct(const Vec2& v1, const Vec2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

inline float dot(const Vec2& v1, const Vec2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}


/*inline const Vec2 crossProduct(const Vec2& v1, const Vec2& v2)
{
	return Vec2(
	(v1.y * v2.z) - (v1.z * v2.y),
	(v1.z * v2.x) - (v1.x * v2.z),
	(v1.x * v2.y) - (v1.y * v2.x)
	);	//NOTE: check me

}*/

	//v1 and v2 unnormalized
/*inline float angleBetween(Vec2& v1, Vec2& v2)
{
	float lf = v1.length() * v2.length();

	if(!lf)
		return PI_OVER_2; //90 //Pi/2 = 1.57079632679489661923

	float dp = dotProduct(v1, v2);

	return acos( dp / lf);
}*/

inline float angleBetweenNormalized(const Vec2& v1, const Vec2& v2)
{
	const float dp = dotProduct(v1, v2);

	return (float)acos(dp);
}

inline const Vec2 normalise(const Vec2& v)
{
	const float vlen = v.length();

	if(!vlen)
		return Vec2(1.0f, 0.0f);

	return v * (1.0f / vlen);
}


#ifdef CYBERSPACE

inline MyStream& operator << (MyStream& stream, const Vec2& point)
{
	stream << point.x;
	stream << point.y;	

	return stream;
}

inline MyStream& operator >> (MyStream& stream, Vec2& point)
{
	stream >> point.x;
	stream >> point.y;	

	return stream;
}

#endif//CYBERSPACE


#endif //__Vec2_H__