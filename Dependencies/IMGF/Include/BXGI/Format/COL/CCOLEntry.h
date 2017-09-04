#pragma once

#include "nsbxgi.h"
#include "Type/Vector/Vec3f.h"
#include "TShapes.h"
#include "CCOLVersion.h"
#include <string>
#include <vector>

class bxgi::CCOLFormat;

class bxgi::CCOLEntry
{
public:
								CCOLEntry(bxgi::CCOLFormat *pCOLFile);

	void						unload(void) {}

	void						unserialize(void);
	void						serialize(void);

	uint32						calculateCollisionMeshVertexCount(void);
	uint32						calculateShadowMeshVertexCount(void);

	void						applyCollisionMeshVerticesOffset(bxcf::Vec3f vecAxisOffsets);

	TBounds&					getBoundingObjects(void) { return m_boundingObjects; }
	std::vector<TSphere>&		getCollisionSpheres(void) { return m_vecCollisionSpheres; }
	std::vector<TBox>&			getCollisionBoxes(void) { return m_vecCollisionBoxes; }
	std::vector<TVertex>&		getCollisionMeshVertices(void) { return m_vecCollisionMeshVertices; }
	std::vector<TFace>&			getCollisionMeshFaces(void) { return m_vecCollisionMeshFaces; }
	std::vector<TFaceGroup>&	getCollisionMeshFaceGroups(void) { return m_vecCollisionMeshFaceGroups; }

	std::vector<TVertex>&		getShadowMeshVertices(void) { return m_vecShadowMeshVertices; }
	std::vector<TFace>&			getShadowMeshFaces(void) { return m_vecShadowMeshFaces; }

	uint32						getCollisionSpheresByteCount(void) { return m_uiCollisionSphereCount * 20; }
	uint32						getCollisionBoxesByteCount(void) { return m_uiCollisionBoxCount * 28; }
	uint32						getCollisionConesByteCount(void) { return m_uiCollisionConeCount * 0; }
	uint32						getCollisionMeshVerticesByteCount(void) { return m_uiCollisionMeshVertexCount * (m_uiCOLVersion == COL_UNKNOWN || m_uiCOLVersion == COL_1 ? 12 : 6); }
	uint32						getCollisionMeshFacesByteCount(void) { return m_uiCollisionMeshFaceCount * (m_uiCOLVersion == COL_UNKNOWN || m_uiCOLVersion == COL_1 ? 16 : 8); }
	uint32						getCollisionMeshFaceGroupsByteCount(void) { return m_uiCollisionMeshFaceGroupCount * 28; }
	uint32						getShadowMeshVerticesByteCount(void) { return m_uiShadowMeshVertexCount * 6; }
	uint32						getShadowMeshFacesByteCount(void) { return m_uiShadowMeshFaceCount * 8; }

	void						parseBoundingObjects(void);
	void						parseCollisionSpheres(void);
	void						parseCollisionBoxes(void);
	void						parseCollisionMeshVertices(void);
	void						parseCollisionMeshFaces(void);
	void						parseCollisionMeshFaceGroups(void);
	void						parseShadowMeshVertices(void);
	void						parseShadowMeshFaces(void);

	void						storeBoundingObjects(void);
	void						storeCollisionSpheres(void);
	void						storeCollisionBoxes(void);
	void						storeCollisionMeshVertices(void);
	void						storeCollisionMeshFaces(void);
	void						storeCollisionMeshFaceGroups(void);
	void						storeShadowMeshVertices(void);
	void						storeShadowMeshFaces(void);

	void				setCOLFile(CCOLFormat *pCOLFile) { m_pCOLFile = pCOLFile; }
	CCOLFormat*			getCOLFile(void) { return m_pCOLFile; }

	void				setCOLVersion(ECOLVersion uiCOLVersion) { m_uiCOLVersion = uiCOLVersion; }
	ECOLVersion			getCOLVersion(void) { return m_uiCOLVersion; }

