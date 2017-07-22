#ifndef CRWSectionContainer_H
#define CRWSectionContainer_H

#include "bxa.h"
#include "Pool/CVectorPool.h"
// #include "CRWSection.h" // todo
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include "Type/Vector/CVector4ui8.h"
#include <vector>

class bxa::CRWSection;
class bxa::C2dEffect;
class bxa::CRWFormat;

class bxa::CRWSectionContainer : public bxa::CVectorPool<bxa::CRWSection*>
{
public:
	CRWSectionContainer(void);

	void									unload(void);

	virtual void							unserialize(void) = 0;
	virtual void							serialize(void) = 0;

	void									serializeRWSectionContainer(CRWSectionContainer *pRWSectionContainer);

	bxa::CRWSection*								addSection(bxa::eRWSection eRWSectionValue, bxa::eRWVersion eRWVersionValue);
	void									removeSectionByIndex(uint32 uiSectionIndex);
	std::vector<bxa::CRWSection*>				getSectionsByType(bxa::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);
	uint32									getSectionCountByType(bxa::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);

	void									removePrelightning(void);
	void									setPrelightningColour(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);
	void									applyPrelightningColourOffset(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);

	bxa::CRWFormat*								getRWFormat(void) { return nullptr; } // todo

	void									setParentNode(bxa::CRWSection* pParentNode) { m_pParentNode = pParentNode; }
	bxa::CRWSection*								getParentNode(void) { return m_pParentNode; }

	void									setDVCColours(std::vector<bxa::CVector4ui8>& vecDVCColours);
	std::vector<bxa::CVector4ui8>				getDVCColours(void);

	void									setNVCColours(std::vector<bxa::CVector4ui8>& vecNVCColours);
	std::vector<bxa::CVector4ui8>				getNVCColours(void);

	void									set2dEffects(std::vector<bxa::C2dEffect*>& vec2dEffects);				// the array of 2d effects are all applied to all 2d effects sections
	void									set2dEffects(std::vector<std::vector<bxa::C2dEffect*>>& vec2dEffects);	// index into outer vector represents 2d effects section index
	std::vector<std::vector<bxa::C2dEffect*>>	get2dEffects(void);													// index into outer vector represents 2d effects section index

private:
	bxa::CRWSection*								m_pParentNode;
};

#endif