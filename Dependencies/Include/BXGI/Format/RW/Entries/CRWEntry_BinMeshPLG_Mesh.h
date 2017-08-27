#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include <vector>

class bxgi::CRWEntry_BinMeshPLG_Mesh
{
public:
	CRWEntry_BinMeshPLG_Mesh(void);

	void							setIndexCount(uint32 uiIndexCount) { m_uiIndexCount = uiIndexCount; }
	uint32							getIndexCount(void) { return m_uiIndexCount; }

	void							setMaterialIndex(uint32 uiMaterialIndex) { m_uiMaterialIndex = uiMaterialIndex; }
	uint32							getMaterialIndex(void) { return m_uiMaterialIndex; }

	std::vector<uint32>&			getVertexIndices(void) { return m_vecVertexIndices; }

private:
	uint32							m_uiIndexCount;
	uint32							m_uiMaterialIndex;
	std::vector<uint32>				m_vecVertexIndices;
};