#ifndef CIDEEntry_2DFX_Ladder_H
#define CIDEEntry_2DFX_Ladder_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CIDEEntry_2DFX_Ladder : public bxcf::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Ladder(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxcf::_2DFX_LADDER),
		m_vecLadderStartPosition{ 0.0f, 0.0f, 0.0f },
		m_vecLadderEndPosition{ 0.0f, 0.0f, 0.0f },
		m_vecClimbDirectionPosition{ 0.0f, 0.0f, 0.0f },
		m_uiFlags(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setLadderStartPosition(bxcf::CVector3D& vecLadderStartPosition) { m_vecLadderStartPosition = vecLadderStartPosition; }
	bxcf::CVector3D&					getLadderStartPosition(void) { return m_vecLadderStartPosition; }

	void						setLadderEndPosition(bxcf::CVector3D& vecLadderEndPosition) { m_vecLadderEndPosition = vecLadderEndPosition; }
	bxcf::CVector3D&					getLadderEndPosition(void) { return m_vecLadderEndPosition; }

	void						setClimbDirectionPosition(bxcf::CVector3D& vecClimbDirectionPosition) { m_vecClimbDirectionPosition = vecClimbDirectionPosition; }
	bxcf::CVector3D&					getClimbDirectionPosition(void) { return m_vecClimbDirectionPosition; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

private:
	// GTA IV only
	bxcf::CVector3D					m_vecLadderStartPosition;
	bxcf::CVector3D					m_vecLadderEndPosition;
	bxcf::CVector3D					m_vecClimbDirectionPosition;
	uint32						m_uiFlags;
};

#endif