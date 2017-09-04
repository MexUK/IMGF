#pragma once

#include "nsbxgi.h"
#include <vector>

class bxgi::CWDRBlock_Geometry;

class bxgi::CWDRBlock_Model
{
public:
	std::vector<bxgi::CWDRBlock_Geometry*>		m_vecGeometries;
};