	void				setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&		getModelName(void) { return m_strModelName; }

	void				setModelId(uint16 usModelId) { m_usModelId = usModelId; }
	uint16				getModelId(void) { return m_usModelId; }

	void				setTBounds(std::string strTBounds) { m_strTBounds = strTBounds; }
	std::string			getTBounds(void) { return m_strTBounds; }

	void				setCollisionSphereCount(uint32 uiCollisionSphereCount) { m_uiCollisionSphereCount = uiCollisionSphereCount; }
	uint32				getCollisionSphereCount(void) { return m_uiCollisionSphereCount; }

	void				setCollisionBoxCount(uint32 uiCollisionBoxCount) { m_uiCollisionBoxCount = uiCollisionBoxCount; }
	uint32				getCollisionBoxCount(void) { return m_uiCollisionBoxCount; }

	void				setCollisionMeshFaceCount(uint32 uiCollisionMeshFaceCount) { m_uiCollisionMeshFaceCount = uiCollisionMeshFaceCount; }
	uint32				getCollisionMeshFaceCount(void) { return m_uiCollisionMeshFaceCount; }

	void				setCollisionMeshVertexCount(uint32 uiCollisionMeshVertexCount) { m_uiCollisionMeshVertexCount = uiCollisionMeshVertexCount; }
	uint32				getCollisionMeshVertexCount(void) { return m_uiCollisionMeshVertexCount; }

	void				setCollisionConeCount(uint32 uiCollisionConeCount) { m_uiCollisionConeCount = uiCollisionConeCount; }
	uint32				getCollisionConeCount(void) { return m_uiCollisionConeCount; }

	void				setCollisionMeshFaceGroupCount(uint32 uiCollisionMeshFaceGroupCount) { m_uiCollisionMeshFaceGroupCount = uiCollisionMeshFaceGroupCount; }
	uint32				getCollisionMeshFaceGroupCount(void) { return m_uiCollisionMeshFaceGroupCount; }

	void				setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32				getFlags(void) { return m_uiFlags; }

	void				setCollisionSpheresOffset(uint32 uiCollisionSpheresOffset) { m_uiCollisionSpheresOffset = uiCollisionSpheresOffset; }
	uint32				getCollisionSpheresOffset(void) { return m_uiCollisionSpheresOffset; }

	void				setCollisionBoxesOffset(uint32 uiCollisionBoxesOffset) { m_uiCollisionBoxesOffset = uiCollisionBoxesOffset; }
	uint32				getCollisionBoxesOffset(void) { return m_uiCollisionBoxesOffset; }

	void				setCollisionConesOffset(uint32 uiCollisionConesOffset) { m_uiCollisionConesOffset = uiCollisionConesOffset; }
	uint32				getCollisionConesOffset(void) { return m_uiCollisionConesOffset; }

	void				setCollisionMeshVerticesOffset(uint32 uiCollisionMeshVerticesOffset) { m_uiCollisionMeshVerticesOffset = uiCollisionMeshVerticesOffset; }
	uint32				getCollisionMeshVerticesOffset(void) { return m_uiCollisionMeshVerticesOffset; }

	void				setCollisionMeshFacesOffset(uint32 uiCollisionMeshFacesOffset) { m_uiCollisionMeshFacesOffset = uiCollisionMeshFacesOffset; }
	uint32				getCollisionMeshFacesOffset(void) { return m_uiCollisionMeshFacesOffset; }

	void				setTrianglePlanesOffset(uint32 uiTrianglePlanesOffset) { m_uiTrianglePlanesOffset = uiTrianglePlanesOffset; }
	uint32				getTrianglePlanesOffset(void) { return m_uiTrianglePlanesOffset; }

	void				setShadowMeshVertexCount(uint32 uiShadowMeshVertexCount) { m_uiShadowMeshVertexCount = uiShadowMeshVertexCount; }
	uint32				getShadowMeshVertexCount(void) { return m_uiShadowMeshVertexCount; }

