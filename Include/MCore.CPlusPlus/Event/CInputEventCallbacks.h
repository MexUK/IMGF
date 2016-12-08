#ifndef CInputEventCallbacks_H
#define CInputEventCallbacks_H

#include "mcore.h"
#include "Type/Vector/CPoint2D.h"

class mcore::CInputEventCallbacks
{
public:
	virtual void					onLeftMouseDown(mcore::CPoint2D& vecCursorPoint) {}
	virtual void					onLeftMouseUp(mcore::CPoint2D& vecCursorPoint) {}
	virtual void					onMouseMove(mcore::CPoint2D& vecCursorPoint) {}
};

#endif