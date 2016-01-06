/*=====================================================================
geometry.h
----------
File created by ClassTemplate on Wed Apr 14 21:19:37 2004
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __GEOMETRY_H_666_
#define __GEOMETRY_H_666_


class Ray;
class Vec3;
class World;
class Colour;

/*=====================================================================
Geometry
--------
interface that represents the shape of an object
=====================================================================*/
class Geometry
{
public:
	/*=====================================================================
	Geometry
	--------
	
	=====================================================================*/
	//Geometry();

	virtual ~Geometry(){}


	//returns negative number if object not hit by the ray
	virtual float getDistanceUntilHit(const Ray& ray) const = 0;

	virtual const Vec3 getNormalForPos(const Vec3& pos) const = 0;
};



#endif //__GEOMETRY_H_666_




