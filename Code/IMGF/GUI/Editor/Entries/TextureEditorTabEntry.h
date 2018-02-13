#pragma once

#include "nsimgf.h"
////////#include <Windows.h>
#include <string>

struct imgf::TextureEditorTabEntry
{
	bool			isCompletelyDisplayed(void)
	{
		return false;
	};

	void			unload(void) {}

	HBITMAP			m_hDiffuseBitmap;
	HBITMAP			m_hAlphaBitmap;
	uint32			m_uiWidth;
	uint32			m_uiHeight;
	std::string		m_strDiffuseName;
	std::string		m_strAlphaName;
	uint8			m_ucBPP;
	std::string		m_strTextureFormat;
	RECT			m_rect;
	uint32			m_uiIndex;
	uint8			m_bIsCorrupt					: 1;
	uint8			m_bTextureContainsNoMipmaps		: 1;
	uint8			m_bIsActive						: 1;
};