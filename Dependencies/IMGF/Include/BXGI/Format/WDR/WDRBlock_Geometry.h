#pragma once

#include "nsbxgi.h"
#include <vector>

class bxgi::WDRBlock_VertexData;
class bxgi::WDRBlock_IndexData;

class bxgi::WDRBlock_Geometry
{
public:
	std::vector<WDRBlock_VertexData*>		m_vecVertices;
	std::vector<WDRBlock_IndexData*>		m_vecIndices;
};