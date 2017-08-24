#ifndef CWDRBlock_VertexData_H
#define CWDRBlock_VertexData_H

#include "bxgi.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CWDRBlock_VertexData
{
public:
	bxcf::Vec3f					m_vecPosition;
	bxcf::Vec3f					m_vecNormals;
	uint32						m_uiColour; // RGBA
	bxcf::Vec2f					m_vecTextureCoordinates;
	float32						m_fNormals2[4];
};

#endif