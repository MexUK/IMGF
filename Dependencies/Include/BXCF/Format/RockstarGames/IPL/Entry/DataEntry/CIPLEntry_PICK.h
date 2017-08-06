#ifndef CIPLEntry_PICK_H
#define CIPLEntry_PICK_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_PICK : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_PICK(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_PICK)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setWeaponId(uint32 uiWeaponId) { m_uiWeaponId = uiWeaponId; }
	uint32						getWeaponId(void) { return m_uiWeaponId; }

	void						setPosition(bxcf::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CVector3D&					getPosition(void) { return m_vecPosition; }

private:
	// GTA SA only
	uint32						m_uiWeaponId;
	bxcf::CVector3D					m_vecPosition;
};

#endif