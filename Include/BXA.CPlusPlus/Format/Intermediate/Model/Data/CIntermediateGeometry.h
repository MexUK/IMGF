#ifndef CIntermediateGeometry_H
#define CIntermediateGeometry_H

#include "BXA.h"
#include "Type/Types.h"
#include "CIntermediateBoundingObject.h"
#include "CIntermediateVertexData.h"
#include "CIntermediateIndexData.h"
#include <vector>

class bxa::CIntermediateGeometry
{
public:
	CIntermediateGeometry(void) :
		m_pBoundingObject(nullptr),
		m_bHasVertexColours(false),
		m_bHasUVTextureCoordinates(false),
		m_bHasPositions(false),
		m_bHasNormals(false)
	{
		bxa::CVector3D vecCenter;
		vecCenter.m_x = 0.0f;
		vecCenter.m_y = 0.0f;
		vecCenter.m_z = 0.0f;
		m_pBoundingObject = new bxa::CIntermediateBoundingObject;
		m_pBoundingObject->setBoundingObjectType(bxa::BOUNDING_OBJECT_TYPE_SPHERE);
		m_pBoundingObject->setCenter(vecCenter);
		m_pBoundingObject->setRadius(0.0f);
		m_pBoundingObject->setHasPositions(false);
		m_pBoundingObject->setHasNormals(false);
	}

	void									unload(void) {}

	void									setBoundingObject(bxa::CIntermediateBoundingObject *pBoundingObject) { m_pBoundingObject = pBoundingObject; }
	bxa::CIntermediateBoundingObject*			getBoundingObject(void) { return m_pBoundingObject; }

	void									setHasVertexColours(bool bHasVertexColours) { m_bHasVertexColours = bHasVertexColours; }
	bool									doesHaveVertexColours(void) { return m_bHasVertexColours; }

	void									setHasUVTextureCoordinates(bool bHasUVTextureCoordinates) { m_bHasUVTextureCoordinates = bHasUVTextureCoordinates; }
	bool									doesHaveUVTextureCoordinates(void) { return m_bHasUVTextureCoordinates; }

	void									setHasPositions(bool bHasPositions) { m_bHasPositions = bHasPositions; }
	bool									doesHavePositions(void) { return m_bHasPositions; }

	void									setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool									doesHaveNormals(void) { return m_bHasNormals; }

	std::vector<bxa::CIntermediateVertexData>&	getVertices(void) { return m_vecVertices; }

	std::vector<bxa::CIntermediateIndexData>&	getTriangles(void) { return m_vecTriangles; }

private:
	bxa::CIntermediateBoundingObject*			m_pBoundingObject;
	uint8									m_bHasVertexColours : 1;
	uint8									m_bHasUVTextureCoordinates : 1;
	uint8									m_bHasPositions : 1;
	uint8									m_bHasNormals : 1;
	std::vector<bxa::CIntermediateVertexData>	m_vecVertices;
	std::vector<bxa::CIntermediateIndexData>		m_vecTriangles;
};

#endif