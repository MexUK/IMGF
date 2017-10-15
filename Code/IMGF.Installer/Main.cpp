#include "Main.h"
#include "Installer/Installer.h"
#include "BXGX.h"

int					WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bxgx::BXGX::get()->setShowWindowValue(nCmdShow);
	bxgx::BXGX::get()->init();

	Installer installer;
	installer.init();
	installer.openWindow();
	installer.process();

	return 0;
}