#include "CWindowManager.h"
#include "gui.h"
#include "CGUIManager.h"
#include "Window/CIMGFWindow.h"
#include "Editors/CIMGEditor.h"

using namespace mcore;

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
	CSize2D vecWindowSize = CSize2D(1025, 698);
	CIMGFWindow *pWindow = gui::CGUIManager::getInstance()->addTemplatedWindow<CIMGFWindow>(vecWindowPosition, vecWindowSize);
	
	CIMGEditor *pIMGEditor = new CIMGEditor; // CIMGEditor eventually extends CGUILayer - todo use pWindow->addTempatedGroup<CIMGEditor>() instead?
	pIMGEditor->setWindow(pWindow);
	pWindow->addEntry(pIMGEditor);
	
	pWindow->initTabs();
	pWindow->bindAllEvents();
	
	return pWindow;
}

// window processing
void					CWindowManager::processWindows(void)
{
	gui::CGUIManager::getInstance()->processWindows();
}