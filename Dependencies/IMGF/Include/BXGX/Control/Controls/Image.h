#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Base/Control.h"
#include <Gdiplus.h>

class bxgx::ImageObject;

class bxgx::Image : public bxgx::Control
{
public:
	Image(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);

	void									setImageObject(ImageObject *pImageObject) { m_pImageObject = pImageObject; }
	ImageObject*							getImageObject(void) { return m_pImageObject; }

	void									setImageData(std::string& strImageData) { m_strImageData = strImageData; }
	std::string&							getImageData(void) { return m_strImageData; }

private:
	ImageObject*							m_pImageObject;
	std::string								m_strImageData;
};