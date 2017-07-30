#ifndef CRWEntry_2dEffect_StreetSign_H
#define CRWEntry_2dEffect_StreetSign_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CRWEntry_2dEffect_StreetSign : public bxcf::C2dEffect
{
public:
	CRWEntry_2dEffect_StreetSign(void);

	void							unserialize(void);
	void							serialize(void);

	void							setSize(bxcf::CVector2D& vecSize) { m_vecSize = vecSize; }
	bxcf::CVector2D&						getSize(void) { return m_vecSize; }

	void							setRotation(bxcf::CVector3D& vecRotation) { m_vecRotation = vecRotation; }
	bxcf::CVector3D&						getRotation(void) { return m_vecRotation; }

	void							setFlags(int16 uiFlags) { m_uiFlags = uiFlags; }
	int16							getFlags(void) { return m_uiFlags; }

	void							setText(uint8 uiStringIndex, std::string& strData) { m_strText[uiStringIndex] = strData; }
	std::string&					getText(uint8 uiStringIndex) { return m_strText[uiStringIndex]; }

private:
	bxcf::CVector2D						m_vecSize;
	bxcf::CVector3D						m_vecRotation;
	uint16							m_uiFlags;
	std::string						m_strText[4];
};

#endif