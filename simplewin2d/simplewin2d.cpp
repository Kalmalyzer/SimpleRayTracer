/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#include "simplewin2d.h"


//#include "../maths/maths.h"


// COTD Entry submitted by Joshua Carmody [paladinoftheweb@hotmail.com]
//modified by me (nick c)

const float MAX_UBYTE_VAL = 255.0f;



/*************************************************************************/
// drawingSurface constructor. Creates a "drawing surface" (DIB) for the
// application to draw to. Takes two parameters, width, and height.
/*************************************************************************/
drawingSurface::drawingSurface(int width, int height) {
  windowWidth = width; // Store the width
  windowHeight = height; // Store the height

  HANDLE heap = GetProcessHeap(); // Get a memory block from windows

  // Allocate memory for the BITMAPINFO and BITMAPINFOHEADER structures.
  // The BITMAPINFO structure is just a BITMAPINFOHEADER structure with
  // RGBQUADs at the end, so we use this code so both structures share the
  // same memory.
  BITMAPINFO *format = (BITMAPINFO *)HeapAlloc(heap, 0, sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 3));
  BITMAPINFOHEADER *header = (BITMAPINFOHEADER*)format;

  header->biSize = sizeof(BITMAPINFOHEADER); // This structure is as big as it is. This is a stupid value required by windows
  header->biWidth = width; // Width of the bitmap
  header->biHeight = -height; // Height of the bitmap. Negative values indicate a top-down bitmap instead of a bottom-up
  header->biPlanes = 1; // 1 plane. Always 1 plane. Never changes.
  header->biBitCount = 32; // 32 bits per pixel, TrueColor
  header->biCompression = BI_RGB; // No compression
  header->biSizeImage = 0; // The size of the image, we can ommit this for a non-compressed image
  header->biXPelsPerMeter = 0; // number of pixels per horizontal meter (we don't care)
  header->biYPelsPerMeter = 0; // number of pixels per vertical meter (we don't care)
  header->biClrUsed = 0; // How many colors are used? 0 means maxiumum
  header->biClrImportant = 0; // How many colors are "important", 0 means all of 'em

  // Create the DIB
  scratchPadBitmap = CreateDIBSection(
    NULL, // DC for the DIB top be compatible with, doesn't matter for 32-bit images
    format, // Bitmap Information
    DIB_RGB_COLORS, // Direct RGB values, instead of paletted values
    (void**)&windowContents, // A pointer to receive a pointer to the bitmap's bytes
    NULL, // This parameter and the next one have to deal with file mapping,
    0     // a subject I don't completely understand.
  );

  HeapFree(heap,0,format); // Free previously allocated memory
}



/*************************************************************************/
// Destructor for drawingSurface, cleans up vairables and frees memory.
/*************************************************************************/
drawingSurface::~drawingSurface() {
  DeleteObject(scratchPadBitmap);
}







/*************************************************************************/
// drawLine draws a line from x1, y1 to x2, y2 in the specified color
/*************************************************************************/
void drawingSurface::drawLineInt(int x1, int y1, int x2, int y2, unsigned long color) {
  int i, j, k, deltaX, deltaY, /*a,NEWCODE*/ testX, testY;

  testX = deltaX = (x2 - x1);
  testY = deltaY = (y2 - y1);
  if(testX < 0) { testX *= -1; }
  if(testY < 0) { testY *= -1; }

  if(testX > testY) {
    for(i=0;i<testX;i++) {
      j = ((i * deltaY) / testX);
      k = ((deltaX * i) / testX);
      setPixelUnclipped(k+x1, j+y1, color);//*(windowContents + ((k + x1) + ((j + y1) * windowWidth))) = color;
    }
  }
  else if(testX <= testY) {
    for(i=0;i<testY;i++) {
      j = ((i * deltaX) / testY);
      k = ((deltaY * i) / testY);
      setPixelUnclipped(j+x1, k+y1, color);//*(windowContents + ((j + x1) + ((k + y1) * windowWidth))) = color;
    }
  }
}




