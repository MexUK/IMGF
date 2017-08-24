#ifndef CDATCAPSFormat_H
#define CDATCAPSFormat_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"

class bxgi::CDATCAPSFormat : public bxcf::CFormat
{
public:
	CDATCAPSFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
	
	void					setOptimalRasterFormatForTextures_RGBA(uint32 uiOptimalRasterFormatForTextures_RGBA) { m_uiOptimalRasterFormatForTextures_RGBA = uiOptimalRasterFormatForTextures_RGBA; }
	uint32					getOptimalRasterFormatForTextures_RGBA(void) { return m_uiOptimalRasterFormatForTextures_RGBA; }
	
	void					setOptimalRasterFormatForTextures_RGB(uint32 uiOptimalRasterFormatForTextures_RGB) { m_uiOptimalRasterFormatForTextures_RGB = uiOptimalRasterFormatForTextures_RGB; }
	uint32					getOptimalRasterFormatForTextures_RGB(void) { return m_uiOptimalRasterFormatForTextures_RGB; }
	
	void					setOptimalRasterFormatForTextures_Greyscale(uint32 uiOptimalRasterFormatForTextures_Greyscale) { m_uiOptimalRasterFormatForTextures_Greyscale = uiOptimalRasterFormatForTextures_Greyscale; }
	uint32					getOptimalRasterFormatForTextures_Greyscale(void) { return m_uiOptimalRasterFormatForTextures_Greyscale; }
	
	void					setOptimalRasterFormatForTextures_RGBA_Palette256(uint32 uiOptimalRasterFormatForTextures_Palette256) { m_uiOptimalRasterFormatForTextures_Palette256 = uiOptimalRasterFormatForTextures_Palette256; }
	uint32					setOptimalRasterFormatForTextures_RGBA_Palette256(void) { return m_uiOptimalRasterFormatForTextures_Palette256; }
	
private:
	uint32					m_uiOptimalRasterFormatForTextures_RGBA;
	uint32					m_uiOptimalRasterFormatForTextures_RGB;
	uint32					m_uiOptimalRasterFormatForTextures_Greyscale;
	uint32					m_uiOptimalRasterFormatForTextures_Palette256;
};

#endif