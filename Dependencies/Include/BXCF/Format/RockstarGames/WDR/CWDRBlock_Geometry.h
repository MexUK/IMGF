#ifndef CWDRBlock_Geometry_H
#define CWDRBlock_Geometry_H

#include "bxcf.h"
#include <vector>

class bxcf::CWDRBlock_VertexData;
class bxcf::CWDRBlock_IndexData;

class bxcf::CWDRBlock_Geometry
{
public:
	std::vector<CWDRBlock_VertexData*>		m_vecVertices;
	std::vector<CWDRBlock_IndexData*>		m_vecIndices;
};

#endif