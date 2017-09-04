#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"

class bxgi::RWSection_TextureDictionary : public bxgi::RWSection
{
public:
	RWSection_TextureDictionary(void);

	void							unserialize(void);
	void							serialize(void);

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	uint16							m_usDeviceId;
};