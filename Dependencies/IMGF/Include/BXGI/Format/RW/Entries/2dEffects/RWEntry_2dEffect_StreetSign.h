#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/_2dEffect.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxgi::RWEntry_2dEffect_StreetSign : public bxgi::_2dEffect
{
public:
	RWEntry_2dEffect_StreetSign(void);

	void							unserialize(void);
	void							serialize(void);

	void							setSize(bxcf::Vec2f& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2f&					getSize(void) { return m_vecSize; }

	void							setRotation(bxcf::Vec3f& vecRotation) { m_vecRotation = vecRotation; }
	bxcf::Vec3f&					getRotation(void) { return m_vecRotation; }

	void							setFlags(int16 uiFlags) { m_uiFlags = uiFlags; }
	int16							getFlags(void) { return m_uiFlags; }

	void							setText(uint8 uiStringIndex, std::string& strData) { m_strText[uiStringIndex] = strData; }
	std::string&					getText(uint8 uiStringIndex) { return m_strText[uiStringIndex]; }

private:
	bxcf::Vec2f						m_vecSize;
	bxcf::Vec3f						m_vecRotation;
	uint16							m_uiFlags;
	std::string						m_strText[4];
};