#ifndef CRWSectionContainer_H
#define CRWSectionContainer_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
// #include "CRWSection.h" // todo
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include "Type/Vector/CVector4ui8.h"
#include <vector>

class mcore::CRWSection;
class mcore::C2dEffect;
class mcore::CRWFormat;

class mcore::CRWSectionContainer : public mcore::CVectorPool<mcore::CRWSection*>
{
public:
	CRWSectionContainer(void);

	void									unload(void);

	virtual void							unserialize(void) = 0;
	virtual void							serialize(void) = 0;

	void									serializeRWSectionContainer(CRWSectionContainer *pRWSectionContainer);

	mcore::CRWSection*								addSection(mcore::eRWSection eRWSectionValue, mcore::eRWVersion eRWVersionValue);
	void									removeSectionByIndex(uint32 uiSectionIndex);
	std::vector<mcore::CRWSection*>				getSectionsByType(mcore::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);
	uint32									getSectionCountByType(mcore::eRWSection eRWSectionValue, bool bCheckRecursiveSections = true);

	void									removePrelightning(void);
	void									setPrelightningColour(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);
	void									applyPrelightningColourOffset(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);

	mcore::CRWFormat*								getRWFormat(void) { return nullptr; } // todo

	void									setParentNode(mcore::CRWSection* pParentNode) { m_pParentNode = pParentNode; }
	mcore::CRWSection*								getParentNode(void) { return m_pParentNode; }

	void									setDVCColours(std::vector<mcore::CVector4ui8>& vecDVCColours);
	std::vector<mcore::CVector4ui8>				getDVCColours(void);

	void									setNVCColours(std::vector<mcore::CVector4ui8>& vecNVCColours);
	std::vector<mcore::CVector4ui8>				getNVCColours(void);

	void									set2dEffects(std::vector<mcore::C2dEffect*>& vec2dEffects);				// the array of 2d effects are all applied to all 2d effects sections
	void									set2dEffects(std::vector<std::vector<mcore::C2dEffect*>>& vec2dEffects);	// index into outer vector represents 2d effects section index
	std::vector<std::vector<mcore::C2dEffect*>>	get2dEffects(void);													// index into outer vector represents 2d effects section index

private:
	mcore::CRWSection*								m_pParentNode;
};

#endif