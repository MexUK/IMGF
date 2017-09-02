#include <Windows.h>
#include "Globals.h"
#include "IMGF.h"

#include "GUI/Window/WindowManager.h"
#include "GUI/Windows/MainWindow.h"

using namespace imgf;

int WINAPI					WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR pCommandLine, int iCommandShow)
{
	g_pIMGF = new IMGF;
	g_pIMGF->init();
	g_pIMGF->openWindow();
	ShowWindow(g_pIMGF->getWindowManager()->getMainWindow()->getWindowHandle(), iCommandShow);
	g_pIMGF->process();
	g_pIMGF->uninit();
	return 0;
}