#ifndef TShapes_H
#define TShapes_H

#include "BXA.h"
#include "Type/Vector/CVector3D.h"

struct bxa::TBounds
{
	float32			m_fRadius;
	bxa::CVector3D		m_vecCenter;
	bxa::CVector3D		m_vecMin;
	bxa::CVector3D		m_vecMax;
};

struct bxa::TSurface
{
	uint8			m_ucMaterial;
	uint8			m_ucFlag;
	uint8			m_ucBrightness;
	uint8			m_ucLight;
};

struct bxa::TSphere
{
	float32			m_fRadius;
	bxa::CVector3D		m_vecCenter;
	TSurface		m_surface;
};

struct bxa::TBox
{
	bxa::CVector3D		m_min;
	bxa::CVector3D		m_max;
	TSurface		m_surface;
};

struct bxa::TFaceGroup
{
	bxa::CVector3D		m_min;
	bxa::CVector3D		m_max;
	uint16			m_startFace;
	uint16			m_endFace;
};

struct bxa::TVertex : public bxa::CVector3D
{
};

struct bxa::TFace
{
	uint32			m_uiA;
	uint32			m_uiB;
	uint32			m_uiC;
	TSurface		m_surface;
};

#endif