#ifndef CInputEventCallbacks_H
#define CInputEventCallbacks_H

#include "bxa.h"
#include "Type/Vector/CPoint2D.h"

class bxa::CInputEventCallbacks
{
public:
	virtual void					onLeftMouseDown(bxa::CPoint2D& vecCursorPoint) {}
	virtual void					onLeftMouseUp(bxa::CPoint2D& vecCursorPoint) {}
	virtual void					onMouseMove(bxa::CPoint2D& vecCursorPoint) {}
};

#endif