/*************************************************************************/
// Erases the entire bitmap (fills with the specifier color)
/*************************************************************************/
void drawingSurface::erase(unsigned long color) {
  int i, j;
  for(i=0;i<windowWidth;i++) {
    for(j=0;j<windowHeight;j++) {
      *(windowContents + i + (j * windowWidth)) = color;
    }
  }
}




/*************************************************************************/
// display, Render the DIB inside the specified window at the specifier
// coordinates
/*************************************************************************/
void drawingSurface::display(int x, int y, HWND windowHandle) {
  HDC windowDC = GetDC(windowHandle); // Get the DC for this window
  HDC memoryDC = CreateCompatibleDC(windowDC); // Create a compatible one in memory

  // Save the old bitmap currently in the memory DC. We do this so we can
  // put it back before we delete it. I don't know why, but windows makes
  // you do this.
  HBITMAP oldBitmap = (HBITMAP)SelectObject(memoryDC, scratchPadBitmap);

  // Copy the bitmap data from the memory DC to the one in the window
  BitBlt(
   windowDC, // The DC of the destination window
   x, // The X coordinate to copy to
   y, // the Y coordinate to copy to
   windowWidth, // Width of the area we're copying
   windowHeight, // Height of the area we're copying
   memoryDC, // DC in memory that holds the source bitmap
   0, // X coordinate in source bitmap
   0, // Y coordinate in source bitmap
   SRCCOPY // COPY the data (instead of doing a bitwise AND or something)
  );

  SelectObject(memoryDC, oldBitmap); // Put the old bitmap back before we delete the DC
  DeleteDC(memoryDC); // Delete the DC
  ReleaseDC(windowHandle, windowDC); // Release the window's DC
}



/*************************************************************************/
// Return the DIB's width
/*************************************************************************/
int drawingSurface::getWidth() {
  return windowWidth;
}




/*************************************************************************/
// Return the DIB's height
/*************************************************************************/
int drawingSurface::getHeight() {
  return windowHeight;
}

void drawingSurface::drawRect(const Vec2& pos, int width, int height, const Vec3& colour)
{
	const int xres = windowWidth;
	const int yres = windowHeight;

	int topleftx = pos.x;
	int toplefty = pos.y;

	//-----------------------------------------------------------------
	//clip to screen
	//-----------------------------------------------------------------
	if(topleftx < 0)
	{
		width += topleftx;

		if(width <= 0)
			return;

		topleftx = 0;
	}
	if(topleftx + width >= xres)
	{
		width = xres - topleftx - 1;
		
		if(width <= 0)
			return;
	}


	if(toplefty < 0)
	{
		height += toplefty;

		if(height <= 0)
			return;

		toplefty = 0;
	}
	if(toplefty + height >= yres)
	{
		height = yres - toplefty - 1;
		
		if(height <= 0)
			return;
	}


	//-----------------------------------------------------------------
	//now draw clipped rect
	//-----------------------------------------------------------------
	const unsigned long col = RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL);

	const int jump_dist = xres - width;

	//-----------------------------------------------------------------
	//position iterator at top left pixel
	//-----------------------------------------------------------------
	unsigned long* rowiterator = windowContents + toplefty*xres + topleftx;

	for(int y=0; y<height; ++y)//for each row
	{
		const unsigned long* end = rowiterator + width;//get iterator pointing to end of row

		//-----------------------------------------------------------------
		//paint row
		//-----------------------------------------------------------------
		while(rowiterator != end)
		{
			*rowiterator++ = col;
		}

		//-----------------------------------------------------------------
		//jump to beginning of next row
		//-----------------------------------------------------------------
		rowiterator += jump_dist;
	}
}
















void bitmapWindow::advanceToNextRow(int currentx)
{
	writeindex += windowContents->getWidth() - currentx;
}


void bitmapWindow::clear()
{
	erase(0);
}


void bitmapWindow::startDrawing()
{
	//erase(0);
	writeindex = windowContents->getSurface();
}

