#include <Windows.h>
#include "Globals.h"
#include "CIMGF.h"

int WINAPI					WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR pCommandLine, int iCommandShow)
{
	g_pIMGF = new CIMGF;
	g_pIMGF->init();
	g_pIMGF->openWindow();
	g_pIMGF->processWindows();
	g_pIMGF->uninit();
	return 0;
}