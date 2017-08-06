#pragma once

#include "bxcf.h"
#include "bxgx.h"

class CGUIEventUtilizer
{
public:
	// event usages
	void									markEventUsages(uint32 uiEventCount, ...);
	void									markEventUsage(uint32 uiEvent);
	void									unmarkEventUsage(uint32 uiEvent);
	bool									isEventUsageMarked(uint32 uiEvent);

	// point testing
	inline virtual bool						isPointInItem(bxcf::CPoint2D& vecPoint) = 0;

	// focus testing
	inline virtual bool						doesItemHaveFocus(void) = 0;

	// events
	virtual bool							onGainFocus(void) { return false; }
	virtual bool							onLoseFocus(void) { return false; }

	virtual bool							onMouseMove(bxcf::CPoint2D& vecCursorPoint) { return false; }

	virtual bool							onLeftMouseDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onLeftMouseUp(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleLeftMouseDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleLeftMouseUp(bxcf::CPoint2D& vecCursorPoint) { return false; }

	virtual bool							onRightMouseDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onRightMouseUp(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleRightMouseDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleRightMouseUp(bxcf::CPoint2D& vecCursorPoint) { return false; }

	virtual bool							onMouseWheelMove(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onMouseWheelDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onMouseWheelUp(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleMouseWheelDown(bxcf::CPoint2D& vecCursorPoint) { return false; }
	virtual bool							onDoubleMouseWheelUp(bxcf::CPoint2D& vecCursorPoint) { return false; }

	virtual bool							onKeyDown(uint16 uiKey) { return false; }
	virtual bool							onKeyUp(uint16 uiKey) { return false; }
	virtual bool							onKeyHeld(uint16 uiKey) { return false; }
	virtual bool							onDoubleKeyDown(uint16 uiKey) { return false; }
	virtual bool							onDoubleKeyUp(uint16 uiKey) { return false; }

	virtual bool							onRender(void) { return false; }
	virtual bool							onRenderBefore(void) { return false; }
	virtual bool							onRenderAfter(void) { return false; }
};