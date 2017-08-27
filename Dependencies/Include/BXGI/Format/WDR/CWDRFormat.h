#pragma once

#include "nsbxgi.h"
#include "Format/CFormat.h"
#include "CWDRBoundingObject.h"
#include <string>
#include <vector>

class bxgi::CWDRBlock_Geometry;
class bxgi::CIntermediateGeometry;
class bxgi::CWDRBlock_Model;

class bxgi::CWDRFormat : public bxcf::CFormat
{
public:
	CWDRFormat(void) : CFormat(true, bxcf::LITTLE_ENDIAN) {}

	void								unload(void);

	static bxgi::CWDRBlock_Geometry*			convertIntermediateGeometryToWDRGeometry(bxgi::CIntermediateGeometry *pGeneralGeometry);

public:
	void								unserialize(void);
	void								serialize(void);

public: // todo - make the properties private
	bxgi::CWDRBoundingObject					m_boundingObject;
	std::vector<bxgi::CWDRBlock_Model*>		m_vecModels;
};