#ifndef CWDRBlock_Geometry_H
#define CWDRBlock_Geometry_H

#include "BXA.h"
#include <vector>

class bxa::CWDRBlock_VertexData;
class bxa::CWDRBlock_IndexData;

class bxa::CWDRBlock_Geometry
{
public:
	std::vector<CWDRBlock_VertexData*>		m_vecVertices;
	std::vector<CWDRBlock_IndexData*>		m_vecIndices;
};

#endif