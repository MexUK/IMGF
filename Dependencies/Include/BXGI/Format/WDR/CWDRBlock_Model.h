#ifndef CWDRBlock_Model_H
#define CWDRBlock_Model_H

#include "bxgi.h"
#include <vector>

class bxgi::CWDRBlock_Geometry;

class bxgi::CWDRBlock_Model
{
public:
	std::vector<bxgi::CWDRBlock_Geometry*>		m_vecGeometries;
};

#endif