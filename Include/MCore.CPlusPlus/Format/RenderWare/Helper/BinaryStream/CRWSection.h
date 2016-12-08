#ifndef CRWSection_H
#define CRWSection_H

#include <d2d1.h>
#include "mcore.h"
#include "CRWSectionContainer.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include <vector>
#include <unordered_map>

class mcore::CRWSection;

class mcore::CRWSection : public mcore::CRWSectionContainer
{
public:
	CRWSection(void);

	static void						initStatic(void);

	void							serialize(void);

	mcore::CRWSection*						addSection(mcore::eRWSection eRWSectionValue, mcore::eRWVersion eRWVersionValue);
	void							removeSection(void);
	uint32							getSectionIndex(void);

	void							fillPlaceholdersForSerialization(uint32 uiSectionByteCount, uint32 uiSectionStructByteCount);

	static mcore::CRWSection*				createRWSection(mcore::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct(mcore::eRWSection eRWSectionValue);
	static bool						doesRWSectionContainStruct_BeforeInit(mcore::eRWSection eRWSectionValue);

	static std::vector<mcore::eRWSection>					getRWSections(void);
	static std::unordered_map<mcore::eRWSection, bool>&	getRWSectionsContainingStruct(void) { return m_umapRWSectionsContainingStruct; }

	void							setSectionId(mcore::eRWSection eSectionId) { m_eSectionId = eSectionId; }
	mcore::eRWSection				getSectionId(void) { return m_eSectionId; }

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
	mcore::eRWSection				m_eSectionId;
	uint32							m_uiSectionSize;
	uint32							m_uiSectionRWVersion;
	uint32							m_uiStructSectionSize;
	bool							m_bUnknownSection;

private:
	uint8											m_bSectionHeaderSkipped		: 1;
	static std::unordered_map<mcore::eRWSection, bool>		m_umapRWSectionsContainingStruct;
};

#endif