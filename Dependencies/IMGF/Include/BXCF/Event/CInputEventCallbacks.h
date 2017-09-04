#ifndef CInputEventCallbacks_H
#define CInputEventCallbacks_H

#include "bxcf.h"
#include "Type/Vector/Vec2i.h"

class bxcf::CInputEventCallbacks
{
public:
	virtual void					onLeftMouseDown(bxcf::Vec2i& vecCursorPoint) {}
	virtual void					onLeftMouseUp(bxcf::Vec2i& vecCursorPoint) {}
	virtual void					onMouseMove(bxcf::Vec2i& vecCursorPoint) {}
};

#endif