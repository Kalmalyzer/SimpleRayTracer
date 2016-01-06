/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#include "graphics2d.h"

#include "../maths/plane2.h"


void Graphics2d::drawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour)
{
	//-----------------------------------------------------------------
	//try early out
	//-----------------------------------------------------------------
	if(	startpos.x > 0 && startpos.x < getWidth() - 1 &&
		startpos.y > 0 && startpos.y < getHeight() - 1 &&
		endpos.x > 0 && endpos.x < getWidth() - 1 &&
		endpos.y > 0 && endpos.y < getHeight() - 1)
		doDrawLine(startpos, endpos, colour);





		//	inline Plane2(const Vec2& normal, float dist_from_origin);
		Vec2 clipped_startpos(startpos);
		Vec2 clipped_endpos(endpos);

		if(endpos.y < 0)
		{
			int a = 9;
		}

		Plane2 top(Vec2(0.0f,-1.0f), -0.1f);

		if(top.clipLineInPlane(clipped_startpos, clipped_endpos))
			return;


		Plane2 right(Vec2(1.0f,0.0f), getWidth() - 1.1f);//right

		if(right.clipLineInPlane(clipped_startpos, clipped_endpos))
			return;



		Plane2 bottom(Vec2(0.0f, 1.0f), getHeight() - 1.1f);//bottom

		if(bottom.clipLineInPlane(clipped_startpos, clipped_endpos))
			return;



		Plane2 left(Vec2(-1.0f, 0.0f), -0.1f);//left

		if(left.clipLineInPlane(clipped_startpos, clipped_endpos))
			return;



		assert(clipped_startpos.y >= -0.1 && clipped_endpos.y >= -0.1);
		assert(clipped_startpos.x >= -0.1 && clipped_endpos.x >= -0.1);

		assert(clipped_startpos.y < getHeight() - 1 && clipped_endpos.y < getHeight() - 1);
		assert(clipped_startpos.x < getWidth() - 1 && clipped_endpos.x < getWidth() - 1);


		doDrawLine(clipped_startpos, clipped_endpos, colour);
}