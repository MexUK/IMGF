#ifndef CRWSection_ExtraVertColour_H
#define CRWSection_ExtraVertColour_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Type/Vector/CVector4ui8.h"

class bxcf::CRWSection_ExtraVertColour : public bxcf::CRWSection
{
public:
	CRWSection_ExtraVertColour(void);

	void							unserialize(void);
	void							serialize(void);

	void							setMagicNumber(uint32 uiMagicNumber) { m_uiMagicNumber = uiMagicNumber; }
	uint32							getMagicNumber(void) { return m_uiMagicNumber; }

	void							setVertexColours(std::vector<bxcf::CVector4ui8>& vecNightVertexColours); // remainder filled with 0xFFFFFFFF to match geometry vertex count.
	std::vector<bxcf::CVector4ui8>&		getVertexColours(void) { return m_vecNightVertexColours; }

private:
	uint32							m_uiMagicNumber;
	std::vector<bxcf::CVector4ui8>		m_vecNightVertexColours;
};

#endif