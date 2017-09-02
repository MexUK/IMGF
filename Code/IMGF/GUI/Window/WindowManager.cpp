#include "WindowManager.h"
#include "nsbxgx.h"
#include "BXGX.h"
#include "GUI/Windows/MainWindow.h"
#include "GUI/Editors/IMGEditor.h"
#include "../../Compiler/Projects/IMGF/resource.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace imgf;

WindowManager::WindowManager(void) :
	m_pMainWindow(nullptr)
{
}

// main interface
void					WindowManager::init(void)
{
}

void					WindowManager::uninit(void)
{
}

// window open/close
MainWindow*			WindowManager::openWindow(void)
{
	LPWSTR pIcon = MAKEINTRESOURCE(IDI_ICON1);
	uint32 uiIcon = (uint32) pIcon;

	m_pMainWindow = bxgx::get()->addWindow<MainWindow>(-1, -1, 1100, 652, uiIcon);
	if (!m_pMainWindow)
	{
		return nullptr;
	}
	
	m_pMainWindow->init();

	return m_pMainWindow;
}

// window processing
void					WindowManager::process(void)
{
	bxgx::get()->process();
}