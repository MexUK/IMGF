#pragma once

#include "nsbxgi.h"
#include "Type/Vector/Vec3f.h"

struct bxgi::TBounds
{
	float32			m_fRadius;
	bxcf::Vec3f		m_vecCenter;
	bxcf::Vec3f		m_vecMin;
	bxcf::Vec3f		m_vecMax;
};

struct bxgi::TSurface
{
	uint8			m_ucMaterial;
	uint8			m_ucFlag;
	uint8			m_ucBrightness;
	uint8			m_ucLight;
};

struct bxgi::TSphere
{
	float32			m_fRadius;
	bxcf::Vec3f		m_vecCenter;
	TSurface		m_surface;
};

struct bxgi::TBox
{
	bxcf::Vec3f		m_min;
	bxcf::Vec3f		m_max;
	TSurface		m_surface;
};

struct bxgi::TFaceGroup
{
	bxcf::Vec3f		m_min;
	bxcf::Vec3f		m_max;
	uint16			m_startFace;
	uint16			m_endFace;
};

struct bxgi::TVertex : public bxcf::Vec3f
{
};

struct bxgi::TFace
{
	uint32			m_uiA;
	uint32			m_uiB;
	uint32			m_uiC;
	TSurface		m_surface;
};