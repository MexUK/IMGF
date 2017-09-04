#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "String/SizedString.h"
#include <vector>
#include <unordered_map>
#include <Windows.h> // for Gdiplus
#include <Gdiplus.h>

// Gdiplus::Pen is for lines
// Gdiplus::Brush is for backgrounds and text

class bxgx::StyleManager;
class bxcf::Colour;

class bxgx::GDIPlus : public GraphicsLibrary
{
public:
	GDIPlus(void);

	void					init(void);

	void					onBeginRender(bxcf::Vec2u& vecBitmapSize);
	void					onResizeWindow(bxcf::Vec2i& vecSizeDifference) {}
	void					onRenderRectangleArea(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					onEndRender(void);

	void					drawLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);

	void					drawRectangleBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawRectangleFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	void					drawCircleBorder(bxcf::Vec2i& vecPosition, float32 fRadius);
	void					drawCircleFill(bxcf::Vec2i& vecPosition, float32 fRadius);

	void					drawEllipseBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawEllipseFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	void					drawPolygonBorder(std::vector<bxcf::Vec2i>& vecPoints);
	void					drawPolygonFill(std::vector<bxcf::Vec2i>& vecPoints);

	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, SizedString& sizedString);
	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u vecTextSize = bxcf::Vec2u(0, 0));
	bxcf::Vec2u				getTextSize(std::string& strText);

	ImageObject*			createImageObject(std::string& strFilePath);
	void					drawImage(bxcf::Vec2i& vecPosition, std::string& strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0));
	void					drawImage(bxcf::Vec2i& vecPosition, ImageObject *pImageObject, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0));

	void					setGraphics(Gdiplus::Graphics* pGraphics) { m_pGraphics = pGraphics; }
	Gdiplus::Graphics*		getGraphics(void) { return m_pGraphics; }

	bxcf::Vec2i				getTextPositionFromStyles(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u& vecTextSize);

private:
	Gdiplus::Pen*			createPenFromStyles(void);
	Gdiplus::Brush*			createBackgroundBrushFromStyles(void);
	Gdiplus::Brush*			createTextBrushFromStyles(void);
	Gdiplus::Font*			getFontFromStyles(void);

	Gdiplus::Point*			getGdiplusPointsFromVectorPoints(std::vector<bxcf::Vec2i>& vecPoints);
	Gdiplus::Rect			getGdiplusRect(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	Gdiplus::Color			getGdiplusColourFromColour(bxcf::Colour *pColour);

private:
	Gdiplus::Graphics*									m_pGraphics;
	
	PAINTSTRUCT											m_ps;
	HDC													m_hdc;
	HDC													m_hdcMem;
	HBITMAP												m_hbmMem;
	HANDLE												m_hOld;

	std::unordered_map<std::string, Gdiplus::Font*>		m_umapFonts;
};