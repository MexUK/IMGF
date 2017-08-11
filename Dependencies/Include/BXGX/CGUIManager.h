#ifndef CGUIManager_H
#define CGUIManager_H

#include "bxgx.h"
#include "Type/Vector/Vec2u.h"
#include "Object/CManager.h"
#include "Pool/CVectorPool.h"
#include "Window/CWindow.h"
#include "Event/CEventBinder.h"
#include "Object/CSingleton.h"
#include "Styles/CStyleManager.h"
#include "Event/EInputEvents.h"
#include <Commctrl.h>
#include <unordered_map>
#include <vector>
#include <tuple>

#include "Debug/CDebug.h"

LRESULT CALLBACK				WndProc_Window(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CGraphicsLibrary;
class CGUIStyles;
class CGUIEventUtilizer;
class CGUIItem;

class bxgx::CGUIManager : public bxcf::CManager, public bxcf::CSingleton<bxgx::CGUIManager>, public bxcf::CVectorPool<CWindow*>, public bxcf::CEventBinder
{
public:
	CGUIManager(void);

	void						init(void);
	void						uninit(void);

	void						bindEvents(void);

	void						unserialize(void);
	void						serialize(void);

	CWindow*					addWindow(bxcf::Vec2i& vecWindowPosition = bxcf::Vec2i((uint32)-1, (uint32)-1), bxcf::Vec2u& vecWindowSize = bxcf::Vec2u((uint32)800, (uint32)600));
	CWindow*					addWindow(uint32 x = -1, uint32 y = -1, uint32 w = 800, uint32 h = 600);
	template <class WindowClass>
	WindowClass*				addWindow(bxcf::Vec2i& vecWindowPosition = bxcf::Vec2i(-1, -1), bxcf::Vec2u& vecWindowSize = bxcf::Vec2u(800, 600));
	template <class WindowClass>
	WindowClass*				addWindow(uint32 x = -1, uint32 y = -1, uint32 w = 800, uint32 h = 600);

	void						processWindows(void);

	template <typename ...Args>
	void						triggerEvent(uint32 uiEvent, bxcf::Vec2i& vecCursorPoint, Args... args);
	template <typename ...Args>
	inline bool					triggerItemEvent(uint32 uiEvent, CGUIEventUtilizer *pItem, Args... args);

	inline bool					isWindowEvent(uint32 uiEvent);
	inline bool					isMouseEvent(uint32 uiEvent);
	inline bool					isKeyEvent(uint32 uiEvent);
	inline bool					isRenderEvent(uint32 uiEvent);

	void						onMouseMove(bxcf::Vec2i& vecCursorPosition);

	void						render(void);
	void						renderNow(void);
	void						checkToRender(void);

	CWindow*					getWindowByHwnd(HWND hWnd);

	static CGUIStyles*			createStyles(void);

	void						setGraphicsLibrary(CGraphicsLibrary* pGraphicsLibrary) { m_pGraphicsLibrary = pGraphicsLibrary; }
	CGraphicsLibrary*			getGraphicsLibrary(void) { return m_pGraphicsLibrary; }

	void						setActiveWindow(CWindow *pActiveWindow) { m_pActiveWindow = pActiveWindow; }
	CWindow*					getActiveWindow(void) { return m_pActiveWindow; }

	void						setCursorPosition(bxcf::Vec2i vecCursorPosition) { m_vecCursorPosition = vecCursorPosition; }
	bxcf::Vec2i&				getCursorPosition(void) { return m_vecCursorPosition; }

private:
	bool						createWindow(CWindow *pWindow);

private:
	CGraphicsLibrary*								m_pGraphicsLibrary;
	CWindow*										m_pActiveWindow;
	bxcf::Vec2i									m_vecCursorPosition;
	CGUIItem*										m_pItemMouseIsOver;

public:
	std::unordered_map<uint32, std::vector<CGUIEventUtilizer*>>	m_umapEventControls;
};

template <class WindowClass>
WindowClass*					bxgx::CGUIManager::addWindow(uint32 x, uint32 y, uint32 w, uint32 h)
{
	return addWindow<WindowClass>(Vec2i(x, y), Vec2u(w, h));
}

template <class WindowClass>
WindowClass*					bxgx::CGUIManager::addWindow(bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize)
{
	WindowClass *pWindow = new WindowClass;

	// check to position window at center of screen
	if (vecWindowPosition.x == -1 && vecWindowPosition.y == -1)
	{
		RECT rectScreenSize;
		GetWindowRect(GetDesktopWindow(), &rectScreenSize);
		bxcf::Vec2u vecScreenSize(rectScreenSize.right, rectScreenSize.bottom);

		vecWindowPosition = bxcf::Vec2i((vecScreenSize.x / 2) - (vecWindowSize.x / 2), (vecScreenSize.y / 2) - (vecWindowSize.y / 2));
	}

	pWindow->setPosition(bxcf::Vec2i(vecWindowPosition.x, vecWindowPosition.y)); // todo - send directly
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
void						bxgx::CGUIManager::triggerEvent(uint32 uiEvent, bxcf::Vec2i& vecCursorPoint, Args... args)
{
	if (m_umapEventControls.find(uiEvent) == m_umapEventControls.end())
	{
		return;
	}

	bool
		bIsMouseEvent = isMouseEvent(uiEvent),
		bIsKeyEvent = isKeyEvent(uiEvent),
		bIsRenderEvent = isRenderEvent(uiEvent),
		bIsWindowEvent = isWindowEvent(uiEvent),
		bTriggerEventForControl,
		bTriggerEvents = true;
	CStyleManager
		*pStyleManager = CStyleManager::get();

	auto umapEventControls = m_umapEventControls;

	for (CGUIEventUtilizer *pGUIEventUtilizer : umapEventControls[uiEvent])
	{
		if (bIsMouseEvent)
		{
			bTriggerEventForControl = pGUIEventUtilizer->isPointInItem(vecCursorPoint);
			if (bTriggerEventForControl)
			{
				if (uiEvent == MOUSE_LEFT_UP)
				{
					if (pGUIEventUtilizer->getItemType() == bxgx::item::CONTROL)
					{
						CGUIControl *pControl = (CGUIControl*)pGUIEventUtilizer;
						pControl->setActiveItem();
						pControl->markToRedraw();

						if (pControl->getControlType() == GUI_CONTROL_BUTTON)
						{
							bxcf::Events::trigger(bxgx::control::events::PRESS_BUTTON, (CButtonControl*)pControl);
						}
					}
				}
				else if (uiEvent == MOUSE_MOVE)
				{
					if (pGUIEventUtilizer != m_pItemMouseIsOver)
					{
						if (m_pItemMouseIsOver)
						{
							triggerItemEvent(MOUSE_EXIT, m_pItemMouseIsOver);
							bxcf::Events::trigger(bxgx::control::events::MOUSE_EXIT_ITEM, m_pItemMouseIsOver);
						}

						CGUIItem *pGUIItem = (CGUIItem*)pGUIEventUtilizer;
						m_pItemMouseIsOver = pGUIItem;

						if (pGUIItem->getItemType() == bxgx::item::CONTROL || pGUIItem->getItemType() == bxgx::item::SHAPE)
						{
							triggerItemEvent(MOUSE_ENTER, pGUIItem);
							bxcf::Events::trigger(bxgx::control::events::MOUSE_ENTER_ITEM, pGUIItem);
						}
					}
				}
			}
		}
		else if (bIsKeyEvent)
		{
			bTriggerEventForControl = pGUIEventUtilizer->doesItemHaveFocus();
		}
		else
		{
			bTriggerEventForControl = true;
		}

		if (bTriggerEvents && bTriggerEventForControl)
		{
			pStyleManager->m_pRenderingEventUtilizer = pGUIEventUtilizer;
			pStyleManager->m_vecRenderingStyleGroups = pGUIEventUtilizer->getStyleGroups();
			pStyleManager->m_uiRenderingItemType = pGUIEventUtilizer->getItemType();
			pStyleManager->m_uiRenderingItemSubType = pGUIEventUtilizer->getItemSubType();
			pStyleManager->m_uiRenderingControlComponent = bxgx::controls::components::DEFAULT_CONTROL_COMPONENT;
			pStyleManager->m_uiRenderingStyleStatus = bxgx::styles::statuses::DEFAULT_STATUS;
			pStyleManager->m_uiRenderingStyleFragment = bxgx::styles::fragments::ALL_STYLE_FRAGMENTS;

			if (bIsRenderEvent)
			{
				triggerItemEvent(uiEvent, pGUIEventUtilizer, args...);
			}
			else if (triggerItemEvent(uiEvent, pGUIEventUtilizer, args...))
			{
				bTriggerEvents = false;
			}
		}
	}
}

template <typename ...Args>
bool						bxgx::CGUIManager::triggerItemEvent(uint32 uiEvent, CGUIEventUtilizer *pItem, Args... args)
{
	bool bResult = false;

	va_list list;
	va_start(list, pItem);

	switch (uiEvent)
	{
		// window
	case WINDOW_GAIN_FOCUS:			bResult = pItem->onGainFocus();											break;
	case WINDOW_LOSE_FOCUS:			bResult = pItem->onLoseFocus();											break;

		// mouse
	case MOUSE_MOVE:				bResult = pItem->onMouseMove(va_arg(list, bxcf::Vec2i));				break;
	
	case MOUSE_LEFT_DOWN:			bResult = pItem->onLeftMouseDown(va_arg(list, bxcf::Vec2i));			break;
	case MOUSE_LEFT_UP:				bResult = pItem->onLeftMouseUp(va_arg(list, bxcf::Vec2i));			break;
	case MOUSE_DOUBLE_LEFT_DOWN:	bResult = pItem->onDoubleLeftMouseDown(va_arg(list, bxcf::Vec2i));	break;
	case MOUSE_DOUBLE_LEFT_UP:		bResult = pItem->onDoubleLeftMouseUp(va_arg(list, bxcf::Vec2i));		break;
	
	case MOUSE_RIGHT_DOWN:			bResult = pItem->onRightMouseDown(va_arg(list, bxcf::Vec2i));		break;
	case MOUSE_RIGHT_UP:			bResult = pItem->onRightMouseUp(va_arg(list, bxcf::Vec2i));			break;
	case MOUSE_DOUBLE_RIGHT_DOWN:	bResult = pItem->onDoubleRightMouseDown(va_arg(list, bxcf::Vec2i));	break;
	case MOUSE_DOUBLE_RIGHT_UP:		bResult = pItem->onDoubleRightMouseUp(va_arg(list, bxcf::Vec2i));	break;

	case MOUSE_WHEEL_MOVE:			bResult = pItem->onMouseWheelMove(va_arg(list, bxcf::Vec2i));		break;
	case MOUSE_WHEEL_DOWN:			bResult = pItem->onMouseWheelDown(va_arg(list, bxcf::Vec2i));		break;
	case MOUSE_WHEEL_UP:			bResult = pItem->onMouseWheelUp(va_arg(list, bxcf::Vec2i));			break;
	case MOUSE_DOUBLE_WHEEL_DOWN:	bResult = pItem->onDoubleMouseWheelDown(va_arg(list, bxcf::Vec2i));	break;
	case MOUSE_DOUBLE_WHEEL_UP:		bResult = pItem->onDoubleMouseWheelUp(va_arg(list, bxcf::Vec2i));	break;

	case MOUSE_ENTER:				bResult = pItem->onMouseEnter();										break;
	case MOUSE_EXIT:				bResult = pItem->onMouseExit();											break;

		// key
	case KEY_DOWN:					bResult = pItem->onKeyDown(va_arg(list, uint16));						break;
	case KEY_UP:					bResult = pItem->onKeyUp(va_arg(list, uint16));							break;
	case KEY_HELD:					bResult = pItem->onKeyHeld(va_arg(list, uint16));						break;
	case KEY_DOUBLE_DOWN:			bResult = pItem->onDoubleKeyDown(va_arg(list, uint16));					break;
	case KEY_DOUBLE_UP:				bResult = pItem->onDoubleKeyUp(va_arg(list, uint16));					break;

		// render
	case RENDER:					pItem->onRender();														break;
	case RENDER_BEFORE:				pItem->onRenderBefore();												break;
	case RENDER_AFTER:				pItem->onRenderAfter();													break;
	}

	va_end(list);

	return bResult;
}

inline bxgx::CGUIManager*		bxgx::get(void) { return bxgx::CGUIManager::get(); }

#endif