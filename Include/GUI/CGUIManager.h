#ifndef CGUIManager_H
#define CGUIManager_H

#include "bxa.h"
#include "gui.h"
#include "Type/Vector/CSize2D.h"
#include "Object/CManager.h"
#include "Pool/CVectorPool.h"
#include "Window/CWindow.h"
#include "Event/CEventBinder.h"
#include "Object/CSingleton.h"
#include <Commctrl.h>

LRESULT CALLBACK				WndProc_Window(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CGraphicsLibrary;
class CGUIStyles;

class gui::CGUIManager : public bxa::CManager, public bxa::CSingleton<gui::CGUIManager>, public bxa::CVectorPool<CWindow*>, public bxa::CEventBinder
{
public:
	CGUIManager(void);

	void						init(void);
	void						uninit(void);

	void						bindEvents(void);

	void						unserialize(void);
	void						serialize(void);

	CWindow*					addWindow(bxa::CPoint2D& vecWindowPosition = bxa::CPoint2D((uint32) 0, (uint32) 0), bxa::CSize2D& vecWindowSize = bxa::CSize2D((uint32) 800, (uint32) 600));
	template <class WindowClass>
	WindowClass*				addTemplatedWindow(bxa::CPoint2D& vecWindowPosition = bxa::CPoint2D(0, 0), bxa::CSize2D& vecWindowSize = bxa::CSize2D(800, 600));

	void						processWindows(void);

	void						onMouseMove(bxa::CPoint2D& vecCursorPosition);

	void						render(void);

	CWindow*					getWindowByHwnd(HWND hWnd);

	static CGUIStyles*			createStyles(void);

	void						setGraphicsLibrary(CGraphicsLibrary* pGraphicsLibrary) { m_pGraphicsLibrary = pGraphicsLibrary; }
	CGraphicsLibrary*			getGraphicsLibrary(void) { return m_pGraphicsLibrary; }

	void						setActiveWindow(CWindow *pActiveWindow) { m_pActiveWindow = pActiveWindow; }
	CWindow*					getActiveWindow(void) { return m_pActiveWindow; }

private:
	bool						createWindow(CWindow *pWindow);

private:
	CGraphicsLibrary*			m_pGraphicsLibrary;
	CWindow*					m_pActiveWindow;
};

template <class WindowClass>
WindowClass*					gui::CGUIManager::addTemplatedWindow(bxa::CPoint2D& vecWindowPosition, bxa::CSize2D& vecWindowSize)
{
	WindowClass *pWindow = new WindowClass;
	pWindow->setPosition(bxa::CPoint2D(vecWindowPosition.m_x, vecWindowPosition.m_y)); // todo - send directly
	pWindow->setSize(vecWindowSize);
	pWindow->setTitleBarHeight(25);
	if (!createWindow(pWindow))
	{
		return nullptr;
	}
	addEntry(pWindow);
	return pWindow;
}

#endif