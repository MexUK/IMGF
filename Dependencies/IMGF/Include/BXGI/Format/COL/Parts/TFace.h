#pragma once

#include "nsbxgi.h"
#include "Format/COL/Parts/TSurface.h"

struct bxgi::TFace
{
	uint32			m_uiA;
	uint32			m_uiB;
	uint32			m_uiC;
	TSurface		m_surface;
};