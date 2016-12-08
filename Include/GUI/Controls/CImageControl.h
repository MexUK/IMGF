#ifndef CImageControl_H
#define CImageControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include <Gdiplus.h>

class CImageControl : public CGUIControl
{
public:
	CImageControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									render(void);

	void									setImage(Gdiplus::Image *pImage) { m_pImage = pImage; }
	Gdiplus::Image*							getImage(void) { return m_pImage; }

	void									setSize(mcore::CSize2D& vecSize) { m_vecSize = vecSize; }
	mcore::CSize2D&								getSize(void) { return m_vecSize; }

	void									setImageData(std::string& strImageData) { m_strImageData = strImageData; }
	std::string&							getImageData(void) { return m_strImageData; }

private:
	Gdiplus::Image*							m_pImage;
	mcore::CSize2D									m_vecSize;
	std::string								m_strImageData;
};

#endif