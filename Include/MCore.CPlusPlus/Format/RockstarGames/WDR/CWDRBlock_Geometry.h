#ifndef CWDRBlock_Geometry_H
#define CWDRBlock_Geometry_H

#include "mcore.h"
#include <vector>

class mcore::CWDRBlock_VertexData;
class mcore::CWDRBlock_IndexData;

class mcore::CWDRBlock_Geometry
{
public:
	std::vector<CWDRBlock_VertexData*>		m_vecVertices;
	std::vector<CWDRBlock_IndexData*>		m_vecIndices;
};

#endif