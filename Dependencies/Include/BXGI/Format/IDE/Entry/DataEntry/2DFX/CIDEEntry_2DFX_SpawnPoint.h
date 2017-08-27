#pragma once

#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec4u.h"

class bxgi::CIDEEntry_2DFX_SpawnPoint: public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SpawnPoint(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_SPAWN_POINT)
	{
		m_vecFlags.x = 0;
		m_vecFlags.y = 0;
		m_vecFlags.z = 0;
		m_vecFlags.w = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						setFlags(bxcf::Vec4u& vecFlags) { m_vecFlags = vecFlags; }
	bxcf::Vec4u&				getFlags(void) { return m_vecFlags; }

private:
	// GTA IV only
	bxcf::Vec4u				m_vecFlags;
};