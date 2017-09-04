#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/_2dEffect.h"
#include "Type/Vector/Vec2u8.h"
#include "Type/Vector/Vec3u8.h"
#include <string>

class bxgi::RWEntry_2dEffect_Light : public bxgi::_2dEffect
{
public:
	RWEntry_2dEffect_Light(void);

	void							unserialize(void);
	void							serialize(void);

	void							setColor(uint32 uiColor) { m_uiColor = uiColor; }
	uint32							getColor(void) { return m_uiColor; }

	void							setCoronaFarClip(float32 fCoronaFarClip) { m_fCoronaFarClip = fCoronaFarClip; }
	float32							getCoronaFarClip(void) { return m_fCoronaFarClip; }

	void							setPointlightRange(float32 fPointlightRange) { m_fPointlightRange = fPointlightRange; }
	float32							getPointlightRange(void) { return m_fPointlightRange; }

	void							setCoronaSize(float32 fCoronaSize) { m_fCoronaSize = fCoronaSize; }
	float32							getCoronaSize(void) { return m_fCoronaSize; }

	void							setShadowSize(float32 fShadowSize) { m_fShadowSize = fShadowSize; }
	float32							getShadowSize(void) { return m_fShadowSize; }

	void							setCoronaShowMode(uint8 ucCoronaShowMode) { m_ucCoronaShowMode = ucCoronaShowMode; }
	uint8							getCoronaShowMode(void) { return m_ucCoronaShowMode; }

	void							setCoronaEnableReflection(uint8 ucCoronaEnableReflection) { m_ucCoronaEnableReflection = ucCoronaEnableReflection; }
	uint8							getCoronaEnableReflection(void) { return m_ucCoronaEnableReflection; }

	void							setCoronaFlareType(uint8 ucCoronaFlareType) { m_ucCoronaFlareType = ucCoronaFlareType; }
	uint8							getCoronaFlareType(void) { return m_ucCoronaFlareType; }

	void							setShadowColorMultiplier(uint8 ucShadowColorMultiplier) { m_ucShadowColorMultiplier = ucShadowColorMultiplier; }
	uint8							getShadowColorMultiplier(void) { return m_ucShadowColorMultiplier; }

	void							setFlags1(uint8 ucFlags1) { m_ucFlags1 = ucFlags1; }
	uint8							getFlags1(void) { return m_ucFlags1; }

	void							setCoronaTexName(std::string& strCoronaTexName) { m_strCoronaTexName = strCoronaTexName; }
	std::string&					getCoronaTexName(void) { return m_strCoronaTexName; }

	void							setShadowTexName(std::string& strShadowTexName) { m_strShadowTexName = strShadowTexName; }
	std::string&					getShadowTexName(void) { return m_strShadowTexName; }

	void							setShadowZDistance(uint8 ucShadowZDistance) { m_ucShadowZDistance = ucShadowZDistance; }
	uint8							getShadowZDistance(void) { return m_ucShadowZDistance; }

	void							setFlags2(uint8 ucFlags2) { m_ucFlags2 = ucFlags2; }
	uint8							getFlags2(void) { return m_ucFlags2; }

	void							setLookDirection(bxcf::Vec3u8& vecLookDirection) { m_vecLookDirection = vecLookDirection; }
	bxcf::Vec3u8&					getLookDirection(void) { return m_vecLookDirection; }

	void							setPadding(bxcf::Vec2u8& vecPadding) { m_vecPadding = vecPadding; }
	bxcf::Vec2u8&					getPadding(void) { return m_vecPadding; }

private:
	uint32							m_uiColor;
	float32							m_fCoronaFarClip;
	float32							m_fPointlightRange;
	float32							m_fCoronaSize;
	float32							m_fShadowSize;
	uint8							m_ucCoronaShowMode;
	uint8							m_ucCoronaEnableReflection;
	uint8							m_ucCoronaFlareType;
	uint8							m_ucShadowColorMultiplier;
	uint8							m_ucFlags1;
	std::string						m_strCoronaTexName;
	std::string						m_strShadowTexName;
	uint8							m_ucShadowZDistance;
	uint8							m_ucFlags2;
	bxcf::Vec3u8					m_vecLookDirection;
	bxcf::Vec2u8					m_vecPadding;
};