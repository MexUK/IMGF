#ifndef CRWSection_H
#define CRWSection_H

#include "bxgi.h"
#include "CRWSectionContainer.h"
#include "Format/RW/eRWSection.h"
#include "Engine/RW/eRWVersion.h"
#include <vector>
#include <unordered_map>

class bxgi::CRWSection;

class bxgi::CRWSection : public bxgi::CRWSectionContainer
{
public:
	CRWSection(void);

	static void						initStatic(void);

	void							serialize(void);

	bxgi::CRWSection*				addSection(bxgi::eRWSection eRWSectionValue, bxgi::eRWVersion eRWVersionValue);
	void							removeSection(void);
	uint32							getSectionIndex(void);

	void							fillPlaceholdersForSerialization(uint32 uiSectionByteCount, uint32 uiSectionStructByteCount);

	static bxgi::CRWSection*		createRWSection(bxgi::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct(bxgi::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct_BeforeInit(bxgi::eRWSection eRWSectionValue);

	static std::vector<bxgi::eRWSection>				getRWSections(void);
	static std::unordered_map<bxgi::eRWSection, bool>&	getRWSectionsContainingStruct(void) { return m_umapRWSectionsContainingStruct; }

	void							setSectionId(bxgi::eRWSection eSectionId) { m_eSectionId = eSectionId; }
	bxgi::eRWSection				getSectionId(void) { return m_eSectionId; }

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

	CRWSection*						getNextParentNodeWithSectionType(eRWSection eSection);
	
private:
	static void						initRWSections(void);

protected:
	bxgi::eRWSection				m_eSectionId;
	uint32							m_uiSectionSize;
	uint32							m_uiSectionRWVersion;
	uint32							m_uiStructSectionSize;
	bool							m_bUnknownSection;

private:
	uint8													m_bSectionHeaderSkipped		: 1;
	static std::unordered_map<bxgi::eRWSection, bool>		m_umapRWSectionsContainingStruct;
};

#endif