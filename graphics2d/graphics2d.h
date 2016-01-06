/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

/*
interface for something that can draw 2d graphics
*/

#include "../maths/vec2.h"
#include "../maths/vec3.h"
#include <string>



class Graphics2d
{
public:
	virtual ~Graphics2d(){}

	virtual void startDrawing(){}
	virtual void finishDrawing(){}

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;


	virtual void drawPixel(const Vec2& pos, const Vec3& colour) = 0;
	virtual void drawPixel(int xpos, int ypos, const Vec3& colour)
	{
		drawPixel(Vec2(xpos, ypos), colour);
	}
	virtual void drawPixel(int xpos, int ypos, unsigned char r, unsigned char g, unsigned char b)
	{
		drawPixel(Vec2(xpos, ypos), Vec3((float)r / 255, (float)g / 255, (float)b / 255));
	}

	virtual void drawRect(const Vec2& pos, int width, int height, const Vec3& colour)
	{
		const int endx = pos.x + width;
		const float endy = pos.y + height;
		
		//-----------------------------------------------------------------
		//draw vertical lines
		//-----------------------------------------------------------------
		for(int x=pos.x; x<endx; x++)
		{
			drawLine(Vec2(x, pos.y), Vec2(x, endy), colour);
		}
	}

	virtual void clear(){}//NOTE: FIXME






	//-----------------------------------------------------------------
	//draws a clipped line
	//-----------------------------------------------------------------
	void drawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour);
		
	//-----------------------------------------------------------------
	//hook method to draw unclipped line
	//-----------------------------------------------------------------
	virtual void doDrawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour) = 0;


	virtual void drawText(const Vec2& pos, const std::string& text, const Vec3& colour) = 0;
};



#endif //__GRAPHICS2D_H__