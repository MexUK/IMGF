#ifndef TShapes_H
#define TShapes_H

#include "bxcf.h"
#include "Type/Vector/CVector3D.h"

struct bxcf::TBounds
{
	float32			m_fRadius;
	bxcf::CVector3D		m_vecCenter;
	bxcf::CVector3D		m_vecMin;
	bxcf::CVector3D		m_vecMax;
};

struct bxcf::TSurface
{
	uint8			m_ucMaterial;
	uint8			m_ucFlag;
	uint8			m_ucBrightness;
	uint8			m_ucLight;
};

struct bxcf::TSphere
{
	float32			m_fRadius;
	bxcf::CVector3D		m_vecCenter;
	TSurface		m_surface;
};

struct bxcf::TBox
{
	bxcf::CVector3D		m_min;
	bxcf::CVector3D		m_max;
	TSurface		m_surface;
};

struct bxcf::TFaceGroup
{
	bxcf::CVector3D		m_min;
	bxcf::CVector3D		m_max;
	uint16			m_startFace;
	uint16			m_endFace;
};

struct bxcf::TVertex : public bxcf::CVector3D
{
};

struct bxcf::TFace
{
	uint32			m_uiA;
	uint32			m_uiB;
	uint32			m_uiC;
	TSurface		m_surface;
};

#endif