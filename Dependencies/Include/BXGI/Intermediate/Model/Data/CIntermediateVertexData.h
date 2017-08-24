#ifndef CIntermediateVertexData_H
#define CIntermediateVertexData_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"

class bxgi::CIntermediateVertexData
{
public:
	CIntermediateVertexData(void) :
		m_uiColour(0)
	{
		m_vecPosition.x = 0.0f;
		m_vecPosition.y = 0.0f;
		m_vecPosition.z = 0.0f;
		m_vecNormal.x = 0.0f;
		m_vecNormal.y = 0.0f;
		m_vecNormal.z = 0.0f;
		m_vecTextureCoordinates.x = 0.0f;
		m_vecTextureCoordinates.y = 0.0f;
		m_vecNormal2.x = 0.0f;
		m_vecNormal2.y = 0.0f;
		m_vecNormal2.z = 0.0f;
		m_vecNormal2.w = 0.0f;
	};

	void								setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&							getPosition(void) { return m_vecPosition; }

	void								setNormal(bxcf::Vec3f& vecNormal) { m_vecNormal = vecNormal; }
	bxcf::Vec3f&							getNormal(void) { return m_vecNormal; }

	void								setColour(uint32 uiColour) { m_uiColour = uiColour; }
	uint32								getColour(void) { return m_uiColour; }

	void								setTextureCoordinates(bxcf::Vec2f& vecTextureCoordinates) { m_vecTextureCoordinates = vecTextureCoordinates; }
	bxcf::Vec2f&							getTextureCoordinates(void) { return m_vecTextureCoordinates; }

	void								setNormal2(bxcf::Vec4f& vecNormal2) { m_vecNormal2 = vecNormal2; }
	bxcf::Vec4f&							getNormal2(void) { return m_vecNormal2; }

private:
	bxcf::Vec3f							m_vecPosition;
	bxcf::Vec3f							m_vecNormal;
	uint32								m_uiColour; // RGBA
	bxcf::Vec2f							m_vecTextureCoordinates;
	bxcf::Vec4f							m_vecNormal2;
};

#endif