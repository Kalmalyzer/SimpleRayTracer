/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __SIMPLEWIN2D_H__
#define __SIMPLEWIN2D_H__


// COTD Entry submitted by Joshua Carmody [paladinoftheweb@hotmail.com]
//modified by me (nick c)

#include <windows.h>
#include <string>
#include "../graphics2d/graphics2d.h"
class Vec2;
class Vec3;
class drawingSurface;

/*************************************************************************/
// the bitmapWindow class. This uses the above drawingSurface class to
// easily create a window that we can draw to directly.
/*************************************************************************/
class bitmapWindow : public Graphics2d 
{
  public:
    bitmapWindow(int x, int y, int width, int height, HINSTANCE currentInstance); // Constructor
    ~bitmapWindow(); // Destructor
    static int getNumberOfBitmapWindows(); // Returns static int below
    void setPixel(int x, int y, unsigned long color); // Set Pixel data in our pointer to the specified color
    void drawLineInt(int x1, int y1, int x2, int y2, unsigned long color); // Draw a line from x1,y1 to x2,y2 in the specified color
    void erase(unsigned long color); // Passes the erase request to the drawingSurface
    void flipIntoView(); // Copies window pixels from memory pointer to screen.






	//-----------------------------------------------------------------
	//NEWCODE: satisfy Graphics2d interface.
	//-----------------------------------------------------------------
	virtual void clear();

	virtual void startDrawing();
	virtual void finishDrawing();

	virtual int getWidth() const;
	virtual int getHeight() const;


	virtual void drawPixel(const Vec2& pos, const Vec3& colour);

	virtual void drawPixel(int xpos, int ypos, const Vec3& colour);


	virtual void doDrawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour);

	virtual void drawRect(const Vec2& pos, int width, int height, const Vec3& colour);


	virtual void drawText(const Vec2& pos, const std::string& text, const Vec3& colour);

	HWND getWindowHandle(){ return windowHandle; } 


	inline void fastDrawPixelAdvance(const Vec3& colour)
	{
		*writeindex++ = RGB(colour.x*255, colour.y*255, colour.z*255);
	}

	void advanceToNextRow(int currentx);


  protected:
    HWND windowHandle; // The handle for the window we'll pop up.
    void registerWindowClass(HINSTANCE currentInstance); // For registering the class of window we'll use
    static BOOL classIsRegistered; // Have we, or have we not, registered our window class?
    static int numberOfBitmapWindows; // The number of these classes in use
    int windowWidth, windowHeight; // Store the window's dimensions
    drawingSurface *windowContents; // easy DIB class defined above

	unsigned long* writeindex;
};






/*************************************************************************/
// drawingSurface class. Allows for very easy drawing to a window.
/*************************************************************************/
class drawingSurface {
  public:
    drawingSurface(int width, int height); // Constructor
    ~drawingSurface(); // Destructor
    
	inline void setPixel(int x, int y, unsigned long color); // Set Pixel data in our pointer to the specified color
    inline void setPixelUnclipped(int x, int y, unsigned long color);
	
	void drawLineInt(int x1, int y1, int x2, int y2, unsigned long color); // Draw a line from x1,y1 to x2,y2 in the specified color
    void display(int x, int y, HWND windowHandle); // Copies window pixels from memory pointer to screen.
    void erase(unsigned long color); // Completely fills the bitmap with the specified color
    int getWidth(); // Return the bitmap's width.
    int getHeight(); // Return the bitmap's height.

	void drawRect(const Vec2& pos, int width, int height, const Vec3& colour);

	HBITMAP getBitmap(){ return scratchPadBitmap; }

	unsigned long* getSurface(){ return windowContents; }

  protected:
    HBITMAP scratchPadBitmap; // Temporary Bitmap
    unsigned long *windowContents; // Pointer to pixel data to display in the window
    int windowWidth, windowHeight; // Store the window's dimensions
};

/*************************************************************************/
// setPixel, sets the pixel at x, y to color inside the DIB
/*************************************************************************/
inline void drawingSurface::setPixel(int x, int y, unsigned long color)
{
	//NEWCODE: clip out pixels off screen
	if(x < 0 || x >= windowWidth || y < 0 || y >= windowHeight)
		return;


  *(windowContents + (x + (y * windowWidth))) = color;
}

inline void drawingSurface::setPixelUnclipped(int x, int y, unsigned long color)
{
  *(windowContents + (x + (y * windowWidth))) = color;
}

#endif //__SIMPLEWIN2D_H__