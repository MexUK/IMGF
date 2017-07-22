#ifndef CIntermediateTextureMipmap_H
#define CIntermediateTextureMipmap_H

#include "BXA.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2ui16.h"
#include <string>

class bxa::CIntermediateTextureMipmap
{
public:
	CIntermediateTextureMipmap(void)
	{
		m_vecSize.m_x = 0;
		m_vecSize.m_y = 0;
	};

	void						unload(void) {}

	void						setSize(bxa::CVector2ui16& vecSize) { m_vecSize = vecSize; }
	bxa::CVector2ui16&				getSize(void) { return m_vecSize; }

	void						setRasterData(std::string& strRasterData) { m_strRasterData = strRasterData; }
	std::string&				getRasterData(void) { return m_strRasterData; }

private:
	bxa::CVector2ui16				m_vecSize;
	std::string					m_strRasterData;
};

#endif