#ifndef CWindow_H
#define CWindow_H

#include <Windows.h>
#include <gdiplus.h>
#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Type/Colour/CColour.h"
#include "Pool/CVectorPool.h"
#include "Event/CEventType.h"
#include "Event/CEventBoundFunction.h"
#include "Event/CEventBinder.h"
#include "Layer/CGUILayer.h"
#include "Item/CGUIItem.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyleableEntity.h"
#include "Interaction/CRectangleItemPlacement.h"
#include "Event/Events.h"
#include <functional>
#include <unordered_map>
#include <vector>

class CRadioControl;
class CDropTarget;
class CGUIStyles;
class CWindow;
class bxcf::CInputEventCallbacks;
class CGUIControl;

class CWindow : /*public bxcf::EventTriggerable, */public bxcf::EventBindable<CWindow>, public bxcf::CEventType, public CGUIStyleableEntity, public bxcf::CVectorPool<CGUILayer*>, public CGUIEventUtilizer
{
public:
	CWindow(void);
	~CWindow(void);
	
	void									init(void);

	void									unload(void);

	void									bindEvents(void);
	void									unbindEvents(void);
	void									bindLayerEvents(void);
	void									unbindLayerEvents(void);
	
	void									unserialize(void);
	void									serialize(void);

	uint32									getItemType(void) { return bxgx::item::WINDOW; }
	uint32									getItemSubType(void) { return bxgx::item::window::TYPE_1; }

	bool									isPointInItem(bxcf::Vec2i& vecPoint) { return true; }
	bool									doesItemHaveFocus(void) { return true; }

	bool									isPointInControl(bxcf::Vec2i& vecPoint);
	CGUIControl*							getControlFromPoint(bxcf::Vec2i& vecPoint);
	bool									doesDropHaveListOpen(void);

	// old - temp
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*, void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, bxcf::CInputEventCallbacks *pObject, void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bool									triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	void									onWindowLoseFocus(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPoint);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	bool									onDoubleLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPoint);

	void									onRenderBefore(void);
	void									onRenderAfter(void);

	virtual void							render(void);
	void									renderNow(void);
	void									checkToRender(void);
	void									onRenderFromWMPaint(void);

	bool									checkToApplyWindowResizeCursor(void);
	bool									checkToApplyWindowRegularCursor(void);
	bool									checkToStartMovingOrResizingWindow(bool bCursorIsHoveringTitleBarIcon = false);
	bool									checkToStopMovingOrResizingWindow(void);
	bool									checkToMoveOrResizeWindow(void);

	void									setMaxSizeApplies(bool bMaxSizeApplies) { m_bMaxSizeApplies = bMaxSizeApplies; }
	bool									doesMaxSizeApply(void) { return m_bMaxSizeApplies; }

	void									setMinSize(bxcf::Vec2u& vecMinSize) { m_vecMinSize = vecMinSize; }
	bxcf::Vec2u&							getMinSize(void) { return m_vecMinSize; }

	void									setMaxSize(bxcf::Vec2u& vecMaxSize) { m_vecMaxSize = vecMaxSize; }
	bxcf::Vec2u&							getMaxSize(void) { return m_vecMaxSize; }

	void									setClassName(const char * pClassName) { m_pClassName = pClassName; }
	const char *							getClassName(void) { return m_pClassName; }

	void									setTitleBarHeight(uint32 uiTitleBarHeight) { m_uiTitleBarHeight = uiTitleBarHeight; }
	uint32									getTitleBarHeight(void) { return m_uiTitleBarHeight; }

