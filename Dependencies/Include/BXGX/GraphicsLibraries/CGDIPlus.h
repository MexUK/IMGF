#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "String/CSizedString.h"
#include <vector>
#include <unordered_map>
#include <Windows.h> // for Gdiplus
#include <Gdiplus.h>

// Gdiplus::Pen is for lines
// Gdiplus::Brush is for backgrounds and text

class bxgx::CStyleManager;
class bxcf::CColour;

class bxgx::CGDIPlus : public CGraphicsLibrary
{
public:
	CGDIPlus(void);

	void					init(void);

	void					drawLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);

	void					drawSquare(bxcf::Vec2i& vecPosition, uint32 uiSize);
	void					drawSquareBorder(bxcf::Vec2i& vecPosition, uint32 uiSize);
	void					drawSquareFill(bxcf::Vec2i& vecPosition, uint32 uiSize);

	void					drawRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawRectangleBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawRectangleFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	void					drawCircle(bxcf::Vec2i& vecPosition, float32 fRadius);
	void					drawCircleBorder(bxcf::Vec2i& vecPosition, float32 fRadius);
	void					drawCircleFill(bxcf::Vec2i& vecPosition, float32 fRadius);

	void					drawEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawEllipseBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawEllipseFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	void					drawTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);
	void					drawEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint);
	void					drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	void					drawIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth);
	void					drawIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	void					drawTriangleBorder(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);
	void					drawTriangleFill(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);

	void					drawPolygon(std::vector<bxcf::Vec2i>& vecPoints);
	void					drawPolygonBorder(std::vector<bxcf::Vec2i>& vecPoints);
	void					drawPolygonFill(std::vector<bxcf::Vec2i>& vecPoints);

	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, CSizedString& gstrString);
	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u vecTextSize = bxcf::Vec2u(0, 0));
	bxcf::Vec2u				getTextSize(std::string& strText);

	void					drawImage(bxcf::Vec2i& vecPosition, std::string& strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0));
	void					drawImage(bxcf::Vec2i& vecPosition, Gdiplus::Image *pImage, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0));

	void					setGraphics(Gdiplus::Graphics* pGraphics) { m_pGraphics = pGraphics; }
	Gdiplus::Graphics*		getGraphics(void) { return m_pGraphics; }

	bxcf::Vec2i				getTextPositionFromStyles(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u& vecTextSize);
	uint32					getTextCenterPositionX(std::string& strText, uint32 uiAreaStartX, uint32 uiAreaWidth);
	uint32					getTextCenterPositionY(std::string& strText, uint32 uiAreaStartY, uint32 uiAreaHeight);

private:
	Gdiplus::Pen*			createPenFromStyles(void);
	Gdiplus::Brush*			createBackgroundBrushFromStyles(void);
	Gdiplus::Brush*			createTextBrushFromStyles(void);
	Gdiplus::Font*			getFontFromStyles(void);

	Gdiplus::Point*			getGdiplusPointsFromVectorPoints(std::vector<bxcf::Vec2i>& vecPoints);
	Gdiplus::Rect			getGdiplusRect(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	Gdiplus::Color			getGdiplusColourFromColour(bxcf::CColour *pColour);

private:
	Gdiplus::Graphics*									m_pGraphics;
	CStyleManager*										m_pStyleManager;
	std::unordered_map<std::string, Gdiplus::Font*>		m_umapFonts;
};