void bitmapWindow::finishDrawing()
{
	flipIntoView();
}

int bitmapWindow::getWidth() const
{
	return windowContents->getWidth();
}

int bitmapWindow::getHeight() const
{
	return windowContents->getHeight();
}



void bitmapWindow::drawPixel(const Vec2& pos, const Vec3& colour)
{
	setPixel(pos.x, pos.y, RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL));
}


void bitmapWindow::drawPixel(int xpos, int ypos, const Vec3& colour)
{
	setPixel(xpos, ypos, RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL));
}




void bitmapWindow::doDrawLine(const Vec2& startpos, const Vec2& endpos, const Vec3& colour)
{	
	drawLineInt(startpos.x, startpos.y, endpos.x, endpos.y, RGB(colour.x*MAX_UBYTE_VAL, colour.y*MAX_UBYTE_VAL, colour.z*MAX_UBYTE_VAL));
}


void bitmapWindow::drawText(const Vec2& pos, const std::string& text, const Vec3& colour)
{
	HDC windowDC = GetDC(windowHandle); // Get the DC for this window
	HDC dc = CreateCompatibleDC(windowDC); // Create a compatible one in memory

//	HDC dc;
	HBITMAP old_bitmap;

	// get the dc from surface
	old_bitmap = (HBITMAP)SelectObject(dc, windowContents->getBitmap());

	// set the colors for the text up
	SetTextColor(dc, RGB(colour.x*MAX_UBYTE_VAL,colour.y*MAX_UBYTE_VAL,colour.z*MAX_UBYTE_VAL));

	// set background mode to transparent so black isn't copied
	SetBkMode(dc, TRANSPARENT);

	//-----------------------------------------------------------------
	//draw text
	//-----------------------------------------------------------------
	TextOut(dc, pos.x, pos.y, text.c_str(), strlen(text.c_str()));

	//-----------------------------------------------------------------
	//restore old DC
	//-----------------------------------------------------------------
	SelectObject(dc, old_bitmap);

}


void bitmapWindow::drawRect(const Vec2& pos, int width, int height, const Vec3& colour)
{
	windowContents->drawRect(pos, width, height, colour);
}






















/*************************************************************************/
// the bitmapWindow class. This uses the above drawingSurface class to
// easily create a window that we can draw to directly.
/*************************************************************************/
/*class bitmapWindow {
  public:
    bitmapWindow(int x, int y, int width, int height, HINSTANCE currentInstance); // Constructor
    ~bitmapWindow(); // Destructor
    static int getNumberOfBitmapWindows(); // Returns static int below
    void setPixel(int x, int y, unsigned long color); // Set Pixel data in our pointer to the specified color
    void drawLine(int x1, int y1, int x2, int y2, unsigned long color); // Draw a line from x1,y1 to x2,y2 in the specified color
    void erase(unsigned long color); // Passes the erase request to the drawingSurface
    void flipIntoView(); // Copies window pixels from memory pointer to screen.

  protected:
    HWND windowHandle; // The handle for the window we'll pop up.
    void registerWindowClass(HINSTANCE currentInstance); // For registering the class of window we'll use
    static BOOL classIsRegistered; // Have we, or have we not, registered our window class?
    static int numberOfBitmapWindows; // The number of these classes in use
    int windowWidth, windowHeight; // Store the window's dimensions
    drawingSurface *windowContents; // easy DIB class defined above
};*/
// Initialize static vairables
BOOL bitmapWindow::classIsRegistered = 0;
int bitmapWindow::numberOfBitmapWindows = 0;



/*************************************************************************/
// Window Handler for our bitmapWindows.
/*************************************************************************/
LRESULT CALLBACK bitmapWindowHandler(HWND windowHandle, // Handle to the window this procedure is handling
                                     UINT message, // A message related to said window
                                     WPARAM wparam, // A parameter vairable
                                     LPARAM lparam) // Another
{ 
  switch(message) {
    case WM_QUIT: // Quit, if we're supposed to
    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      break;
  }
  // Take default action if not told to quit
  return DefWindowProc(windowHandle, message, wparam, lparam);
}




