#pragma once

#include "nsbxgi.h"
#include "Pool/VectorPool.h"
#include "Format/RW/ERWSection.h"
#include "Engine/RW/ERWVersion.h"
#include "Type/Vector/Vec4u8.h"
#include <vector>

class bxgi::RWSection;
class bxgi::_2dEffect;
class bxgi::RWFormat;

class bxgi::RWSectionContainer : public bxcf::VectorPool<bxgi::RWSection*>
{
public:
	RWSectionContainer(void);

	void									unload(void);

	virtual void							unserialize(void) = 0;
	virtual void							serialize(void) = 0;

	void									serializERWSectionContainer(RWSectionContainer *pRWSectionContainer);

	bxgi::RWSection*						addSection(bxgi::ERWSection ERWSectionValue, bxgi::ERWVersion ERWVersionValue);
	void									removeSectionByIndex(uint32 uiSectionIndex);
	std::vector<bxgi::RWSection*>			getSectionsByType(bxgi::ERWSection ERWSectionValue, bool bCheckRecursiveSections = true);
	uint32									getSectionCountByType(bxgi::ERWSection ERWSectionValue, bool bCheckRecursiveSections = true);

	void									removePrelightning(void);
	void									setPrelightningColour(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);
	void									applyPrelightningColourOffset(int16 ssRed, int16 ssGreen, int16 ssBlue, int16 ssAlpha);

	bxgi::RWFormat*							getRWFormat(void) { return nullptr; } // todo

	void									setParentNode(bxgi::RWSection* pParentNode) { m_pParentNode = pParentNode; }
	bxgi::RWSection*						getParentNode(void) { return m_pParentNode; }

	void									setDVColours(std::vector<bxcf::Vec4u8>& vecDVColours);
	std::vector<bxcf::Vec4u8>				getDVColours(void);

	void									setNVColours(std::vector<bxcf::Vec4u8>& vecNVColours);
	std::vector<bxcf::Vec4u8>				getNVColours(void);

	void									set2dEffects(std::vector<bxgi::_2dEffect*>& vec2dEffects);				// the array of 2d effects are all applied to all 2d effects sections
	void									set2dEffects(std::vector<std::vector<bxgi::_2dEffect*>>& vec2dEffects);	// index into outer vector represents 2d effects section index
	std::vector<std::vector<bxgi::_2dEffect*>>	get2dEffects(void);													// index into outer vector represents 2d effects section index

private:
	bxgi::RWSection*						m_pParentNode;
};