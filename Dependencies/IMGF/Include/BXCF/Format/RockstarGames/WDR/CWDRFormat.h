#ifndef CWDRFormat_H
#define CWDRFormat_H

#include "bxcf.h"
#include "Format/CFormat.h"
#include "CWDRBoundingObject.h"
#include <string>
#include <vector>

class bxcf::CWDRBlock_Geometry;
class bxcf::CIntermediateGeometry;
class bxcf::CWDRBlock_Model;

class bxcf::CWDRFormat : public bxcf::CFormat
{
public:
	CWDRFormat(void) : CFormat(true, bxcf::LITTLE_ENDIAN) {};

	void								unload(void);

	static bxcf::CWDRBlock_Geometry*			convertIntermediateGeometryToWDRGeometry(bxcf::CIntermediateGeometry *pGeneralGeometry);

public:
	void								unserialize(void);
	void								serialize(void);

public: // todo - make the properties private
	bxcf::CWDRBoundingObject					m_boundingObject;
	std::vector<bxcf::CWDRBlock_Model*>		m_vecModels;
};

#endif