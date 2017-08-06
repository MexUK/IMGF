#ifndef CRWSection_H
#define CRWSection_H

#include <d2d1.h>
#include "bxcf.h"
#include "CRWSectionContainer.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include <vector>
#include <unordered_map>

class bxcf::CRWSection;

class bxcf::CRWSection : public bxcf::CRWSectionContainer
{
public:
	CRWSection(void);

	static void						initStatic(void);

	void							serialize(void);

	bxcf::CRWSection*						addSection(bxcf::eRWSection eRWSectionValue, bxcf::eRWVersion eRWVersionValue);
	void							removeSection(void);
	uint32							getSectionIndex(void);

	void							fillPlaceholdersForSerialization(uint32 uiSectionByteCount, uint32 uiSectionStructByteCount);

	static bxcf::CRWSection*				createRWSection(bxcf::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct(bxcf::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct_BeforeInit(bxcf::eRWSection eRWSectionValue);

	static std::vector<bxcf::eRWSection>					getRWSections(void);
	static std::unordered_map<bxcf::eRWSection, bool>&	getRWSectionsContainingStruct(void) { return m_umapRWSectionsContainingStruct; }

	void							setSectionId(bxcf::eRWSection eSectionId) { m_eSectionId = eSectionId; }
	bxcf::eRWSection				getSectionId(void) { return m_eSectionId; }

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
	bxcf::eRWSection				m_eSectionId;
	uint32							m_uiSectionSize;
	uint32							m_uiSectionRWVersion;
	uint32							m_uiStructSectionSize;
	bool							m_bUnknownSection;

private:
	uint8											m_bSectionHeaderSkipped		: 1;
	static std::unordered_map<bxcf::eRWSection, bool>		m_umapRWSectionsContainingStruct;
};

#endif