/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __SIMWIN_FRAMEWORK_H__
#define __SIMWIN_FRAMEWORK_H__


#include <windows.h>
//class Graphics2d;
//#include "simplewin2d.h"
class bitmapWindow;

//-----------------------------------------------------------------
//funcs user must define
//-----------------------------------------------------------------

void getWindowDims(int& width, int& height);

void doInit(HINSTANCE hinstance, HWND windowhandle, bitmapWindow& graphics);
void doMain(bitmapWindow& graphics);
void doShutdown();


#endif //__SIMWIN_FRAMEWORK_H__