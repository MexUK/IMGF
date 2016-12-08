#ifndef CWDRBlock_Model_H
#define CWDRBlock_Model_H

#include "mcore.h"
#include <vector>

class mcore::CWDRBlock_Geometry;

class mcore::CWDRBlock_Model
{
public:
	std::vector<mcore::CWDRBlock_Geometry*>		m_vecGeometries;
};

#endif