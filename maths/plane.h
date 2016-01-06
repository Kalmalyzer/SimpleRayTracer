/*===================================================================

  
  digital liberation front 2001
  
  _______    ______      _______
 /______/\  |______|    /\______\  
|       \ \ |      |   / /       |    
|	      \| |      |  |/         |  
|_____    \ |      |_ /    ______|       
 ____|    | |      |_||    |_____          
     |____| |________||____|                
           



Code by Nicholas Chapman[/ Ono-Sendai]
nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may not use this code for any commercial project.
====================================================================*/
#ifndef __PLANE_H__
#define __PLANE_H__


#include "vec3.h"
#include "mathstypes.h"
class CoordFrame;

class Plane
{
public:
	inline Plane();
	inline Plane(const Vec3& origin, const Vec3& normal);
	inline Plane(const Vec3& normal, float dist_from_origin);
	inline Plane(const Plane& rhs);
	inline ~Plane();

//	Plane& operator = (const Plane& rhs);

	inline void set(const Vec3& normal, float dist_from_origin);
	inline void set(const Vec3& origin, const Vec3& normal);

	inline void setUnnormalised(const Vec3& origin, const Vec3& nonunit_normal);

	


	inline bool pointOnFrontSide(const Vec3& point) const;

	inline bool pointOnBackSide(const Vec3& point) const;

	inline bool isPointOnPlane(const Vec3& point) const;

	inline const Vec3 calcOrigin() const;//SLOW!

	inline const Vec3 projOnPlane(const Vec3& vec) const;

	inline const Vec3 compNormalToPlane(const Vec3& vec) const;

	inline float signedDistToPoint(const Vec3& p) const;

	inline const Vec3 closestPointOnPlane(const Vec3& p) const;

	inline float getDist() const { return d; }
	inline float getD() const { return d; }

	inline const Vec3& getNormal() const { return normal; }

	//returns fraction of ray travelled. Will be in range [0, 1] if ray hit
	inline float finiteRayIntersect(const Vec3& raystart, const Vec3& rayend) const;

	inline float rayIntersect(const Vec3& raystart, const Vec3 ray_unitdir) const;

	const Plane transformToLocal(const CoordFrame& coordframe) const;

	inline bool isSpherePartiallyOnFrontSide(const Vec3& sphere_center, float radius) const;
	inline bool isSphereTotallyOnFrontSide(const Vec3& sphere_center, float radius) const;

	inline bool isPlaneOnFrontSide(const Plane& p) const;

private:
	float d;
	Vec3 normal;
};


Plane::Plane()
{}

Plane::Plane(const Vec3& origin, const Vec3& normal_)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1.0f) );

	d = dot(origin, normal);
}

Plane::Plane(const Vec3& normal_, float dist_from_origin)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1.0f) );

	d = dist_from_origin;
}

Plane::Plane(const Plane& rhs)
{
	normal = rhs.normal;
	d = rhs.d;
}

Plane::~Plane()
{}

/*Plane& Plane::operator = (const Plane& rhs)
{
	normal = rhs.normal;
	d = rhs.d;

	return *this;
}*/
void Plane::set(const Vec3& normal_, float dist_from_origin)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1.0f) );

	d = dist_from_origin;
}



void Plane::set(const Vec3& origin, const Vec3& normal_)
{
	normal = normal_;

	assert( epsEqual(normal.length(), 1.0f) );

	d = dot(origin, normal);
}

void Plane::setUnnormalised(const Vec3& origin, const Vec3& nonunit_normal)
{
	normal = nonunit_normal;

	normal.normalise();

	d = dot(origin, normal);
}

bool Plane::pointOnFrontSide(const Vec3& point) const
{
	return (dot(point, normal) >= d);
}

bool Plane::pointOnBackSide(const Vec3& point) const
{
	return (dot(point, normal) < d);
}

bool Plane::isPointOnPlane(const Vec3& point) const 
{
	if(fabs(signedDistToPoint(point)) < 0.00001f)
		return true;
	else
		return false;
}


const Vec3 Plane::calcOrigin() const
{
	return normal * d;
}

const Vec3 Plane::projOnPlane(const Vec3& vec) const
{
	return vec - compNormalToPlane(vec);
}

const Vec3 Plane::compNormalToPlane(const Vec3& vec) const
{
	return dot(vec, normal) * normal;
}

float Plane::signedDistToPoint(const Vec3& p) const
{
	return dot(p, normal) - d;
}

const Vec3 Plane::closestPointOnPlane(const Vec3& p) const
{
	return p - (signedDistToPoint(p) * normal);
}

float Plane::finiteRayIntersect(const Vec3& raystart, const Vec3& rayend) const
{
	const float raystart_dot_n = dot(raystart, normal);

	const float rayend_dot_n = dot(rayend, normal);

	const float denom = rayend_dot_n - raystart_dot_n;

	if(denom == 0.0f)
		return -1.0f;

	return (d - raystart_dot_n) / denom;

}

float Plane::rayIntersect(const Vec3& raystart, const Vec3 ray_unitdir) const
{

	const float start_to_plane_dist = signedDistToPoint(raystart);

	return start_to_plane_dist / -dot(ray_unitdir, normal);

	//NOTE: deal with div by 0?

}

/*
const Plane Plane::transformToLocal(const CoordFrame& coordframe) const
{
	const Vec3 pointonplane = closestPointOnPlane(Vec3(0,0,0));

	const Vec3& transformed_point = coordframe.transformPointToLocal(pointonplane);

	const Vec3& transformed_normal = coordframe.transformVecToLocal(getNormal());

	return Plane(transformed_point, transformed_normal);

	//NOTE: check this is right
}*/

bool Plane::isSpherePartiallyOnFrontSide(const Vec3& sphere_center, float radius) const
{
	return signedDistToPoint(sphere_center) <= radius * -1.0f;
}

bool Plane::isSphereTotallyOnFrontSide(const Vec3& sphere_center, float radius) const
{
	return signedDistToPoint(sphere_center) >= radius;
}

bool Plane::isPlaneOnFrontSide(const Plane& p) const
{
	return epsEqual(p.getNormal(), this->getNormal())
				&& p.getDist() > this->getDist();
}



#endif //__PLANE_H__