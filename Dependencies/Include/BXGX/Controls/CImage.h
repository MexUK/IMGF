#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include <Gdiplus.h>

class bxgx::CImage : public bxgx::Control
{
public:
	CImage(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);

	void									setImage(Gdiplus::Image *pImage) { m_pImage = pImage; }
	Gdiplus::Image*							getImage(void) { return m_pImage; }

	void									setImageData(std::string& strImageData) { m_strImageData = strImageData; }
	std::string&							getImageData(void) { return m_strImageData; }

private:
	Gdiplus::Image*							m_pImage;
	std::string								m_strImageData;
};