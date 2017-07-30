#ifndef CRWSectionContainer_H
#define CRWSectionContainer_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
// #include "CRWSection.h" // todo
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include "Type/Vector/CVector4ui8.h"
#include <vector>

class bxcf::CRWSection;
class bxcf::C2dEffect;
class bxcf::CRWFormat;

class bxcf::CRWSectionContainer : public bxcf::CVectorPool<bxcf::CRWSection*>
{
public:
	CRWSectionContainer(void);

	void									unload(void);

	virtual void							unserialize(void) = 0;
	virtual void							serialize(void) = 0;

	void									serializeRWSectionContainer(CRWSectionContainer *pRWSectionContainer);

	bxcf::CRWSection*								addSection(bxcf::eRWSection eRWSectionValue, bxcf::eRWVersion eRWVersionValue);
	void									removeSectionByIndex(uint32 uiSectionIndex);
	std::vector<bxcf::CRWSection*>				getSectionsByType(bxcf::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);
	uint32									getSectionCountByType(bxcf::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);

	void									removePrelightning(void);
	void									setPrelightningColour(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);
	void									applyPrelightningColourOffset(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);

	bxcf::CRWFormat*								getRWFormat(void) { return nullptr; } // todo

	void									setParentNode(bxcf::CRWSection* pParentNode) { m_pParentNode = pParentNode; }
	bxcf::CRWSection*								getParentNode(void) { return m_pParentNode; }

	void									setDVCColours(std::vector<bxcf::CVector4ui8>& vecDVCColours);
	std::vector<bxcf::CVector4ui8>				getDVCColours(void);

	void									setNVCColours(std::vector<bxcf::CVector4ui8>& vecNVCColours);
	std::vector<bxcf::CVector4ui8>				getNVCColours(void);

	void									set2dEffects(std::vector<bxcf::C2dEffect*>& vec2dEffects);				// the array of 2d effects are all applied to all 2d effects sections
	void									set2dEffects(std::vector<std::vector<bxcf::C2dEffect*>>& vec2dEffects);	// index into outer vector represents 2d effects section index
	std::vector<std::vector<bxcf::C2dEffect*>>	get2dEffects(void);													// index into outer vector represents 2d effects section index

private:
	bxcf::CRWSection*								m_pParentNode;
};

#endif