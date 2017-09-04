#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "IntermediateBoundingObject.h"
#include "IntermediateVertexData.h"
#include "IntermediateIndexData.h"
#include <vector>

class bxgi::IntermediateGeometry
{
public:
	IntermediateGeometry(void);

	void									unload(void) {}

	void									setBoundingObject(bxgi::IntermediateBoundingObject *pBoundingObject) { m_pBoundingObject = pBoundingObject; }
	bxgi::IntermediateBoundingObject*			getBoundingObject(void) { return m_pBoundingObject; }

	void									setHasVertexColours(bool bHasVertexColours) { m_bHasVertexColours = bHasVertexColours; }
	bool									doesHaveVertexColours(void) { return m_bHasVertexColours; }

	void									setHasUVTextureCoordinates(bool bHasUVTextureCoordinates) { m_bHasUVTextureCoordinates = bHasUVTextureCoordinates; }
	bool									doesHaveUVTextureCoordinates(void) { return m_bHasUVTextureCoordinates; }

	void									setHasPositions(bool bHasPositions) { m_bHasPositions = bHasPositions; }
	bool									doesHavePositions(void) { return m_bHasPositions; }

	void									setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool									doesHaveNormals(void) { return m_bHasNormals; }

	std::vector<bxgi::IntermediateVertexData>&	getVertices(void) { return m_vecVertices; }

	std::vector<bxgi::IntermediateIndexData>&	getTriangles(void) { return m_vecTriangles; }

private:
	bxgi::IntermediateBoundingObject*			m_pBoundingObject;
	uint8									m_bHasVertexColours : 1;
	uint8									m_bHasUVTextureCoordinates : 1;
	uint8									m_bHasPositions : 1;
	uint8									m_bHasNormals : 1;
	std::vector<bxgi::IntermediateVertexData>	m_vecVertices;
	std::vector<bxgi::IntermediateIndexData>		m_vecTriangles;
};