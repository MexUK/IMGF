#include <Windows.h>
#include "Globals.h"
#include "IMGF.h"
#include "BXGX.h"

#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

using namespace imgf;

int WINAPI					WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR pCommandLine, int iCommandShow)
{
	g_pIMGF = new IMGF;
	bxgx::BXGX::get()->setShowWindowValue(iCommandShow);
	g_pIMGF->init();
	g_pIMGF->openWindow();
	g_pIMGF->process();
	g_pIMGF->uninit();
	return 0;
}