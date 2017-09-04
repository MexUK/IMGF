#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"
#include "Format/RW/ERWSection.h"
#include "Partial/RWGeometryBoundingInfo.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4u8.h"
#include "Type/Vector/Vec4u16.h"
#include <string>

class bxgi::IntermediateGeometry;

class bxgi::RWSection_Geometry : public bxgi::RWSection
{
public:
	RWSection_Geometry(void);

	void							unserialize(void);
	void							serialize(void);

	std::string						getTextureDiffuseName(void);

	void							removePrelightning(void);

	bxgi::IntermediateGeometry*	convertToIntermediateGeometry(void);

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

	void							setVertexColours(std::vector<bxcf::Vec4u8>& vecVertexColours); // Remainder is filled with 0xFFFFFFFF until vertex count is reached,
	std::vector<bxcf::Vec4u8>&		getVertexColours(void) { return m_vecVertexColours; }

	void							setTextureCoordinates(std::vector<bxcf::Vec2f>& vecTextureCoordinates) { m_vecTextureCoordinates = vecTextureCoordinates; }
	std::vector<bxcf::Vec2f>&		getTextureCoordinates(void) { return m_vecTextureCoordinates; }

	void							setVertexIndices(std::vector<bxcf::Vec4u16>& vecVertexIndices) { m_vecVertexIndices = vecVertexIndices; }
	std::vector<bxcf::Vec4u16>&		getVertexIndices(void) { return m_vecVertexIndices; }

	void							setVertexPositions(std::vector<bxcf::Vec3f>& vecVertexPositions) { m_vecVertexPositions = vecVertexPositions; }
	std::vector<bxcf::Vec3f>&		getVertexPositions(void) { return m_vecVertexPositions; }

	void							setVertexNormals(std::vector<bxcf::Vec3f>& vecVertexNormals) { m_vecVertexNormals = vecVertexNormals; }
	std::vector<bxcf::Vec3f>&		getVertexNormals(void) { return m_vecVertexNormals; }

	void							setBoundingInfo(bxgi::RWGeometryBoundingInfo& boundingInfo) { m_boundingInfo = boundingInfo; }
	bxgi::RWGeometryBoundingInfo&	getBoundingInfo(void) { return m_boundingInfo; }

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
	
	std::vector<bxcf::Vec4u8>		m_vecVertexColours;
	std::vector<bxcf::Vec2f>		m_vecTextureCoordinates;
	std::vector<bxcf::Vec4u16>		m_vecVertexIndices;
	std::vector<bxcf::Vec3f>		m_vecVertexPositions;
	std::vector<bxcf::Vec3f>		m_vecVertexNormals;

	bxgi::RWGeometryBoundingInfo	m_boundingInfo;
};