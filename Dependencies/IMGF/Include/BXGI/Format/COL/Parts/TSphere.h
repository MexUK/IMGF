#pragma once

#include "nsbxgi.h"
#include "Format/COL/Parts/TSurface.h"
#include "Type/Vector/Vec3f.h"

struct bxgi::TSphere
{
	float32			m_fRadius;
	bxcf::Vec3f		m_vecCenter;
	TSurface		m_surface;
};