#pragma once

#include "nsbxgi.h"
#include "Type/Vector/Vec3f.h"

struct bxgi::TBounds
{
	float32			m_fRadius;
	bxcf::Vec3f		m_vecCenter;
	bxcf::Vec3f		m_vecMin;
	bxcf::Vec3f		m_vecMax;
};