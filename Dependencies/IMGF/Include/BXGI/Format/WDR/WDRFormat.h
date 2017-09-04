#pragma once

#include "nsbxgi.h"
#include "Format/Format.h"
#include "WDRBoundingObject.h"
#include <string>
#include <vector>

class bxgi::WDRBlock_Geometry;
class bxgi::IntermediateGeometry;
class bxgi::WDRBlock_Model;

class bxgi::WDRFormat : public bxcf::Format
{
public:
	WDRFormat(void) : Format(true, bxcf::LITTLE_ENDIAN) {}

	void								unload(void);

	static bxgi::WDRBlock_Geometry*			convertIntermediateGeometryToWDRGeometry(bxgi::IntermediateGeometry *pGeneralGeometry);

public:
	void								unserialize(void);
	void								serialize(void);

public: // todo - make the properties private
	bxgi::WDRBoundingObject					m_boundingObject;
	std::vector<bxgi::WDRBlock_Model*>		m_vecModels;
};