	void				setShadowMeshFaceCount(uint32 uiShadowMeshFaceCount) { m_uiShadowMeshFaceCount = uiShadowMeshFaceCount; }
	uint32				getShadowMeshFaceCount(void) { return m_uiShadowMeshFaceCount; }

	void				setShadowMeshVerticesOffset(uint32 uiShadowMeshVerticesOffset) { m_uiShadowMeshVerticesOffset = uiShadowMeshVerticesOffset; }
	uint32				getShadowMeshVerticesOffset(void) { return m_uiShadowMeshVerticesOffset; }

	void				setShadowMeshFacesOffset(uint32 uiShadowMeshFacesOffset) { m_uiShadowMeshFacesOffset = uiShadowMeshFacesOffset; }
	uint32				getShadowMeshFacesOffset(void) { return m_uiShadowMeshFacesOffset; }

	void				setCollisionMeshFaceGroupsOffset(uint32 uiCollisionMeshFaceGroupsOffset) { m_uiCollisionMeshFaceGroupsOffset = uiCollisionMeshFaceGroupsOffset; }
	uint32				getCollisionMeshFaceGroupsOffset(void) { return m_uiCollisionMeshFaceGroupsOffset; }

	void				setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; } // used by COL 1 and COL 4
	uint32				getUnknown1(void) { return m_uiUnknown1; } // used by COL 1 and COL 4

	void				setHeaderStartOffset(uint32 uiHeaderStartOffset) { m_uiHeaderStartOffset = uiHeaderStartOffset; }
	uint32				getHeaderStartOffset(void) { return m_uiHeaderStartOffset; }

private:
	void				serializeHeader_Versions2_3_4(void);

	void				serializeBody_Version1(void);
	void				serializeBody_Versions2_3_4(void);

	uint32				calculateEntrySizeForPacking(void);
	uint32				getFlagsForPacking(void);

private:
	CCOLFormat*				m_pCOLFile;

	ECOLVersion				m_uiCOLVersion;
	uint32					m_uiFileSize;
	std::string				m_strModelName;
	uint16					m_usModelId;
	std::string				m_strTBounds;

	uint32					m_uiCollisionSphereCount;
	uint32					m_uiCollisionBoxCount;
	uint32					m_uiCollisionMeshVertexCount;
	uint32					m_uiCollisionMeshFaceCount;
	uint32					m_uiCollisionMeshFaceGroupCount;
	uint32					m_uiCollisionConeCount;
	uint32					m_uiFlags;
	uint32					m_uiCollisionSpheresOffset;
	uint32					m_uiCollisionBoxesOffset;
	uint32					m_uiCollisionConesOffset;
	uint32					m_uiCollisionMeshVerticesOffset;
	uint32					m_uiCollisionMeshFacesOffset;
	uint32					m_uiTrianglePlanesOffset;
	uint32					m_uiCollisionMeshFaceGroupsOffset;

	uint32					m_uiShadowMeshVertexCount;
	uint32					m_uiShadowMeshFaceCount;
	uint32					m_uiShadowMeshVerticesOffset;
	uint32					m_uiShadowMeshFacesOffset;

	uint32					m_uiUnknown1; // used by COL 1 and COL 4

	uint32					m_uiHeaderStartOffset;

	std::vector<TSphere>	m_vecCollisionSpheres;
	std::vector<TBox>		m_vecCollisionBoxes;
	std::vector<TVertex>	m_vecCollisionMeshVertices;
	std::vector<TFace>		m_vecCollisionMeshFaces;
	std::vector<TFaceGroup>	m_vecCollisionMeshFaceGroups;
	std::vector<TVertex>	m_vecShadowMeshVertices;
	std::vector<TFace>		m_vecShadowMeshFaces;
	TBounds					m_boundingObjects;
};