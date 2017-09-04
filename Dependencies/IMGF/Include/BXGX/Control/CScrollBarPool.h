#pragma once

#include "nsbxgx.h"
#include "Pool/CVectorPool.h"
#include "Controls/CScrollBar.h"

class bxgx::CScrollBarPool : public bxcf::CVectorPool<CScrollBar*>
{
public:
	CScrollBar*					getScrollBarByOrientation(E2DAxis uiOrientation);
};