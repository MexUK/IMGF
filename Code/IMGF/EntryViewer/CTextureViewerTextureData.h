#ifndef CTextureViewerTextureData_H
#define CTextureViewerTextureData_H

#include <Windows.h>
#include <string>

struct CTextureViewerTextureData
{
	bool			isCompletelyDisplayed(void)
	{
		return false;
	};

	void			unload(void) {}

	HBITMAP			m_hBitmap;
	uint32	m_uiWidth;
	uint32	m_uiHeight;
	std::string		m_strDiffuseName;
	std::string		m_strAlphaName;
	uint8	m_ucBPP;
	std::string		m_strTextureFormat;
	RECT			m_rect;
	uint32	m_uiIndex;
	uint8	m_bIsCorrupt : 1;
	uint8	m_bTextureContainsNoMipmaps : 1;
};

#endif