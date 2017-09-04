#pragma once

#include "bxgx.h"
#include "Type/Vector/Vec2u.h"
#include "Object/CManager.h"
#include "Pool/CVectorPool.h"
#include "Window/CWindow.h"
#include "Object/CSingleton.h"
#include "Styles/CStyleManager.h"
#include "Event/EInputEvents.h"
#include "Event/EInternalEvent.h"
#include "Controls/CScrollControl.h"
#include "Static/CDebug.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <thread>
#include <Windows.h> // for HCURSOR

#define BXGX_THREAD 0
#define IMGF_THREAD 1

class CGraphicsLibrary;
class CGUIStyles;
class CRenderable;
class CGUIItem;
class CButtonControl;

class bxgx::BXGXManager : public bxcf::CManager, public bxcf::CSingleton<bxgx::BXGXManager>, public bxcf::CVectorPool<CWindow*>
{
public:
	BXGXManager(void);

	void						init(void);
	void						uninit(void);

	void						bindEvents(void);

	void						unserialize(void);
	void						serialize(void);

	LRESULT						WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void						processBXGX(void);

	void						setCursorPosition(bxcf::Vec2i vecCursorPosition) { m_vecCursorPosition = vecCursorPosition; }
	bxcf::Vec2i&				getCursorPosition(void) { return m_vecCursorPosition; }

	void						setPreviousCursorPosition(bxcf::Vec2i vecPreviousCursorPosition) { m_vecPreviousCursorPosition = vecPreviousCursorPosition; }
	bxcf::Vec2i&				getPreviousCursorPosition(void) { return m_vecPreviousCursorPosition; }

	void						setCursorScreenPosition(bxcf::Vec2i vecCursorScreenPosition) { m_vecCursorScreenPosition = vecCursorScreenPosition; }
	bxcf::Vec2i&				getCursorScreenPosition(void) { return m_vecCursorScreenPosition; }

	void						setCursorMoveDifference(bxcf::Vec2i& vecCursorMoveDifference) { m_vecCursorMoveDifference = vecCursorMoveDifference; }
	bxcf::Vec2i&				getCursorMoveDifference(void) { return m_vecCursorMoveDifference; }

	std::thread&				getBXGXThread(void) { return m_tBXGXThread; }

	void						setThread1Locked(bool bThread1Locked) { m_bThread1Locked = bThread1Locked; }
	bool						isThread1Locked(void) { return m_bThread1Locked; }

	void						setThread2Locked(bool bThread2Locked) { m_bThread2Locked = bThread2Locked; }
	bool						isThread2Locked(void) { return m_bThread2Locked; }

	void						setDefaultCursor(char *pCursorIcon);
	void						setDefaultCursor(HCURSOR hDefaultCursor) { m_hDefaultCursor = hDefaultCursor; }
	HCURSOR						getDefaultCursor(void) { return m_hDefaultCursor; }
	void						applyDefaultCursor(void);

	bool						applyCursor(void);
	void						applyCursor(char *pCursorIcon);

	CWindow*					addWindow(bxcf::Vec2i& vecWindowPosition = bxcf::Vec2i((uint32)-1, (uint32)-1), bxcf::Vec2u& vecWindowSize = bxcf::Vec2u((uint32)800, (uint32)600), uint32 uiIcon = -1);
	CWindow*					addWindow(uint32 x = -1, uint32 y = -1, uint32 w = 800, uint32 h = 600, uint32 uiIcon = -1);
	template <class WindowClass>
	WindowClass*				addWindow(bxcf::Vec2i& vecWindowPosition = bxcf::Vec2i(-1, -1), bxcf::Vec2u& vecWindowSize = bxcf::Vec2u(800, 600), uint32 uiIcon = -1);
	template <class WindowClass>
	WindowClass*				addWindow(uint32 x = -1, uint32 y = -1, uint32 w = 800, uint32 h = 600, uint32 uiIcon = -1);

	void						processWindows(void);

