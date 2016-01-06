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
#ifndef __VEC3_H__
#define __VEC3_H__



/*=================================================================
3 component vector class
------------------------
Coded by NIck Chapman in the year 2000-
=================================================================*/

#include <math.h>
#include "mathstypes.h"
#include <assert.h>
#include <string>

#ifdef CYBERSPACE
#include "../cyberspace/mystream.h"
#endif

//#pragma warning (disable:4244)
//disable "conversion from 'double' to 'float', possible loss of data"


class Vec3
{
public:

	inline Vec3()
	{}

	inline ~Vec3()
	{}

	inline Vec3(float x_, float y_, float z_)
	:	x(x_),
		y(y_),
		z(z_)
	{}

	inline Vec3(const Vec3& rhs)
	:	x(rhs.x),
		y(rhs.y),
		z(rhs.z)
	{}

	inline Vec3(const float* f)
	:	x(f[0]),
		y(f[1]),
		z(f[2])
	{}

	inline Vec3(const Vec3& v, float scale)
	:	x(v.x * scale),
		y(v.y * scale),
		z(v.z * scale)
	{}
		

	inline void set(float newx, float newy, float newz)
	{
		x = newx;
		y = newy;
		z = newz;
	}

	inline float& operator[] (int index)
	{
		//NOTE: no asserting
		return ((float*)(&x))[index];
	}

	inline const float& operator[] (int index) const
	{
		//NOTE: no asserting
		return ((float*)(&x))[index];
	}

	inline const Vec3 operator + (const Vec3& rhs) const
	{
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}


