#ifndef CIDEEntry_2DFX_SpawnPoint_H
#define CIDEEntry_2DFX_SpawnPoint_H

#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec4u.h"
#include <string>

class bxcf::CIDEEntry_2DFX_SpawnPoint: public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SpawnPoint(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_SPAWN_POINT)
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

#endif