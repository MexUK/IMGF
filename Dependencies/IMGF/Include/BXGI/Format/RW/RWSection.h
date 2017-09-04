#pragma once

#include "nsbxgi.h"
#include "RWSectionContainer.h"
#include "Format/RW/ERWSection.h"
#include "Engine/RW/ERWVersion.h"
#include <vector>
#include <unordered_map>

class bxgi::RWSection;

class bxgi::RWSection : public bxgi::RWSectionContainer
{
public:
	RWSection(void);

	static void						initStatic(void);

	void							serialize(void);

	bxgi::RWSection*				addSection(bxgi::ERWSection ERWSectionValue, bxgi::ERWVersion ERWVersionValue);
	void							removeSection(void);
	uint32							getSectionIndex(void);

	void							fillPlaceholdersForSerialization(uint32 uiSectionByteCount, uint32 uiSectionStructByteCount);

	static bxgi::RWSection*		creatERWSection(bxgi::ERWSection ERWSectionValue);
	static bool						doesRWSectionContainStruct(bxgi::ERWSection ERWSectionValue);
	static bool						doesRWSectionContainStruct_BeforeInit(bxgi::ERWSection ERWSectionValue);

	static std::vector<bxgi::ERWSection>				getRWSections(void);
	static std::unordered_map<bxgi::ERWSection, bool>&	getRWSectionsContainingStruct(void) { return m_umapRWSectionsContainingStruct; }

	void							setSectionId(bxgi::ERWSection eSectionId) { m_uiSectionId = eSectionId; }
	bxgi::ERWSection				getSectionId(void) { return m_uiSectionId; }

	void							setSectionSize(uint32 uiSectionSize) { m_uiSectionSize = uiSectionSize; }
	uint32							getSectionSize(void) { return m_uiSectionSize; }

	void							setStructSectionSize(uint32 uiStructSectionSize) { m_uiStructSectionSize = uiStructSectionSize; }
	uint32							getStructSectionSize(void) { return m_uiStructSectionSize; }

	void							setSectionRWVersion(uint32 uiSectionRWVersion) { m_uiSectionRWVersion = uiSectionRWVersion; }
	uint32							getSectionRWVersion(void) { return m_uiSectionRWVersion; }

	void							setSectionHeaderSkipped(bool bSectionHeaderSkipped) { m_bSectionHeaderSkipped = bSectionHeaderSkipped; }
	bool							isSectionHeaderSkipped(void) { return m_bSectionHeaderSkipped; }

	void							setUnknownSection(bool bUnknownSection) { m_bUnknownSection = bUnknownSection; }
	bool							isUnknownSection(void) { return m_bUnknownSection; }

	RWSection*						getNextParentNodeWithSectionType(ERWSection eSection);
	
private:
	static void						initRWSections(void);

protected:
	bxgi::ERWSection				m_uiSectionId;
	uint32							m_uiSectionSize;
	uint32							m_uiSectionRWVersion;
	uint32							m_uiStructSectionSize;
	bool							m_bUnknownSection;

private:
	uint8													m_bSectionHeaderSkipped		: 1;
	static std::unordered_map<bxgi::ERWSection, bool>		m_umapRWSectionsContainingStruct;
};