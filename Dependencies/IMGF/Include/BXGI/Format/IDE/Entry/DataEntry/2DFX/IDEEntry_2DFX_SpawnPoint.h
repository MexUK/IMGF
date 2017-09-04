#pragma once

#include "Format/IDE/Entry/DataEntry/IDEEntry_2DFX.h"
#include "Type/Vector/Vec4u.h"

class bxgi::IDEEntry_2DFX_SpawnPoint: public bxgi::IDEEntry_2DFX
{
public:
	IDEEntry_2DFX_SpawnPoint(bxgi::IDEFormat *pIDEFormat) :
		IDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_SPAWN_POINT)
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