#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"
#include "Type/Vector/Vec4u8.h"

class bxgi::RWSection_ExtraVertColour : public bxgi::RWSection
{
public:
	RWSection_ExtraVertColour(void);

	void							unserialize(void);
	void							serialize(void);

	void							setMagicNumber(uint32 uiMagicNumber) { m_uiMagicNumber = uiMagicNumber; }
	uint32							getMagicNumber(void) { return m_uiMagicNumber; }

	void							setVertexColours(std::vector<bxcf::Vec4u8>& vecNightVertexColours); // remainder filled with 0xFFFFFFFF to match geometry vertex count.
	std::vector<bxcf::Vec4u8>&		getVertexColours(void) { return m_vecNightVertexColours; }

private:
	uint32							m_uiMagicNumber;
	std::vector<bxcf::Vec4u8>		m_vecNightVertexColours;
};