private:
	void									setTitleBarColour(bxcf::CColour colour) { m_colTitleBarColour = colour; }
	bxcf::CColour							getTitleBarColour(void) { return m_colTitleBarColour; }

	void									setTitleBarIconGapDistance(uint32 uiTitleBarIconGapDistance) { m_uiTitleBarIconGapDistance = uiTitleBarIconGapDistance; }
	uint32									getTitleBarIconGapDistance(void) { return m_uiTitleBarIconGapDistance; }

	void									setTitleBarIconHoverStatus(bool bTitleBarIconHoverStatus) { m_bTitleBarIconHoverStatus = bTitleBarIconHoverStatus; }
	bool									getTitleBarIconHoverStatus(void) { return m_bTitleBarIconHoverStatus; }

	void									setTitleBarIconHoverIndex(uint32 uiTitleBarIconHoverIndex) { m_uiTitleBarIconHoverIndex = uiTitleBarIconHoverIndex; }
	uint32									getTitleBarIconHoverIndex(void) { return m_uiTitleBarIconHoverIndex; }

public:
	void									addTitleBar(std::string strTitleBarText);
	void									removeTitleBar(void);

private:
	bxcf::Vec2i								getTitleBarIconPosition(uint32 uiIconIndex);
	bxcf::Vec2u								getTitleBarIconSize(void);
	bool									isPointInTitleBar(bxcf::Vec2i& vecPoint);
	CGUIStyles								getTitleBarIconStyles(void);
	void									onClickTitleBarIcon(uint32 uiIconIndex);

	uint8									getTitleBarIconCursorHoverIndex(void);
	bool									isCursorHoveringTitleBarIcon(void);
	bxcf::Vec2i								getTitleBarIconsHoverPosition(void);
	bxcf::Vec2u								getTitleBarIconsHoverSize(void);

	void									renderTitleBar(void);
	void									renderTitleBarBackground(void);
	void									renderTitleBarText(void);

	void									renderTitleBarIcons(void);

	void									renderTitleBarIconHoverBackground(void);

	void									renderTitleBarMinimizeIcon(void);
	void									renderTitleBarMaximizeIcon(void);
	void									renderTitleBarCloseIcon(void);

public:
	CGUILayer*								createLayer(uint32 uiLayerId = -1, bool bEnabled = true);
	CGUILayer*								createLayer(CWindow *pWindow, uint32 uiLayerId = -1, bool bEnabled = true);
	CGUILayer*								addLayer(uint32 uiLayerId = -1, bool bEnabled = true);
	template <class LayerClass>
	LayerClass*								addLayer(uint32 uiLayerId = -1, bool bEnabled = true);
	CGUILayer*								getLayerById(uint32 uiLayerId);
	void									swapLayersEnabled(uint32 uiLayerId1, uint32 uiLayerId2);

	bool									doesActiveItemExist(void) { return m_pActiveItem != nullptr; }
	void									setActiveItem(CGUIItem *pItem);
	CGUIItem*								getActiveItem(void) { return m_pActiveItem; }
	void									clearActiveItem(void);

	void									unmarkRadios(CRadioControl *pRadio);

	void									setOpenLastFilename(std::string strFileName);
	void									clearOpenLastFilename(void);

	void									setWindowHandle(HWND hwndWindow) { m_hwndWindow = hwndWindow; }
	HWND									getWindowHandle(void) { return m_hwndWindow; }

	void									setMarkedToRedraw(bool bMarkedToRedraw) { m_bMarkedToRedraw = bMarkedToRedraw; }
	void									markToRedraw(void) { m_bMarkedToRedraw = true; }
	bool									isMarkedToRedraw(void) { return m_bMarkedToRedraw; }

	void									setPosition(bxcf::Vec2i& vecPosition);
	bxcf::Vec2i&							getPosition(void) { return m_vecPosition; }

	void									setSize(bxcf::Vec2u& vecSize);
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }

	void									setMovingWindow(bool bMovingMainWindow) { m_bMovingWindow = bMovingMainWindow; }
	bool									isMovingWindow(void) { return m_bMovingWindow; }

	void									setResizingWindow(bool bResizingWindow) { m_bResizingWindow = bResizingWindow; }
	bool									isResizingWindow(void) { return m_bResizingWindow; }

	void									setWindowResizeEdges(uint32 uiMainWindowResizeEdges) { m_uiWindowResizeEdges = uiMainWindowResizeEdges; }
	uint32									getWindowResizeEdges(void) { return m_uiWindowResizeEdges; }

	void									setParentWindow(CWindow *pParentWindow) { m_pParentWindow = pParentWindow; }
	CWindow*								getParentWindow(void) { return m_pParentWindow; }

	void									setMaximized(bool bMaximized);
	bool									isMaximized(void) { return m_bMaximized; }

	void									setMinimized(bool bMinimized);
	bool									isMinimized(void) { return m_bMinimized; }

	void									setPreviousPosition(bxcf::Vec2i& vecPreviousPosition) { m_vecPreviousPosition = vecPreviousPosition; }
	bxcf::Vec2i&							getPreviousPosition(void) { return m_vecPreviousPosition; }

	void									setPreviousSize(bxcf::Vec2u& vecPreviousSize) { m_vecPreviousSize = vecPreviousSize; }
	bxcf::Vec2u&							getPreviousSize(void) { return m_vecPreviousSize; }

	void									setEventTriggerEventTypeId(bxcf::eEventType eEventTriggerEventTypeId) { m_eEventTriggerEventTypeId = eEventTriggerEventTypeId; }
	bxcf::eEventType						getEventTriggerEventTypeId(void) { return m_eEventTriggerEventTypeId; }

