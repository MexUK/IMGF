#pragma once

#include "nsbxgi.h"
#include "Type/Vector/Vec3f.h"

struct bxgi::TFaceGroup
{
	bxcf::Vec3f		m_min;
	bxcf::Vec3f		m_max;
	uint16			m_startFace;
	uint16			m_endFace;
};