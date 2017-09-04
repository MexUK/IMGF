#pragma once

#include "nsbxgx.h"
#include <Windows.h> // for Gdiplus
#include <Gdiplus.h>

class bxgx::ImageObject
{
public:
	ImageObject(void);

public:
	Gdiplus::Image*		m_pGDIPlusImage;
};