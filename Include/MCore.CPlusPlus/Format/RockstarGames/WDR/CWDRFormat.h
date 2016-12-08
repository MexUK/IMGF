#ifndef CWDRFormat_H
#define CWDRFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "CWDRBoundingObject.h"
#include <string>
#include <vector>

class mcore::CWDRBlock_Geometry;
class mcore::CIntermediateGeometry;
class mcore::CWDRBlock_Model;

class mcore::CWDRFormat : public mcore::CFormat
{
public:
	CWDRFormat(void) : CFormat(true, mcore::LITTLE_ENDIAN) {};

	void								unload(void);

	static mcore::CWDRBlock_Geometry*			convertIntermediateGeometryToWDRGeometry(mcore::CIntermediateGeometry *pGeneralGeometry);

public:
	void								unserialize(void);
	void								serialize(void);

public: // todo - make the properties private
	mcore::CWDRBoundingObject					m_boundingObject;
	std::vector<mcore::CWDRBlock_Model*>		m_vecModels;
};

#endif