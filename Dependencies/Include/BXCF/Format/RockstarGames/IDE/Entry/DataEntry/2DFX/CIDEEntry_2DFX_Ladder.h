#ifndef CIDEEntry_2DFX_Ladder_H
#define CIDEEntry_2DFX_Ladder_H

#include "bxcf.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec3f.h"
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

	void						setLadderStartPosition(bxcf::Vec3f& vecLadderStartPosition) { m_vecLadderStartPosition = vecLadderStartPosition; }
	bxcf::Vec3f&					getLadderStartPosition(void) { return m_vecLadderStartPosition; }

	void						setLadderEndPosition(bxcf::Vec3f& vecLadderEndPosition) { m_vecLadderEndPosition = vecLadderEndPosition; }
	bxcf::Vec3f&					getLadderEndPosition(void) { return m_vecLadderEndPosition; }

	void						setClimbDirectionPosition(bxcf::Vec3f& vecClimbDirectionPosition) { m_vecClimbDirectionPosition = vecClimbDirectionPosition; }
	bxcf::Vec3f&					getClimbDirectionPosition(void) { return m_vecClimbDirectionPosition; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

private:
	// GTA IV only
	bxcf::Vec3f					m_vecLadderStartPosition;
	bxcf::Vec3f					m_vecLadderEndPosition;
	bxcf::Vec3f					m_vecClimbDirectionPosition;
	uint32						m_uiFlags;
};

#endif