/*************************************************************************/
// constructor for bitmapWindow. Takes 5 parameters. An X coordinate for
// the window to appear, a Y coordinate for the window to appear, the
// width of the window, the height of the window, and the handle to this
// program's instance.
/*************************************************************************/
bitmapWindow::bitmapWindow(int x, int y, int width, int height, HINSTANCE currentInstance) 
{
	writeindex = 0;



  // We only need to register the window class once.
  if(!classIsRegistered) { registerWindowClass(currentInstance); }

  windowWidth = width + 7; // Store the width
  windowHeight = height + 25; // Store the height

  // Create a window
  windowHandle = CreateWindow(
    "Library_BMP_Window", // Name of the window class (registered above)
    "Window", // Name of the window, appears in the window title bar
    WS_BORDER | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU, // Window style
    x, // X coordinate of the window on-screen
    y, // Y coordinate of the window on-screen
    windowWidth, // width of the window
    windowHeight, // height of the window
    NULL, // Handle to a parent window (none)
    NULL, // Handle to a child window (none)
    currentInstance, // Handle to the current Instance
    0 // Pointer to extra data I don't care about
  );

  ShowWindow(windowHandle, SW_SHOW); // Show the window
  UpdateWindow(windowHandle); // Redundant, just in case

  windowContents = new drawingSurface(width, height); // Create the drawing surface, this class is defined above
  numberOfBitmapWindows++; // Keep track of the number of these classes
}


/*************************************************************************/
// Destructor, cleans up allocated memory and updates the number of
// these windows
/*************************************************************************/
bitmapWindow::~bitmapWindow() {
  DestroyWindow(windowHandle);
  numberOfBitmapWindows--;
}



/*************************************************************************/
// getNumberOfBitmapWindows, returns: the number of bitmap windows!
/*************************************************************************/
int bitmapWindow::getNumberOfBitmapWindows() {
  return numberOfBitmapWindows;
}


/*************************************************************************/
// Passes a request to change pixel data on to the drawing surface.
/*************************************************************************/
void bitmapWindow::setPixel(int x, int y, unsigned long color) {
  windowContents->setPixel(x, y, color);
}


/*************************************************************************/
// Passes a request to draw a line on to the drawing surface.
/*************************************************************************/
void bitmapWindow::drawLineInt(int x1, int y1, int x2, int y2, unsigned long color) {
  windowContents->drawLineInt(x1, y1, x2, y2, color);
}


/*************************************************************************/
// Passes a request to erase a line on to the drawingSurface.
/*************************************************************************/
void bitmapWindow::erase(unsigned long color) {
  windowContents->erase(color);
}



/*************************************************************************/
// Display's this windows drawing surface
/*************************************************************************/
void bitmapWindow::flipIntoView() {
  windowContents->display(0, 0, windowHandle);
}



/*************************************************************************/
// Registers the window class we use
/*************************************************************************/
void bitmapWindow::registerWindowClass(HINSTANCE currentInstance) {
  WNDCLASS windowClass;

  windowClass.style = CS_OWNDC; // The style of the window. CS_OWNDC means every window has it's own DC
  windowClass.lpfnWndProc = bitmapWindowHandler; // The function to call when this window receives a message
  windowClass.cbClsExtra = 0; // Extra bytes to allocate for this class (none)
  windowClass.cbWndExtra = 0; // Extra bytes to allocate for each window (none)
  windowClass.hInstance = currentInstance; // This application's instance
  windowClass.hIcon = LoadIcon(currentInstance, IDI_APPLICATION); // A standard Icon
  windowClass.hCursor = LoadCursor(currentInstance, IDC_ARROW); // A standard cursor
  windowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE; // A standard background
  windowClass.lpszMenuName = NULL; // No menus in this window
  windowClass.lpszClassName = "Library_BMP_Window"; // A name for this class

  RegisterClass(&windowClass); // Register the class
  classIsRegistered = 1; // Did we register the class? Yes, we did.
}

