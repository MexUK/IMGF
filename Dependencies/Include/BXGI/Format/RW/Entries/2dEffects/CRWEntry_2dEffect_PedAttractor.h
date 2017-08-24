#ifndef CRWEntry_2dEffect_PedAttractor_H
#define CRWEntry_2dEffect_PedAttractor_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxgi::CRWEntry_2dEffect_PedAttractor : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_PedAttractor(void);

	void							unserialize(void);
	void							serialize(void);

	void							setType(int32 iType) { m_iType = iType; }
	int32							getType(void) { return m_iType; }

	void							setRotation(uint8 ucRotationIndex, bxcf::Vec3f& vecRotation) { m_vecRotation[ucRotationIndex] = vecRotation; }
	bxcf::Vec3f&						getRotation(uint8 ucRotationIndex) { return m_vecRotation[ucRotationIndex]; }

	void							setExternalScriptName(std::string& strExternalScriptName) { m_strExternalScriptName = strExternalScriptName; }
	std::string&					getExternalScriptName(void) { return m_strExternalScriptName; }

	void							setPedExistingProbability(int32 iPedExistingProbability) { m_iPedExistingProbability = iPedExistingProbability; }
	int32							getPedExistingProbability(void) { return m_iPedExistingProbability; }

	void							setUnknown1(uint8 ucUnknown1) { m_ucUnknown1 = ucUnknown1; }
	uint8							getUnknown1(void) { return m_ucUnknown1; }

	void							setNotUsed1(uint8 ucNotUsed1) { m_ucNotUsed1 = ucNotUsed1; }
	uint8							getNotUsed1(void) { return m_ucNotUsed1; }

	void							setUnknown2(uint8 ucUnknown2) { m_ucUnknown2 = ucUnknown2; }
	uint8							getUnknown2(void) { return m_ucUnknown2; }

	void							setNotUsed2(uint8 ucNotUsed2) { m_ucNotUsed2 = ucNotUsed2; }
	uint8							getNotUsed2(void) { return m_ucNotUsed2; }

private:
	int32							m_iType;
	bxcf::Vec3f						m_vecRotation[3];
	std::string						m_strExternalScriptName;
	int32							m_iPedExistingProbability;
	uint8							m_ucUnknown1;
	uint8							m_ucNotUsed1;
	uint8							m_ucUnknown2;
	uint8							m_ucNotUsed2;
};

#endif