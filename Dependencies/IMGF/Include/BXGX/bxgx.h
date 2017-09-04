#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2u.h"
#include "Object/Manager.h"
#include "Pool/VectorPool.h"
#include "Window/Window.h"
#include "Object/Singleton.h"
#include "Style/StyleManager.h"
#include "Event/EInputEvent.h"
#include "Event/EInternalEvent.h"
#include "Control/Controls/ScrollBar.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <thread>
#include <Windows.h> // for HCURSOR

extern std::mutex mutexRenderItemEvents;

class bxgx::GraphicsLibrary;
class bxgx::RenderItem;
class bxgx::LayerItem;
class bxgx::Button;
class bxgx::MenuItem;
class bxgx::ScrollBar;

class bxgx::BXGX : public bxcf::Manager, public bxcf::Singleton<bxgx::BXGX>, public bxcf::VectorPool<Window*>
{
public:
	BXGX(void);

	void						init(void);
	void						uninit(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						unserialize(void);
	void						serialize(void);

	void						process(void); // main thread
	void						process2ndThread(void); // 2nd thread

	LRESULT						WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // main thread

	void						setCursorPosition(bxcf::Vec2i vecCursorPosition) { m_vecCursorPosition = vecCursorPosition; }
	bxcf::Vec2i&				getCursorPosition(void) { return m_vecCursorPosition; }

	void						setPreviousCursorPosition(bxcf::Vec2i vecPreviousCursorPosition) { m_vecPreviousCursorPosition = vecPreviousCursorPosition; }
	bxcf::Vec2i&				getPreviousCursorPosition(void) { return m_vecPreviousCursorPosition; }

	void						setCursorScreenPosition(bxcf::Vec2i vecCursorScreenPosition) { m_vecCursorScreenPosition = vecCursorScreenPosition; }
	bxcf::Vec2i&				getCursorScreenPosition(void) { return m_vecCursorScreenPosition; }

	void						setCursorMoveDifference(bxcf::Vec2i& vecCursorMoveDifference) { m_vecCursorMoveDifference = vecCursorMoveDifference; }
	bxcf::Vec2i&				getCursorMoveDifference(void) { return m_vecCursorMoveDifference; }

	std::thread&				get2ndThread(void) { return m_t2ndThread; }

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

	Window*					addWindow(bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize, uint32 uiIcon = -1);
	Window*					addWindow(int32 x, int32 y, uint32 w, uint32 h, uint32 uiIcon = -1);
	Window*					addWindow(uint32 w = 800, uint32 h = 600, uint32 uiIcon = -1);
	template <class WindowClass>
	WindowClass*				addWindow(bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize, uint32 uiIcon = -1);
	template <class WindowClass>
	WindowClass*				addWindow(int32 x, int32 y, uint32 w, uint32 h, uint32 uiIcon = -1);
	template <class WindowClass>
	WindowClass*				addWindow(uint32 w, uint32 h, uint32 uiIcon = -1);

	void						triggerEvent(bxgx::events::EInternalEvent uiEvent, bxcf::Vec2i vecCursorPoint, ...);
	bool						triggerItemEventVA(bxgx::events::EInternalEvent uiEvent, RenderItem *pItem, ...);
	bool						triggerItemEvent(bxgx::events::EInternalEvent uiEvent, RenderItem *pItem, va_list args);

	inline bool					isWindowEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isMouseEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isKeyEvent(bxgx::events::EInternalEvent uiEvent);
	inline bool					isRenderEvent(bxgx::events::EInternalEvent uiEvent);

	void						onMouseMove(bxcf::Vec2i& vecCursorPosition);

	void						render(void);
	void						renderNow(void);

	Window*					getWindowByHwnd(HWND hWnd);

	void						setGraphicsLibrary(GraphicsLibrary* pGraphicsLibrary) { m_pGraphicsLibrary = pGraphicsLibrary; }
	GraphicsLibrary*			getGraphicsLibrary(void) { return m_pGraphicsLibrary; }

	void						setActiveWindow(Window *pActiveWindow) { m_pActiveWindow = pActiveWindow; }
	Window*					getActiveWindow(void) { return m_pActiveWindow; }

	void						setRenderItemMouseIsOver(RenderItem* pItemMouseIsOver) { m_pRenderItemMouseIsOver = pItemMouseIsOver; }
	RenderItem*				getRenderItemMouseIsOver(void) { return m_pRenderItemMouseIsOver; }
	bool						isMouseOverItem(void) { return m_pRenderItemMouseIsOver != nullptr; }
	void						clearItemMouseIsOver(void) { m_pRenderItemMouseIsOver = nullptr; }

	RenderItem*				getRenderItemFromPoint(bxcf::Vec2i& vecPoint);
	LayerItem*					getControlOrShapeFromPoint(bxcf::Vec2i& vecPoint);
	Layer*						getLayerFromPoint(bxcf::Vec2i& vecPoint);
	Window*					getWindowFromPoint(bxcf::Vec2i& vecScreenPoint);

	bool						createWindow(Window *pWindow, uint32 uiIcon = -1);

	void						markMainThreadToUpdateWindow(void) { m_bMainThreadIsMarkedToUpdateWindow = true; }
	void						unmarkMainThreadToUpdateWindow(void) { m_bMainThreadIsMarkedToUpdateWindow = false; }
	bool						isMainThreadMarkedToUpdateWindow(void) { return m_bMainThreadIsMarkedToUpdateWindow; }

	std::vector<Button*>&		getButtonsPressedPending(void) { return m_vecButtonsPressedPending; }
	std::vector<MenuItem*>&	getMenuItemsPressed(void) { return m_vecMenuItemsPressed; }

	void						setActiveScrollBar(ScrollBar *pScrollBar) { m_pActiveScrollBar = pScrollBar; }
	ScrollBar*					getActiveScrollBar(void) { return m_pActiveScrollBar; }
	void						clearActiveScrollBar(void) { m_pActiveScrollBar = nullptr; }

private:
	bool						initializeWindow(Window *pWindow, bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize, uint32 uiIcon);

private:
	bxcf::Vec2i										m_vecCursorPosition;
	bxcf::Vec2i										m_vecPreviousCursorPosition;
	bxcf::Vec2i										m_vecCursorScreenPosition;
	bxcf::Vec2i										m_vecCursorMoveDifference;
	HANDLE											m_tMainThread;
	std::thread										m_t2ndThread;
	bool											m_bThread1Locked;
	bool											m_bThread2Locked;
	bool											m_bMainThreadIsMarkedToUpdateWindow;
	GraphicsLibrary*								m_pGraphicsLibrary;
	Window*										m_pActiveWindow;
	RenderItem*									m_pRenderItemMouseIsOver;
	HCURSOR											m_hDefaultCursor;
	ScrollBar*										m_pActiveScrollBar;
	std::vector<Button*>							m_vecButtonsPressed;
	std::vector<Button*>							m_vecButtonsPressedPending;
	std::vector<MenuItem*>							m_vecMenuItemsPressed;

public:
	std::unordered_map<uint32, std::vector<RenderItem*>>	m_umapRenderItemEvents;
	bool													m_bTerminateThreads;
	bool													m_b2ndThreadHasTerminated;
};

template <class WindowClass>
WindowClass*					bxgx::BXGX::addWindow(bxcf::Vec2i& vecWindowPosition, bxcf::Vec2u& vecWindowSize, uint32 uiIcon)
{
	WindowClass *pWindow = new WindowClass;
	if (!initializeWindow(pWindow, vecWindowPosition, vecWindowSize, uiIcon))
	{
		delete pWindow;
		return nullptr;
	}
	return pWindow;
}

template <class WindowClass>
WindowClass*					bxgx::BXGX::addWindow(int32 x, int32 y, uint32 w, uint32 h, uint32 uiIcon)
{
	return addWindow<WindowClass>(Vec2i(x, y), Vec2u(w, h), uiIcon);
}

template <class WindowClass>
WindowClass*					bxgx::BXGX::addWindow(uint32 w, uint32 h, uint32 uiIcon)
{
	return addWindow<WindowClass>(Vec2i(-1, -1), Vec2u(w, h), uiIcon);
}

inline bxgx::BXGX*		bxgx::get(void) { return bxgx::BXGX::get(); }