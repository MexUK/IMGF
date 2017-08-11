#include "CWindowManager.h"
#include "bxgx.h"
#include "CGUIManager.h"
#include "Window/CIMGFWindow.h"
#include "Editors/CIMGEditor.h"

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
CIMGFWindow*			CWindowManager::openWindow(void)
{
	m_pMainWindow = bxgx::get()->addWindow<CIMGFWindow>(-1, -1, 1100, 652);
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