	void						triggerEvent(bxgx::events::EInternalEvent uiEvent, bxcf::Vec2i& vecCursorPoint, ...);
	bool						triggerItemEvent(bxgx::events::EInternalEvent uiEvent, CRenderable *pItem, ...);
	bool						triggerItemEvent(bxgx::events::EInternalEvent uiEvent, CRenderable *pItem, va_list args);

	inline bool					isWindowEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isMouseEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isKeyEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isRenderEvent(bxgx::events::EInternalEvent uiEvent);

	void						onMouseMove(bxcf::Vec2i& vecCursorPosition);

	void						render(void);
	void						renderNow(void);

	CWindow*					getWindowByHwnd(HWND hWnd);

	static CGUIStyles*			createStyles(void);

	void						setGraphicsLibrary(CGraphicsLibrary* pGraphicsLibrary) { m_pGraphicsLibrary = pGraphicsLibrary; }
	CGraphicsLibrary*			getGraphicsLibrary(void) { return m_pGraphicsLibrary; }

	void						setActiveWindow(CWindow *pActiveWindow) { m_pActiveWindow = pActiveWindow; }
	CWindow*					getActiveWindow(void) { return m_pActiveWindow; }

	void						setItemMouseIsOver(CGUIItem* pItemMouseIsOver) { m_pItemMouseIsOver = pItemMouseIsOver; }
	CGUIItem*					getItemMouseIsOver(void) { return m_pItemMouseIsOver; }
	bool						isMouseOverItem(void) { return m_pItemMouseIsOver != nullptr; }
	void						clearItemMouseIsOver(void) { m_pItemMouseIsOver = nullptr; }

	CGUIItem*					getControlOrShapeFromPoint(bxcf::Vec2i& vecPoint);

	bool						createWindow(CWindow *pWindow, uint32 uiIcon = -1);

	void						markMainThreadToUpdateWindow(void) { m_bMainThreadIsMarkedToUpdateWindow = true; }
	void						unmarkMainThreadToUpdateWindow(void) { m_bMainThreadIsMarkedToUpdateWindow = false; }
	bool						isMainThreadMarkedToUpdateWindow(void) { return m_bMainThreadIsMarkedToUpdateWindow; }

private:
	bxcf::Vec2i										m_vecCursorPosition;
	bxcf::Vec2i										m_vecPreviousCursorPosition;
	bxcf::Vec2i										m_vecCursorScreenPosition;
	bxcf::Vec2i										m_vecCursorMoveDifference;
	std::thread										m_tBXGXThread;
	HANDLE											m_tAppThread;
	bool											m_bThread1Locked;
	bool											m_bThread2Locked;
	bool											m_bMainThreadIsMarkedToUpdateWindow;
	CGraphicsLibrary*								m_pGraphicsLibrary;
	CWindow*										m_pActiveWindow;
	CGUIItem*										m_pItemMouseIsOver;
	HCURSOR											m_hDefaultCursor;
	std::vector<CButtonControl*>					m_vecButtonsPressed;
	std::vector<CButtonControl*>					m_vecButtonsPressedPending;

public:
	std::unordered_map<uint32, std::vector<CRenderable*>>	m_umapEventControls;
};

template <class WindowClass>
WindowClass*					bxgx::BXGXManager::addWindow(uint32 x, uint32 y, uint32 w, uint32 h, uint32 uiIcon)
{
	return addWindow<WindowClass>(Vec2i(x, y), Vec2u(w, h), uiIcon);
}

template <class WindowClass>
WindowClass*					bxgx::BXGXManager::addWindow(bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize, uint32 uiIcon)
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

	if (!createWindow(pWindow, uiIcon))
	{
		return nullptr;
	}

	// remove title bar and border
	SetWindowLong(pWindow->getWindowHandle(), GWL_STYLE, 0);

	// show the window
	ShowWindow(pWindow->getWindowHandle(), SW_SHOW);

	// initial window draw
	pWindow->render();
	pWindow->triggerPaint(); // todo - shouldn't be here

	return pWindow;
}

inline bxgx::BXGXManager*		bxgx::get(void) { return bxgx::BXGXManager::get(); }