	inline const Vec3 operator - (const Vec3& rhs) const
	{	
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	inline const Vec3 operator * (const Vec3& rhs) const
	{	
		return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}



	inline Vec3& operator += (const Vec3& rhs)
	{		
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	inline Vec3& operator -= (const Vec3& rhs)
	{	
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	inline Vec3& operator = (const Vec3& rhs)
	{	
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	inline bool operator == (const Vec3& rhs) const
	{
		return ( (x == rhs.x) && (y == rhs.y) && (z == rhs.z) );
	}

	inline bool operator != (const Vec3& rhs) const
	{
		return ( (x != rhs.x) || (y != rhs.y) || (z != rhs.z) );
	}

	//for sorting Vec3's
	inline bool operator < (const Vec3& rhs) const
	{
		if(x < rhs.x)
			return true;
		else if(x > rhs.x)
			return false;
		else	//else x == rhs.x
		{
			if(y < rhs.y)
				return true;
			else if(y > rhs.y)
				return false;
			else
			{
				/*if(z < rhs.z)
					return true;
				else if(z >= rhs.z)
					return false;*/
				return z < rhs.z;
			}
		}
	}

	inline void normalise()
	{
		//if(!x && !y && !z)
		//	return;

		float inverselength = length();//will be inverted later

		if(!inverselength)
			return;

		inverselength = 1.0f / inverselength;//invert it

		x *= inverselength;
		y *= inverselength;
		z *= inverselength;
	}


	inline void fastNormalise()
	{
		const float inverselength = RSqrt( length2() );

		//if(!inverselength)
		//	return;

		x *= inverselength;
		y *= inverselength;
		z *= inverselength;
	}

	inline float normalise_ret_length()
	{
		//if(!x && !y && !z)
		//	return 0.0f;

		const float len = length();

		if(!len)
			return 0.00001f;

		const float inverselength = 1.0f / len;

		x *= inverselength;
		y *= inverselength;
		z *= inverselength;

		return len;
	}

	inline float normalise_ret_length(float& inv_len_out)
	{
		//if(!x && !y && !z)
		//	return 0.0f;

		const float len = length();

		if(!len)
			return 0.00001f;

		const float inverselength = 1.0f / len;

		x *= inverselength;
		y *= inverselength;
		z *= inverselength;

		inv_len_out = inverselength;

		return len;
	}

	inline float normalise_ret_length2()
	{
		//if(!x && !y && !z)
		//	return 0.0f;

		const float len2 = length2();

		if(!len2)
			return 0.00001f;

		const float inverselength = 1.0f / sqrt(len2);

		x *= inverselength;
		y *= inverselength;
		z *= inverselength;

		return len2;
	}




	inline float length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	inline float length2() const
	{
		return (x*x + y*y + z*z);
	}

	inline void scale(float factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
	}

	inline Vec3& operator *= (float factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	inline void setLength(float newlength)
	{
		const float current_len = length();

		if(!current_len)
			return;

		scale(newlength / current_len);
	}

	inline Vec3& operator /= (float divisor)
	{
		*this *= (1.0f / divisor);
		return *this;
	}

	inline const Vec3 operator * (float factor) const
	{
		return Vec3(x * factor, y * factor, z * factor);
	}

	inline const Vec3 operator / (float divisor) const
	{
		const float inverse_d = (1.0f / divisor);

		return Vec3(x * inverse_d, y * inverse_d, z * inverse_d);
	}

	inline void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline float getDist(const Vec3& other) const
	{
		const Vec3 dif = other - *this;
		return dif.length();
	}

	inline float getDist2(const Vec3& other) const
	{
		//const Vec3 dif = other - *this;
		//return dif.length2();
		//float sum = other.x - x;

		//sum += other.y - y;

		//sum += other.z - z;

		float sum = other.x - x;
		sum *= sum;

		float dif = other.y - y;
		sum += dif*dif;

		dif = other.z - z;

		return sum + dif*dif;


		//return (other.x - x) + (other.y - y) + (other.z - z);
	}

	inline void assertUnitVector() const
	{
		const float len = length();

		const float var = fabs(1.0f - len);

		const float EPSILON_ = 0.0001f;

		assert(var <= EPSILON_);
	}

	void print() const;
	const std::string toString() const;

//	const static Vec3 zerovector;	//(0,0,0)
//	const static Vec3 i;			//(1,0,0)
//	const static Vec3 j;			//(0,1,0)
//	const static Vec3 k;			//(0,0,1)

	float x,y,z;



	inline const float* data() const { return (float*)this; }
	



	//-----------------------------------------------------------------
	//Euler angle stuff
	//-----------------------------------------------------------------
	//static Vec3 ws_up;//default z axis
	//static Vec3 ws_right;//default -y axis
	//static Vec3 ws_forwards;//must = crossProduct(ws_up, ws_right).   default x axis

	//static void setWsUp(const Vec3& vec){ ws_up = vec; }
	//static void setWsRight(const Vec3& vec){ ws_right = vec; }
	//static void setWsForwards(const Vec3& vec){ ws_forwards = vec; }

	float getYaw() const { return x; }
	float getPitch() const { return y; }
	float getRoll() const { return z; }

	void setYaw(float newyaw){ x = newyaw; }
	void setPitch(float newpitch){ y = newpitch; }
	void setRoll(float newroll){ z = newroll; }

	/*==================================================================
	getAngles
	---------
	Gets the Euler angles of this vector.  Returns the vector (yaw, pitch, roll). 
	Yaw is the angle between this vector and the vector 'ws_forwards' measured
	anticlockwise when looking towards the origin from along the vector 'ws_up'.
	Yaw will be in the range (-Pi, Pi).

	Pitch is the angle between this vector and the vector 'ws_forwards' as seen when
	looking from along the vecotr 'ws_right' towards the origin.  A pitch of Pi means
	the vector is pointing along the vector 'ws_up', a pitch of -Pi means the vector is
	pointing straight down. (ie pointing in the opposite direction from 'ws_up'.
	A pitch of 0 means the vector is in the 'ws_right'-'ws_forwards' plane.
	Will be in the range [-Pi/2, Pi/2].

	Roll will be 0.
	====================================================================*/
	const Vec3 getAngles(const Vec3& ws_forwards, const Vec3& ws_up, const Vec3& ws_right) const;
	//const Vec3 getAngles() const; //around i, j, k

	const Vec3 fromAngles(const Vec3& ws_forwards, const Vec3& ws_up, const Vec3& ws_right) const;

	float dotProduct(const Vec3& rhs) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	float dot(const Vec3& rhs) const
	{
		return dotProduct(rhs);
	}

	static const Vec3 randomVec(float component_lowbound, float component_highbound);


	inline void setToMult(const Vec3& other, float factor)
	{
		x = other.x * factor;
		y = other.y * factor;
		z = other.z * factor;
	}

	inline void addMult(const Vec3& other, float factor)
	{
		x += other.x * factor;
		y += other.y * factor;
		z += other.z * factor;
	}

	inline void subMult(const Vec3& other, float factor)
	{
		x -= other.x * factor;
		y -= other.y * factor;
		z -= other.z * factor;
	}

	inline void add(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	inline void sub(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	inline void removeComponentInDir(const Vec3& unitdir)
	{
		subMult(unitdir, this->dot(unitdir));
	}
};

inline const Vec3 normalise(const Vec3& v)
{
	const float vlen = v.length();

	if(!vlen)
		return Vec3(1.0f, 0.0f, 0.0f);

	return v * (1.0f / vlen);
}

inline const Vec3 operator * (float m, const Vec3& right)
{
	return Vec3(right.x * m, right.y * m, right.z * m);
}


inline float dotProduct(const Vec3& v1, const Vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

inline float dot(const Vec3& v1, const Vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


inline const Vec3 crossProduct(const Vec3& v1, const Vec3& v2)
{
	return Vec3(
	(v1.y * v2.z) - (v1.z * v2.y),
	(v1.z * v2.x) - (v1.x * v2.z),
	(v1.x * v2.y) - (v1.y * v2.x)
	);	//NOTE: check me

}

	//v1 and v2 unnormalized
inline float angleBetween(Vec3& v1, Vec3& v2)
{
	const float lf = v1.length() * v2.length();

	if(!lf)
		return 1.57079632679489661923f;

	const float dp = dotProduct(v1, v2);

	return acos( dp / lf);
}

inline float angleBetweenNormalized(const Vec3& v1, const Vec3& v2)
{
	const float dp = dotProduct(v1, v2);

	return acos(dp);
}


inline bool epsEqual(const Vec3& v1, const Vec3& v2)
{
	const float dp = dotProduct(v1, v2);

	return dp >= 0.99999f;
}


inline std::ostream& operator << (std::ostream& stream, const Vec3& point)
{
	stream << point.x << " ";
	stream << point.y << " ";	
	stream << point.z << " ";

	return stream;
}

inline std::istream& operator >> (std::istream& stream, Vec3& point)
{
	stream >> point.x;
	stream >> point.y;	
	stream >> point.z;

	return stream;
}

#ifdef CYBERSPACE

inline MyStream& operator << (MyStream& stream, const Vec3& point)
{
	stream << point.x;
	stream << point.y;	
	stream << point.z;

	return stream;
}

inline MyStream& operator >> (MyStream& stream, Vec3& point)
{
	stream >> point.x;
	stream >> point.y;	
	stream >> point.z;

	return stream;
}

#endif//CYBERSPACE

#endif //__VEC3_H__