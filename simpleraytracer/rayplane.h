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
#ifndef __RAYPLANE_H__
#define __RAYPLANE_H__

#include "geometry.h"
#include "../maths/plane.h"

class RayPlane : public Geometry
{
public:
	RayPlane(const Plane& plane);
	~RayPlane(){}


	//returns negative number if object not hit by the ray
	virtual float getDistanceUntilHit(const Ray& ray) const;

	virtual const Vec3 getNormalForPos(const Vec3& pos) const { return plane.getNormal(); }


private:
	Plane plane;
};


#endif //__RAYPLANE_H__