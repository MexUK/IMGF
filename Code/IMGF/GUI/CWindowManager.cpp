#include "CWindowManager.h"
#include "bxgx.h"
#include "CGUIManager.h"
#include "Window/CIMGFWindow.h"
#include "Editors/CIMGEditor.h"

using namespace bxcf;

void					CWindowManager::init(void)
{
}

void					CWindowManager::uninit(void)
{
}

// window open/close
CWindow*				CWindowManager::openWindow(void)
{
	CPoint2D vecWindowPosition = CPoint2D((int32)150, 150);
	CSize2D vecWindowSize = CSize2D(1100, 652);

	CIMGFWindow *pWindow = bxgx::CGUIManager::getInstance()->addTemplatedWindow<CIMGFWindow>(vecWindowPosition, vecWindowSize);
	if (!pWindow)
	{
		return nullptr;
	}
	
	pWindow->init();

	return pWindow;
}

// window processing
void					CWindowManager::processWindows(void)
{
	bxgx::CGUIManager::getInstance()->processWindows();
}