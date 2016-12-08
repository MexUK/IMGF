#ifndef TShapes_H
#define TShapes_H

#include "mcore.h"
#include "Type/Vector/CVector3D.h"

struct mcore::TBounds
{
	float32			m_fRadius;
	mcore::CVector3D		m_vecCenter;
	mcore::CVector3D		m_vecMin;
	mcore::CVector3D		m_vecMax;
};

struct mcore::TSurface
{
	uint8			m_ucMaterial;
	uint8			m_ucFlag;
	uint8			m_ucBrightness;
	uint8			m_ucLight;
};

struct mcore::TSphere
{
	float32			m_fRadius;
	mcore::CVector3D		m_vecCenter;
	TSurface		m_surface;
};

struct mcore::TBox
{
	mcore::CVector3D		m_min;
	mcore::CVector3D		m_max;
	TSurface		m_surface;
};

struct mcore::TFaceGroup
{
	mcore::CVector3D		m_min;
	mcore::CVector3D		m_max;
	uint16			m_startFace;
	uint16			m_endFace;
};

struct mcore::TVertex : public mcore::CVector3D
{
};

struct mcore::TFace
{
	uint32			m_uiA;
	uint32			m_uiB;
	uint32			m_uiC;
	TSurface		m_surface;
};

#endif