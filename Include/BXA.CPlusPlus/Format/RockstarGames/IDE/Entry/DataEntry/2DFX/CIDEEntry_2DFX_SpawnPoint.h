#ifndef CIDEEntry_2DFX_SpawnPoint_H
#define CIDEEntry_2DFX_SpawnPoint_H

#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/CVector4ui32.h"
#include <string>

class bxa::CIDEEntry_2DFX_SpawnPoint: public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_SpawnPoint(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_SPAWN_POINT)
	{
		m_vecFlags.m_x = 0;
		m_vecFlags.m_y = 0;
		m_vecFlags.m_z = 0;
		m_vecFlags.m_w = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						setFlags(bxa::CVector4ui32& vecFlags) { m_vecFlags = vecFlags; }
	bxa::CVector4ui32&				getFlags(void) { return m_vecFlags; }

private:
	// GTA IV only
	bxa::CVector4ui32				m_vecFlags;
};

#endif