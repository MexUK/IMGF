#ifndef CIDEEntry_2DFX_Ped_H
#define CIDEEntry_2DFX_Ped_H

#include "mcore.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/CVector3D.h"

class mcore::CIDEEntry_2DFX_Ped : public mcore::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Ped(mcore::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, mcore::_2DFX_PED),
		m_uiBehaviour(0),
		m_vecUnknown2{ 0.0f, 0.0f, 0.0f },
		m_vecPedRotation{ 0.0f, 0.0f, 0.0f }
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setBehaviour(uint32 uiBehaviour) { m_uiBehaviour = uiBehaviour; }
	uint32						getBehaviour(void) { return m_uiBehaviour; }

	void						setUnknown2(mcore::CVector3D& vecUnknown2) { m_vecUnknown2 = vecUnknown2; }
	mcore::CVector3D&					getUnknown2(void) { return m_vecUnknown2; }

	void						setPedRotation(mcore::CVector3D& vecPedRotation) { m_vecPedRotation = vecPedRotation; }
	mcore::CVector3D&					getPedRotation(void) { return m_vecPedRotation; }

private:
	// GTA III era only
	uint32						m_uiBehaviour;
	mcore::CVector3D					m_vecUnknown2;
	mcore::CVector3D					m_vecPedRotation;
};

#endif