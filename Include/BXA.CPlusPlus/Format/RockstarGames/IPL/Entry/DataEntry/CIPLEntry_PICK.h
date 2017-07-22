#ifndef CIPLEntry_PICK_H
#define CIPLEntry_PICK_H

#include "BXA.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxa::CIPLEntry_PICK : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_PICK(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_PICK)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setWeaponId(uint32 uiWeaponId) { m_uiWeaponId = uiWeaponId; }
	uint32						getWeaponId(void) { return m_uiWeaponId; }

	void						setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&					getPosition(void) { return m_vecPosition; }

private:
	// GTA SA only
	uint32						m_uiWeaponId;
	bxa::CVector3D					m_vecPosition;
};

#endif