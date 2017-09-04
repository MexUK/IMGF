#pragma once

#include "nsbxgi.h"
#include <vector>

class bxgi::WDRBlock_Geometry;

class bxgi::WDRBlock_Model
{
public:
	std::vector<bxgi::WDRBlock_Geometry*>		m_vecGeometries;
};