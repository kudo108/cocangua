//this 3 below lines for detect mem leak
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include <atlstr.h>
USING_NS_CC;

static bool isBackgroundMusicPlaying = false;

// uncomment below line, open debug console
//#define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
	_CrtDumpMemoryLeaks();//print out if mem leak
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(800, 600);
	//char* title = "Co Ca Ngua - CrazyTeam";
	CString strTest (_T("Co Ca Ngua - CrazyTeam"));
	SetWindowTextW(eglView->getHWnd(),(LPCWSTR) strTest );
    int ret = CCApplication::sharedApplication()->run();
	
#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
