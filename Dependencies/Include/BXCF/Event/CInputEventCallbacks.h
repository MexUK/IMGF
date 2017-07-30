#ifndef CInputEventCallbacks_H
#define CInputEventCallbacks_H

#include "bxcf.h"
#include "Type/Vector/CPoint2D.h"

class bxcf::CInputEventCallbacks
{
public:
	virtual void					onLeftMouseDown(bxcf::CPoint2D& vecCursorPoint) {}
	virtual void					onLeftMouseUp(bxcf::CPoint2D& vecCursorPoint) {}
	virtual void					onMouseMove(bxcf::CPoint2D& vecCursorPoint) {}
};

#endif