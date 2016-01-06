/*===================================================================

  
  digital liberation front 2002
  
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
#ifndef __RAYSPHERE_H__
#define __RAYSPHERE_H__

#include "geometry.h"
#include "../maths/vec3.h"


class RaySphere : public Geometry
{
public:
	RaySphere(const Vec3& pos_, float radius_)
	{
		centerpos = pos_;
		radius = radius_;
		radius_squared = radius_ * radius_;
		recip_radius = 1.0f / radius;
	}

	~RaySphere(){}



	//returns negative number if object not hit by the ray
	virtual float getDistanceUntilHit(const Ray& ray) const;


	virtual const Vec3 getNormalForPos(const Vec3& pos) const;


	Vec3 centerpos;

private:

	float radius;

	//stuff below is precomputed for efficiency
	float radius_squared;
	float recip_radius;
};





#endif //__RAYSPHERE_H__