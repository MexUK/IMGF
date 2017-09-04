#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/RWSection.h"
#include "Format/RW/Entries/RWEntry_BinMeshPLG_Mesh.h"
#include <vector>

class bxgi::RWSection_BinMeshPLG : public bxgi::RWSection
{
public:
	RWSection_BinMeshPLG(void);

	void										unserialize(void);
	void										serialize(void);

	void										setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32										getFlags(void) { return m_uiFlags; }

	void										setMeshCount(uint32 uiMeshCount) { m_uiMeshCount = uiMeshCount; }
	uint32										getMeshCount(void) { return m_uiMeshCount; }

	void										setIndexCount(uint32 uiIndexCount) { m_uiIndexCount = uiIndexCount; }
	uint32										getIndexCount(void) { return m_uiIndexCount; }

	std::vector<bxgi::RWEntry_BinMeshPLG_Mesh*>&		getMeshes(void) { return m_vecMeshes; }

private:
	uint32										m_uiFlags; // 0 = triangle list, 1 = triangle strip
	uint32										m_uiMeshCount;
	uint32										m_uiIndexCount;
	std::vector<bxgi::RWEntry_BinMeshPLG_Mesh*>		m_vecMeshes;
};