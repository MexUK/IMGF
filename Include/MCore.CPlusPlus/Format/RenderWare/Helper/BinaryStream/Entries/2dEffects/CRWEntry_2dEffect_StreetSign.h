#ifndef CRWEntry_2dEffect_StreetSign_H
#define CRWEntry_2dEffect_StreetSign_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class mcore::CRWEntry_2dEffect_StreetSign : public mcore::C2dEffect
{
public:
	CRWEntry_2dEffect_StreetSign(void);

	void							unserialize(void);
	void							serialize(void);

	void							setSize(mcore::CVector2D& vecSize) { m_vecSize = vecSize; }
	mcore::CVector2D&						getSize(void) { return m_vecSize; }

	void							setRotation(mcore::CVector3D& vecRotation) { m_vecRotation = vecRotation; }
	mcore::CVector3D&						getRotation(void) { return m_vecRotation; }

	void							setFlags(int16 uiFlags) { m_uiFlags = uiFlags; }
	int16							getFlags(void) { return m_uiFlags; }

	void							setText(uint8 uiStringIndex, std::string& strData) { m_strText[uiStringIndex] = strData; }
	std::string&					getText(uint8 uiStringIndex) { return m_strText[uiStringIndex]; }

private:
	mcore::CVector2D						m_vecSize;
	mcore::CVector3D						m_vecRotation;
	uint16							m_uiFlags;
	std::string						m_strText[4];
};

#endif