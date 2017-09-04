#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3f.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_PICK : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_PICK(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setWeaponId(uint32 uiWeaponId) { m_uiWeaponId = uiWeaponId; }
	uint32						getWeaponId(void) { return m_uiWeaponId; }

	void						setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&					getPosition(void) { return m_vecPosition; }

private:
	// GTA SA only
	uint32						m_uiWeaponId;
	bxcf::Vec3f					m_vecPosition;
};