#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/E2DFXType.h"
#include "Type/Vector/Vec3f.h"

class bxgi::_2dEffect;

class bxgi::_2dEffect
{
public:
	_2dEffect(E2DFXType E2DFXTypeValue);

	void							unload(void) {}
	
	virtual void					unserialize(void)	= 0;
	virtual void					serialize(void)		= 0;
	
	static bxgi::_2dEffect*				createRW2dEffect(E2DFXType E2DFXTypeValue);
	
	void							setDataSize(uint32 uiDataSize) { m_uiDataSize = uiDataSize; }
	uint32							getDataSize(void) { return m_uiDataSize; }

	void							setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&						getPosition(void) { return m_vecPosition; }

	void							set2DFXType(E2DFXType E2DFXTypeValue) { m_E2DFXType = E2DFXTypeValue; }
	E2DFXType						get2DFXType(void) { return m_E2DFXType; }

protected:
	uint32							m_uiDataSize;

private:
	bxcf::Vec3f						m_vecPosition;
	E2DFXType						m_E2DFXType;
};