#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2u16.h"
#include <string>

class bxgi::CIntermediateTextureMipmap
{
public:
	CIntermediateTextureMipmap(void)
	{
		m_vecSize.x = 0;
		m_vecSize.y = 0;
	};

	void						unload(void) {}

	void						setSize(bxcf::Vec2u16& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u16&				getSize(void) { return m_vecSize; }

	void						setRasterData(std::string& strRasterData) { m_strRasterData = strRasterData; }
	std::string&				getRasterData(void) { return m_strRasterData; }

private:
	bxcf::Vec2u16				m_vecSize;
	std::string					m_strRasterData;
};