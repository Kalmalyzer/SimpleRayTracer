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

#ifndef __PLANE2_H__
#define __PLANE2_H__


#include "vec2.h"
#include "mathstypes.h"
#include <assert.h>

class Plane2
{
public:
	inline Plane2();
	inline Plane2(const Vec2& origin, const Vec2& normal);
	inline Plane2(const Vec2& normal, float dist_from_origin);
	inline Plane2(const Plane2& rhs);
	inline ~Plane2();

//	Plane2& operator = (const Plane2& rhs);

	inline void set(const Vec2& normal, float dist_from_origin);
	inline void set(const Vec2& origin, const Vec2& normal);

	inline void setUnnormalised(const Vec2& origin, const Vec2& nonunit_normal);

	


	inline bool pointOnFrontSide(const Vec2& point) const;

	inline bool pointOnBackSide(const Vec2& point) const;

	inline bool isPointOnPlane2(const Vec2& point) const;

	inline const Vec2 calcOrigin() const;//SLOW!

	inline const Vec2 projOnPlane2(const Vec2& vec) const;

	inline const Vec2 compNormalToPlane2(const Vec2& vec) const;

	inline float signedDistToPoint(const Vec2& p) const;

	inline const Vec2 closestPointOnPlane2(const Vec2& p) const;

	inline float getDist() const { return d; }
	inline float getD() const { return d; }

	inline const Vec2& getNormal() const { return normal; }

	//returns fraction of ray travelled. Will be in range [0, 1] if ray hit
	inline float rayIntersect(const Vec2& raystart, const Vec2& rayend) const;

	//returns true if line segment intersected plane
	inline bool getSegIntersectPos(const Vec2& raystart, const Vec2& rayend, Vec2& in_pos_out) const;

	//returns true if line clipped away completely
	inline bool clipLineInPlane(Vec2& start, Vec2& end) const;


private:
	float d;
	Vec2 normal;
};


Plane2::Plane2()
{}

Plane2::Plane2(const Vec2& origin, const Vec2& normal_)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1) );

	d = dot(origin, normal);
}

Plane2::Plane2(const Vec2& normal_, float dist_from_origin)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1) );

	d = dist_from_origin;
}

Plane2::Plane2(const Plane2& rhs)
{
	normal = rhs.normal;
	d = rhs.d;
}

Plane2::~Plane2()
{}

/*Plane2& Plane2::operator = (const Plane2& rhs)
{
	normal = rhs.normal;
	d = rhs.d;

	return *this;
}*/
void Plane2::set(const Vec2& normal_, float dist_from_origin)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1) );

	d = dist_from_origin;
}



void Plane2::set(const Vec2& origin, const Vec2& normal_)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1) );

	d = dot(origin, normal);
}

void Plane2::setUnnormalised(const Vec2& origin, const Vec2& nonunit_normal)
{
	normal = nonunit_normal;

	normal.normalise();

	d = dot(origin, normal);
}

bool Plane2::pointOnFrontSide(const Vec2& point) const
{
	return (dot(point, normal) >= d);
}

bool Plane2::pointOnBackSide(const Vec2& point) const
{
	return (dot(point, normal) < d);
}

bool Plane2::isPointOnPlane2(const Vec2& point) const 
{
	if(fabs(signedDistToPoint(point)) < 0.00001)
		return true;
	else
		return false;
}


const Vec2 Plane2::calcOrigin() const
{
	return normal * d;
}

const Vec2 Plane2::projOnPlane2(const Vec2& vec) const
{
	return vec - compNormalToPlane2(vec);
}

const Vec2 Plane2::compNormalToPlane2(const Vec2& vec) const
{
	return normal * dot(vec, normal);
}

float Plane2::signedDistToPoint(const Vec2& p) const
{
	return dot(p, normal) - d;
}

const Vec2 Plane2::closestPointOnPlane2(const Vec2& p) const
{
	return p - (normal * signedDistToPoint(p));
}

float Plane2::rayIntersect(const Vec2& raystart, const Vec2& rayend) const
{
	const float raystart_dot_n = dot(raystart, normal);

	const float rayend_dot_n = dot(rayend, normal);

	const float denom = rayend_dot_n - raystart_dot_n;

	if(denom == 0)
		return -1;

	return (d - raystart_dot_n) / denom;

}


bool Plane2::getSegIntersectPos(const Vec2& raystart, const Vec2& rayend, Vec2& in_pos_out) const
{
	const float fraction = rayIntersect(raystart, rayend);

	if(fraction > 0 && fraction < 1)
	{
		in_pos_out = rayend;
		in_pos_out.sub(raystart);
		in_pos_out *= fraction;

		in_pos_out += raystart;
		return true;
	}

	return false;
}






//returns true if line clipped away completely
bool Plane2::clipLineInPlane(Vec2& start, Vec2& end/*, bool& waspartiallyclipped_out*/) const
{

	if(pointOnFrontSide(start))
	{
		if(pointOnFrontSide(end))
		{
			//waspartiallyclipped_out = true;
			return true;
		}

		//const float fraction_out = dot(start, normal) / (-dot(end, normal) + dot(start, normal));
		//start += (end - start) * fraction_out;
		start += (end-start) * rayIntersect(start, end);

		//waspartiallyclipped_out = true;
		return false;
	}
	

	if(pointOnFrontSide(end))
	{
		if(pointOnFrontSide(start))
		{
			//waspartiallyclipped_out = true;
			return true;
		}

	//	const float fraction_out = dot(end, normal) / (-dot(start, normal) + dot(end, normal));
	//	end += (start - end) * fraction_out;
		end += (start - end) * rayIntersect(end, start);

		//waspartiallyclipped_out = true;
		return false;
	}

	//waspartiallyclipped_out = false;
	return false;
}










#endif //__PLANE2_H__