private:
	const char *							m_pClassName;
	HWND									m_hwndWindow;
	CWindow*								m_pParentWindow;
	bxcf::Vec2i								m_vecPosition;
	bxcf::Vec2u								m_vecSize;
	bxcf::Vec2u								m_vecMinSize;
	bxcf::Vec2u								m_vecMaxSize;
	uint32									m_uiWindowResizeEdges;
	CDropTarget*							m_pDropTarget;
	uint32									m_uiTitleBarHeight;
	bxcf::CColour							m_colTitleBarColour;
	std::string								m_strTitleBarText;
	uint32									m_uiTitleBarIconGapDistance;
	uint32									m_uiTitleBarIconHoverIndex;
	uint8									m_bMovingWindow					: 1;
	uint8									m_bResizingWindow				: 1;
	uint8									m_bMarkedToRedraw				: 1;
	uint8									m_bMaximized					: 1;
	uint8									m_bMinimized					: 1;
	uint8									m_bTitleBarIconHoverStatus		: 1;
	uint8									m_bTitleBarExists				: 1;
	uint8									m_bMaxSizeApplies				: 1;
	bxcf::Vec2i								m_vecPreviousPosition;
	bxcf::Vec2u								m_vecPreviousSize;
	CGUIItem*								m_pActiveItem;
	bxcf::eEventType						m_eEventTriggerEventTypeId;
	// todo CRectangleItemPlacement<CWindow>	m_placeableWindow;		// gui windows
	CRectangleItemPlacement<CGUIItem>		m_placeableItem;		// gui items - e.g. shapes and controls
	std::unordered_map<uint32, bool>		m_umapEventUsages;

	/*
	todo
	HMENU						m_hMenu_File;
	HMENU						m_hSubMenu_File_OpenRecent;
	HMENU						m_hMenu_Entry_Sort;
	HMENU						m_hSubMenu_File_Sessions;

	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_SelectRWVersion; // todo - move this shit to like CMenuManager
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_FilterRWVersion;
	std::unordered_map<uint32, eCOLVersion>			m_umapMenuItemMapping_FilterCOLVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion_DragDrop;

	std::unordered_map<uint32, eCOLVersion>		m_umapFilterMapping_COLVersion;
	std::unordered_map<uint32, eRWVersion>		m_umapFilterMapping_RWVersion;
	int											m_iFilterMapping_UnknownVersion;
	*/
};

/*
template <typename... Args>
void									CWindow::bindEvent(uint32 uiEvent, void(*function)(Args&... args))
{

}
*/

template <class LayerClass>
LayerClass*								CWindow::addLayer(uint32 uiLayerId, bool bEnabled)
{
	LayerClass *pLayer = new LayerClass;
	pLayer->setWindow(this);
	pLayer->setId(uiLayerId);
	pLayer->setEnabledWithoutEvents(bEnabled);
	addEntry(pLayer);
	return pLayer;
}

#endif