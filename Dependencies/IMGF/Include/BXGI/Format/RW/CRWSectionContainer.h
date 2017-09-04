#pragma once

#include "nsbxgi.h"
#include "Pool/CVectorPool.h"
// #include "CRWSection.h" // todo
#include "Format/RW/ERWSection.h"
#include "Engine/RW/ERWVersion.h"
#include "Type/Vector/Vec4u8.h"
#include <vector>

class bxgi::CRWSection;
class bxgi::C2dEffect;
class bxgi::CRWFormat;

class bxgi::CRWSectionContainer : public bxcf::CVectorPool<bxgi::CRWSection*>
{
public:
	CRWSectionContainer(void);

	void									unload(void);

	virtual void							unserialize(void) = 0;
	virtual void							serialize(void) = 0;

	void									serializERWSectionContainer(CRWSectionContainer *pRWSectionContainer);

	bxgi::CRWSection*								addSection(bxgi::ERWSection ERWSectionValue, bxgi::ERWVersion ERWVersionValue);
	void									removeSectionByIndex(uint32 uiSectionIndex);
	std::vector<bxgi::CRWSection*>				getSectionsByType(bxgi::ERWSection ERWSectionValue, bool bCheckRecursiveSections = true);
	uint32									getSectionCountByType(bxgi::ERWSection ERWSectionValue, bool bCheckRecursiveSections = true);

	void									removePrelightning(void);
	void									setPrelightningColour(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);
	void									applyPrelightningColourOffset(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);

	bxgi::CRWFormat*								getRWFormat(void) { return nullptr; } // todo

	void									setParentNode(bxgi::CRWSection* pParentNode) { m_pParentNode = pParentNode; }
	bxgi::CRWSection*								getParentNode(void) { return m_pParentNode; }

	void									setDVCColours(std::vector<bxcf::Vec4u8>& vecDVCColours);
	std::vector<bxcf::Vec4u8>				getDVCColours(void);

	void									setNVCColours(std::vector<bxcf::Vec4u8>& vecNVCColours);
	std::vector<bxcf::Vec4u8>				getNVCColours(void);

	void									set2dEffects(std::vector<bxgi::C2dEffect*>& vec2dEffects);				// the array of 2d effects are all applied to all 2d effects sections
	void									set2dEffects(std::vector<std::vector<bxgi::C2dEffect*>>& vec2dEffects);	// index into outer vector represents 2d effects section index
	std::vector<std::vector<bxgi::C2dEffect*>>	get2dEffects(void);													// index into outer vector represents 2d effects section index

private:
	bxgi::CRWSection*								m_pParentNode;
};