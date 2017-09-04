#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"

class bxgi::RWSection_Texture : public bxgi::RWSection
{
public:
	RWSection_Texture(void);

	void							unserialize(void);
	void							serialize(void);

	void							setFilterFlags(uint16 usFilterFlags) { m_usFilterFlags = usFilterFlags; }
	uint16							getFilterFlags(void) { return m_usFilterFlags; }

	void							setUnknown1(uint16 usUnknown1) { m_usUnknown1 = usUnknown1; }
	uint16							getUnknown1(void) { return m_usUnknown1; }

private:
	uint16							m_usFilterFlags;
	uint16							m_usUnknown1;
};