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
#include "rayplane.h"

#include "ray.h"



RayPlane::RayPlane(const Plane& plane_)
:	plane(plane_)
{
	
}

float RayPlane::getDistanceUntilHit(const Ray& ray) const
{
	//NOTE: deal with div by 0?

	return (ray.startpos.dot(plane.getNormal()) - plane.getDist()) / 
			-dot(plane.getNormal(), ray.unitdir);
}

