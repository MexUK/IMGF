#include "CWindowManager.h"
#include "bxgx.h"
#include "BXGXManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "../../Compiler/Projects/IMGF/resource.h"
#include <string>

using namespace std;
using namespace bxcf;

CWindowManager::CWindowManager(void) :
	m_pMainWindow(nullptr)
{
}

// main interface
void					CWindowManager::init(void)
{
}

void					CWindowManager::uninit(void)
{
}

// window open/close
CMainWindow*			CWindowManager::openWindow(void)
{
	LPWSTR pIcon = MAKEINTRESOURCE(IDI_ICON1);
	uint32 uiIcon = (uint32) pIcon;

	m_pMainWindow = bxgx::get()->addWindow<CMainWindow>(-1, -1, 1100, 652, uiIcon);
	if (!m_pMainWindow)
	{
		return nullptr;
	}
	
	m_pMainWindow->init();

	return m_pMainWindow;
}

// window processing
void					CWindowManager::processWindows(void)
{
	bxgx::get()->processWindows();
}