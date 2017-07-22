#ifndef CWDRFormat_H
#define CWDRFormat_H

#include "BXA.h"
#include "Format/CFormat.h"
#include "CWDRBoundingObject.h"
#include <string>
#include <vector>

class bxa::CWDRBlock_Geometry;
class bxa::CIntermediateGeometry;
class bxa::CWDRBlock_Model;

class bxa::CWDRFormat : public bxa::CFormat
{
public:
	CWDRFormat(void) : CFormat(true, bxa::LITTLE_ENDIAN) {};

	void								unload(void);

	static bxa::CWDRBlock_Geometry*			convertIntermediateGeometryToWDRGeometry(bxa::CIntermediateGeometry *pGeneralGeometry);

public:
	void								unserialize(void);
	void								serialize(void);

public: // todo - make the properties private
	bxa::CWDRBoundingObject					m_boundingObject;
	std::vector<bxa::CWDRBlock_Model*>		m_vecModels;
};

#endif