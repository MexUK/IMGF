#pragma once

#include "nsbxgx.h"
#include "Pool/VectorPool.h"
#include "Control/Controls/ScrollBar.h"

class bxgx::ScrollBarPool : public bxcf::VectorPool<ScrollBar*>
{
public:
	ScrollBar*					getScrollBarByOrientation(bxcf::E2DAxis uiOrientation);
};