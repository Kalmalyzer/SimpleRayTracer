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
#include "raysphere.h"

#include "ray.h"



	//returns neg num if object not hit by the ray
float RaySphere::getDistanceUntilHit(const Ray& ray) const
{
	const Vec3 raystarttosphere = this->centerpos - ray.startpos;

	const float dist_to_rayclosest = dotProduct(raystarttosphere, ray.unitdir);


	//-----------------------------------------------------------------
	//check if center of sphere lies behind ray startpos (in dir of ray)
	//-----------------------------------------------------------------
	if(dist_to_rayclosest < 0.0f)//will think of rays as having infinite length || q_closest > ray.length)
		return -666.0f;


	const float sph_cen_to_ray_closest_len2 = raystarttosphere.length2() - 
		dist_to_rayclosest*dist_to_rayclosest;

	//-----------------------------------------------------------------
	//ray has missed sphere?
	//-----------------------------------------------------------------
	if(sph_cen_to_ray_closest_len2 > this->radius_squared)
		return -666.0f;


	//ray has hit sphere...
	
	
	return dist_to_rayclosest - sqrt(this->radius_squared - sph_cen_to_ray_closest_len2);
}


const Vec3 RaySphere::getNormalForPos(const Vec3& point) const 
{ 
	return (point - centerpos) * recip_radius;
}