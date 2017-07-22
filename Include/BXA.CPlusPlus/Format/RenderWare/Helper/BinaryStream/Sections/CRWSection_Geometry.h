#ifndef CRWSection_Geometry_H
#define CRWSection_Geometry_H

#include "BXA.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Partial/CRWGeometryBoundingInfo.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include "Type/Vector/CVector4ui8.h"
#include "Type/Vector/CVector4ui16.h"
#include <string>

class bxa::CIntermediateGeometry;

class bxa::CRWSection_Geometry : public bxa::CRWSection
{
public:
	CRWSection_Geometry(void);

	void							unserialize(void);
	void							serialize(void);

	std::string						getTextureDiffuseName(void);

	void							removePrelightning(void);

	bxa::CIntermediateGeometry*			convertToIntermediateGeometry(void);

	void							setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32							getFlags(void) { return m_uiFlags; }

	void							setUVCoordinateCount(uint8 ucUVCoordinateCount) { m_ucUVCoordinateCount = ucUVCoordinateCount; }
	uint8							getUVCoordinateCount(void) { return m_ucUVCoordinateCount; }

	void							setGeometryNativeFlags(uint8 ucGeometryNativeFlags) { m_ucGeometryNativeFlags = ucGeometryNativeFlags; }
	uint8							getGeometryNativeFlags(void) { return m_ucGeometryNativeFlags; }

	void							setTriangleCount(uint32 uiTriangleCount) { m_uiTriangleCount = uiTriangleCount; }
	uint32							getTriangleCount(void) { return m_uiTriangleCount; }

	void							setVertexCount(uint32 uiVertexCount) { m_uiVertexCount = uiVertexCount; }
	uint32							getVertexCount(void) { return m_uiVertexCount; }

	void							setFrameCount(uint32 uiFrameCount) { m_uiFrameCount = uiFrameCount; }
	uint32							getFrameCount(void) { return m_uiFrameCount; }

	void							setAmbientColour(uint32 uiAmbientColour) { m_uiAmbientColour = uiAmbientColour; }
	uint32							getAmbientColour(void) { return m_uiAmbientColour; }

	void							setDiffuseColour(uint32 uiDiffuseColour) { m_uiDiffuseColour = uiDiffuseColour; }
	uint32							getDiffuseColour(void) { return m_uiDiffuseColour; }

	void							setSpecularColour(uint32 uiSpecularColour) { m_uiSpecularColour = uiSpecularColour; }
	uint32							getSpecularColour(void) { return m_uiSpecularColour; }

	void							setVertexColours(std::vector<bxa::CVector4ui8>& vecVertexColours); // Remainder is filled with 0xFFFFFFFF until vertex count is reached,
	std::vector<bxa::CVector4ui8>&		getVertexColours(void) { return m_vecVertexColours; }

	void							setTextureCoordinates(std::vector<bxa::CVector2D>& vecTextureCoordinates) { m_vecTextureCoordinates = vecTextureCoordinates; }
	std::vector<bxa::CVector2D>&			getTextureCoordinates(void) { return m_vecTextureCoordinates; }

	void							setVertexIndices(std::vector<bxa::CVector4ui16>& vecVertexIndices) { m_vecVertexIndices = vecVertexIndices; }
	std::vector<bxa::CVector4ui16>&		getVertexIndices(void) { return m_vecVertexIndices; }

	void							setVertexPositions(std::vector<bxa::CVector3D>& vecVertexPositions) { m_vecVertexPositions = vecVertexPositions; }
	std::vector<bxa::CVector3D>&			getVertexPositions(void) { return m_vecVertexPositions; }

	void							setVertexNormals(std::vector<bxa::CVector3D>& vecVertexNormals) { m_vecVertexNormals = vecVertexNormals; }
	std::vector<bxa::CVector3D>&			getVertexNormals(void) { return m_vecVertexNormals; }

	void							setBoundingInfo(bxa::CRWGeometryBoundingInfo& boundingInfo) { m_boundingInfo = boundingInfo; }
	bxa::CRWGeometryBoundingInfo&		getBoundingInfo(void) { return m_boundingInfo; }

private:
	uint32							m_uiFlags;
	uint8							m_ucUVCoordinateCount;
	uint8							m_ucGeometryNativeFlags;
	uint32							m_uiTriangleCount;
	uint32							m_uiVertexCount;
	uint32							m_uiFrameCount;
	
	uint32							m_uiAmbientColour;
	uint32							m_uiDiffuseColour;
	uint32							m_uiSpecularColour;
	
	std::vector<bxa::CVector4ui8>		m_vecVertexColours;
	std::vector<bxa::CVector2D>			m_vecTextureCoordinates;
	std::vector<bxa::CVector4ui16>		m_vecVertexIndices;
	std::vector<bxa::CVector3D>			m_vecVertexPositions;
	std::vector<bxa::CVector3D>			m_vecVertexNormals;

	bxa::CRWGeometryBoundingInfo			m_boundingInfo;
};

#endif