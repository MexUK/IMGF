#ifndef CGUIScrollPool_H
#define CGUIScrollPool_H

#include "Pool/CVectorPool.h"
#include "Controls/CScrollControl.h"

class CGUIScrollPool : public bxcf::CVectorPool<CScrollControl*>
{
public:
	CScrollControl*					getScrollBarByOrientation(e2DMirroredOrientation uiOrientation);
};

#endif