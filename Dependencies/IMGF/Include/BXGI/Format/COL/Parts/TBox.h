#pragma once

#include "nsbxgi.h"
#include "Type/Vector/Vec3f.h"

struct bxgi::TBox
{
	bxcf::Vec3f		m_min;
	bxcf::Vec3f		m_max;
	TSurface		m_surface;
};