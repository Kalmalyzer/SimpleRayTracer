/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __RAY_H_666_
#define __RAY_H_666_



#include "../maths/vec3.h"

class Ray
{
public:
	Ray(const Vec3& startpos_, const Vec3& unitdir_)
	:	startpos(startpos_),
		unitdir(unitdir_)
	{}



	~Ray(){}

	Vec3 startpos;
	Vec3 unitdir;
};


#endif //__RAY_H_666_