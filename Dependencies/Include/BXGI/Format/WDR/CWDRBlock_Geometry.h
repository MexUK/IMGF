#ifndef CWDRBlock_Geometry_H
#define CWDRBlock_Geometry_H

#include "bxgi.h"
#include <vector>

class bxgi::CWDRBlock_VertexData;
class bxgi::CWDRBlock_IndexData;

class bxgi::CWDRBlock_Geometry
{
public:
	std::vector<CWDRBlock_VertexData*>		m_vecVertices;
	std::vector<CWDRBlock_IndexData*>		m_vecIndices;
};

#endif