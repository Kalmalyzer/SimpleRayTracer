/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/

#include "simwin_framework.h"

#include "simplewin2d.h"

bitmapWindow* graphics = NULL;
HINSTANCE hinstance = NULL;
HWND windowhandle = NULL;

void frameworkInit();
void frameworkMain();
void frameworkShutdown();




//entry point to program
int WINAPI WinMain(HINSTANCE hinstance_, 
                      HINSTANCE hprevinstance, 
                      LPSTR lpcmdline, 
                      int ncmdshow)
{
	hinstance = hinstance_;


	//    bitmapWindow(int x, int y, int width, int height, HINSTANCE currentInstance); // Constructor

	frameworkInit();

	//-----------------------------------------------------------------
	//enter main program loop
	//-----------------------------------------------------------------
	MSG msg;     
	while(true)  // run forever - or until we manually break out of the loop!
	{
		if (PeekMessage(&msg, NULL,0,0,PM_REMOVE)) // check if a message awaits and remove 
                                             // it from the queue if there is one..
		{
			if(msg.message == WM_QUIT) 
				break; // exit loop if a quit message
             
            TranslateMessage(&msg); //Converts the message to a format used in the
                                     //event handler
             
            DispatchMessage(&msg); // THIS function sends the message to the event
                                    // handler
		}
           
     // Here you are free to do anything not related to messages - like the inner loop
     // of a game or something like that.
		frameworkMain();

     
   } // end while(TRUE)



	frameworkShutdown();

	return 0;

}




void win2dError(const std::string& errormessage)
{
	MessageBox(NULL, errormessage.c_str(), "Error", MB_OK);
	exit(666);
}


void win2dError(const std::string& errormessage, const std::string& boxtitle)
{
	MessageBox(NULL, errormessage.c_str(), boxtitle.c_str(), MB_OK);
	exit(666);
}



void frameworkInit()
{

	int width, height;
	getWindowDims(width, height);

	graphics = new bitmapWindow(30, 30, width, height, hinstance);

	windowhandle = graphics->getWindowHandle();


	doInit(hinstance, windowhandle, *graphics);
}

void frameworkMain()
{
	graphics->startDrawing();

	doMain(*graphics);

	graphics->finishDrawing();

}


void frameworkShutdown()
{
	doShutdown();

	delete graphics;
}


