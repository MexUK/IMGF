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
#include <tuple>

#include "Debug/CDebug.h"

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

	template <typename ...Args>
	void						triggerEvent(uint32 uiEvent, bxcf::CPoint2D& vecCursorPoint, Args... args);
	template <class T, typename ...Args>
	inline bool					triggerItemEvent(uint32 uiEvent, T *pItem, Args... args);

	inline bool					isWindowEvent(uint32 uiEvent);
	inline bool					isMouseEvent(uint32 uiEvent);
	inline bool					isKeyEvent(uint32 uiEvent);
	inline bool					isRenderEvent(uint32 uiEvent);

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

template <typename ...Args>
void						bxgx::CGUIManager::triggerEvent(uint32 uiEvent, bxcf::CPoint2D& vecCursorPoint, Args... args)
{
	bool
		bIsMouseEvent = isMouseEvent(uiEvent),
		bIsKeyEvent = isKeyEvent(uiEvent),
		bIsRenderEvent = isRenderEvent(uiEvent),
		bIsWindowEvent = isWindowEvent(uiEvent);
	for (CWindow *pWindow : getEntries())
	{
		for (CGUILayer *pLayer : pWindow->getEntries())
		{
			if (triggerItemEvent<CGUILayer>(uiEvent, pLayer, args...))
			{
				return;
			}
			for (CGUIShape *pShape : pLayer->getShapes().getEntries())
			{
				if (pShape->isEventUsageMarked(uiEvent))
				{
					if ((bIsMouseEvent && pShape->isPointInItem(vecCursorPoint)) || bIsRenderEvent)
					{
						if (triggerItemEvent<CGUIShape>(uiEvent, pShape, args...))
						{
							return;
						}
					}
				}
			}
			uint32 uiStartTickCount = GetTickCount();
			for (CGUIControl *pControl : pLayer->m_vecControls.getEntries()) // <--- this line causes huge lag
			{
				if (pControl->isEventUsageMarked(uiEvent))
				{
					if ((bIsMouseEvent && pControl->isPointInItem(vecCursorPoint)) || (bIsKeyEvent && pControl->doesControlHaveFocus()) || bIsRenderEvent)
					{
						if (triggerItemEvent<CGUIControl>(uiEvent, pControl, args...))
						{
							return;
						}
					}
				}
			}
			bxcf::CDebug::log("Milliseconds: " + CString2::toString(GetTickCount() - uiStartTickCount));
		}
		
		if (bIsWindowEvent)
		{
			if (triggerItemEvent<CWindow>(uiEvent, pWindow, args...))
			{
				return;
			}
		}
	}
}

template <class T, typename ...Args>
bool						bxgx::CGUIManager::triggerItemEvent(uint32 uiEvent, T *pItem, Args... args)
{
	bool bResult = false;

	va_list list;
	va_start(list, pItem);

	switch (uiEvent)
	{
		// window
	case WINDOW_GAIN_FOCUS:		bResult = pItem->onGainFocus();										break;
	case WINDOW_LOSE_FOCUS:		bResult = pItem->onLoseFocus();										break;

		// mouse
	case MOUSE_MOVE:			bResult = pItem->onMouseMove(va_arg(list, bxcf::CPoint2D));			break;
	case MOUSE_LEFT_DOWN:		bResult = pItem->onLeftMouseDown(va_arg(list, bxcf::CPoint2D));		break;
	case MOUSE_LEFT_UP:			bResult = pItem->onLeftMouseUp(va_arg(list, bxcf::CPoint2D));		break;
	case MOUSE_RIGHT_DOWN:		bResult = pItem->onRightMouseDown(va_arg(list, bxcf::CPoint2D));	break;
	case MOUSE_RIGHT_UP:		bResult = pItem->onRightMouseUp(va_arg(list, bxcf::CPoint2D));		break;

		// key
	case KEY_DOWN:				bResult = pItem->onKeyDown(va_arg(list, uint16));					break;
	case KEY_UP:				bResult = pItem->onKeyUp(va_arg(list, uint16));						break;
	case KEY_HELD:				bResult = pItem->onKeyHeld(va_arg(list, uint16));					break;

		// render
	case RENDER:				bResult = pItem->onRender();										break;
	case RENDER_BEFORE:			bResult = pItem->onRenderBefore();									break;
	case RENDER_AFTER:			bResult = pItem->onRenderAfter();									break;
	}

	va_end(list);

	return bResult;
}

#endif