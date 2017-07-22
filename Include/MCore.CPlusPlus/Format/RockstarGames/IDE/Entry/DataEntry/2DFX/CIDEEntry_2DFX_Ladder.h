#ifndef CIDEEntry_2DFX_Ladder_H
#define CIDEEntry_2DFX_Ladder_H

#include "bxa.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxa::CIDEEntry_2DFX_Ladder : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Ladder(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_LADDER),
		m_vecLadderStartPosition{ 0.0f, 0.0f, 0.0f },
		m_vecLadderEndPosition{ 0.0f, 0.0f, 0.0f },
		m_vecClimbDirectionPosition{ 0.0f, 0.0f, 0.0f },
		m_uiFlags(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setLadderStartPosition(bxa::CVector3D& vecLadderStartPosition) { m_vecLadderStartPosition = vecLadderStartPosition; }
	bxa::CVector3D&					getLadderStartPosition(void) { return m_vecLadderStartPosition; }

	void						setLadderEndPosition(bxa::CVector3D& vecLadderEndPosition) { m_vecLadderEndPosition = vecLadderEndPosition; }
	bxa::CVector3D&					getLadderEndPosition(void) { return m_vecLadderEndPosition; }

	void						setClimbDirectionPosition(bxa::CVector3D& vecClimbDirectionPosition) { m_vecClimbDirectionPosition = vecClimbDirectionPosition; }
	bxa::CVector3D&					getClimbDirectionPosition(void) { return m_vecClimbDirectionPosition; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

private:
	// GTA IV only
	bxa::CVector3D					m_vecLadderStartPosition;
	bxa::CVector3D					m_vecLadderEndPosition;
	bxa::CVector3D					m_vecClimbDirectionPosition;
	uint32						m_uiFlags;
};

#endif