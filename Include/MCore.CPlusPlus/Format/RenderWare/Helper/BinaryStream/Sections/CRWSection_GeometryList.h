#ifndef CRWSection_GeometryList_H
#define CRWSection_GeometryList_H

#include "bxa.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"

class bxa::CRWSection_GeometryList : public bxa::CRWSection
{
public:
	CRWSection_GeometryList(void);

	void							unserialize(void);
	void							serialize(void);

	void							setGeometryCount(uint32 uiGeometryCount) { m_uiGeometryCount = uiGeometryCount; }
	uint32							getGeometryCount(void) { return m_uiGeometryCount; }

private:
	uint32							m_uiGeometryCount;
};

#endif