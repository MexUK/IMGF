#ifndef CRWSection_ExtraVertColour_H
#define CRWSection_ExtraVertColour_H

#include "bxgi.h"
#include "Format/RW/CRWSection.h"
#include "Type/Vector/Vec4u8.h"

class bxgi::CRWSection_ExtraVertColour : public bxgi::CRWSection
{
public:
	CRWSection_ExtraVertColour(void);

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

#endif