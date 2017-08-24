#ifndef CRWEntry_BinMeshPLG_Mesh_H
#define CRWEntry_BinMeshPLG_Mesh_H

#include "bxgi.h"
#include "Type/Types.h"
#include <vector>

class bxgi::CRWEntry_BinMeshPLG_Mesh
{
public:
	CRWEntry_BinMeshPLG_Mesh(void) :
		m_uiIndexCount(0),
		m_uiMaterialIndex(0)
	{};

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

#endif