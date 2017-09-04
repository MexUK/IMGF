#ifndef CWDRBlock_Model_H
#define CWDRBlock_Model_H

#include "bxcf.h"
#include <vector>

class bxcf::CWDRBlock_Geometry;

class bxcf::CWDRBlock_Model
{
public:
	std::vector<bxcf::CWDRBlock_Geometry*>		m_vecGeometries;
};

#endif