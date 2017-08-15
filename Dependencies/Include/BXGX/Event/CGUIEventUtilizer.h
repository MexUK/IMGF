#pragma once

#include "bxcf.h"
#include "bxgx.h"
#include "Type/Types.h"
#include <string>
#include <vector>
#include <set>

class CGUIEventUtilizer
{
public:
	// event usages
	void									markEventUsages(uint32 uiEventCount, ...);
	void									markEventUsage(uint32 uiEvent);
	void									unmarkEventUsage(uint32 uiEvent);
	void									unmarkEventUsages(uint32 uiEventCount, ...);
	void									unmarkAllEventUsages(void);
	bool									isEventUsageMarked(uint32 uiEvent);
	bool									isAnyEventUsageMarked(void);

	// item
	inline virtual uint32					getItemType(void) = 0;
	virtual uint32							getItemSubType(void) = 0;

	// rendering
	void									setRenderingControlComponent(uint32 uiControlComponent);
	void									resetRenderingControlComponent(void);
	void									setRenderingStyleStatus(uint32 uiStyleStatus);
	void									resetRenderingStyleStatus(void);
	void									setRenderingStyleFragment(uint32 uiStyleFragment);
	void									resetRenderingStyleFragment(void);
	void									setRenderingStyleGroups(std::string strStyleGroups);
	void									setRenderingStyleGroups(std::vector<uint32> vecStyleGroups);
	void									resetRenderingStyleGroups(void);

	// point testing
	inline virtual bool						isPointInItem(bxcf::Vec2i& vecPoint) = 0;

	// focus testing
	inline virtual bool						doesItemHaveFocus(void) = 0;

	// events
	virtual bool							onGainFocus(void) { return false; }
	virtual bool							onLoseFocus(void) { return false; }

	virtual bool							onMouseMove(bxcf::Vec2i& vecCursorPoint) { return false; }

	virtual bool							onLeftMouseDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onLeftMouseUp(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleLeftMouseDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleLeftMouseUp(bxcf::Vec2i& vecCursorPoint) { return false; }

	virtual bool							onRightMouseDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onRightMouseUp(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleRightMouseDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleRightMouseUp(bxcf::Vec2i& vecCursorPoint) { return false; }

	virtual bool							onMouseWheelMove(int16 iRotationDistance) { return false; }
	virtual bool							onMouseWheelDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onMouseWheelUp(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleMouseWheelDown(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onDoubleMouseWheelUp(bxcf::Vec2i& vecCursorPoint) { return false; }

	virtual bool							onMouseEnter(bxcf::Vec2i& vecCursorPoint) { return false; }
	virtual bool							onMouseExit(bxcf::Vec2i& vecCursorPoint) { return false; }

	virtual bool							onKeyDown(uint16 uiKey) { return false; }
	virtual bool							onKeyUp(uint16 uiKey) { return false; }
	virtual bool							onKeyHeld(uint16 uiKey) { return false; }
	virtual bool							onDoubleKeyDown(uint16 uiKey) { return false; }
	virtual bool							onDoubleKeyUp(uint16 uiKey) { return false; }

	virtual void							onRender(void) {}
	virtual void							onRenderBefore(void) {}
	virtual void							onRenderAfter(void) {}

	void									setStyleGroups(std::string& strStyleGroups);
	void									setStyleGroups(std::vector<std::string>& vecStyleGroups);
	void									setStyleGroups(std::vector<uint32>& vecStyleGroups) { m_vecStyleGroups = vecStyleGroups; }
	std::vector<uint32>&					getStyleGroups(void) { return m_vecStyleGroups; }

private:
	std::set<uint32>						m_setItemEvents;
	std::vector<uint32>						m_vecStyleGroups;
};