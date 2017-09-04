#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"

class bxgi::RWSection_GeometryList : public bxgi::RWSection
{
public:
	RWSection_GeometryList(void);

	void							unserialize(void);
	void							serialize(void);

	void							setGeometryCount(uint32 uiGeometryCount) { m_uiGeometryCount = uiGeometryCount; }
	uint32							getGeometryCount(void) { return m_uiGeometryCount; }

private:
	uint32							m_uiGeometryCount;
};