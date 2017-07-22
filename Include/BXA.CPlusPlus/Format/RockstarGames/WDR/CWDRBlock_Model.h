#ifndef CWDRBlock_Model_H
#define CWDRBlock_Model_H

#include "BXA.h"
#include <vector>

class bxa::CWDRBlock_Geometry;

class bxa::CWDRBlock_Model
{
public:
	std::vector<bxa::CWDRBlock_Geometry*>		m_vecGeometries;
};

#endif