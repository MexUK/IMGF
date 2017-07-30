#ifndef CGUIManager_H
#define CGUIManager_H

#include "bxgx.h"
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

class bxgx::CGUIManager : public bxcf::CManager, public bxcf::CSingleton<bxgx::CGUIManager>, public bxcf::CVectorPool<CWindow*>, public bxcf::CEventBinder
{
public:
	CGUIManager(void);

	void						init(void);
	void						uninit(void);

	void						bindEvents(void);

	void						unserialize(void);
	void						serialize(void);

	CWindow*					addWindow(bxcf::CPoint2D& vecWindowPosition = bxcf::CPoint2D((uint32) 0, (uint32) 0), bxcf::CSize2D& vecWindowSize = bxcf::CSize2D((uint32) 800, (uint32) 600));
	template <class WindowClass>
	WindowClass*				addTemplatedWindow(bxcf::CPoint2D& vecWindowPosition = bxcf::CPoint2D(0, 0), bxcf::CSize2D& vecWindowSize = bxcf::CSize2D(800, 600));

	void						processWindows(void);

	void						onMouseMove(bxcf::CPoint2D& vecCursorPosition);

	void						render(void);
	void						renderNow(void);
	void						checkToRender(void);

	CWindow*					getWindowByHwnd(HWND hWnd);

	static CGUIStyles*			createStyles(void);

	void						setGraphicsLibrary(CGraphicsLibrary* pGraphicsLibrary) { m_pGraphicsLibrary = pGraphicsLibrary; }
	CGraphicsLibrary*			getGraphicsLibrary(void) { return m_pGraphicsLibrary; }

	void						setActiveWindow(CWindow *pActiveWindow) { m_pActiveWindow = pActiveWindow; }
	CWindow*					getActiveWindow(void) { return m_pActiveWindow; }

	void						setCursorPosition(bxcf::CPoint2D vecCursorPosition) { m_vecCursorPosition = vecCursorPosition; }
	bxcf::CPoint2D&				getCursorPosition(void) { return m_vecCursorPosition; }

private:
	bool						createWindow(CWindow *pWindow);

private:
	CGraphicsLibrary*			m_pGraphicsLibrary;
	CWindow*					m_pActiveWindow;
	bxcf::CPoint2D				m_vecCursorPosition;
};

template <class WindowClass>
WindowClass*					bxgx::CGUIManager::addTemplatedWindow(bxcf::CPoint2D& vecWindowPosition, bxcf::CSize2D& vecWindowSize)
{
	WindowClass *pWindow = new WindowClass;
	pWindow->init();

	// check to position window at center of screen
	if (vecWindowPosition.m_x == -1 && vecWindowPosition.m_y == -1)
	{
		RECT rectScreenSize;
		GetWindowRect(GetDesktopWindow(), &rectScreenSize);
		bxcf::CSize2D vecScreenSize(rectScreenSize.right, rectScreenSize.bottom);

		vecWindowPosition = bxcf::CPoint2D((vecScreenSize.m_x / 2) - (vecWindowSize.m_x / 2), (vecScreenSize.m_y / 2) - (vecWindowSize.m_y / 2));
	}

	pWindow->setPosition(bxcf::CPoint2D(vecWindowPosition.m_x, vecWindowPosition.m_y)); // todo - send directly
	pWindow->setSize(vecWindowSize);
	addEntry(pWindow);

	if (!createWindow(pWindow))
	{
		return nullptr;
	}
	
	// remove title bar and border
	SetWindowLong(pWindow->getWindowHandle(), GWL_STYLE, 0);

	// show the window
	ShowWindow(pWindow->getWindowHandle(), SW_SHOW);

	// initial window draw
	render();

	return pWindow;
}

#endif