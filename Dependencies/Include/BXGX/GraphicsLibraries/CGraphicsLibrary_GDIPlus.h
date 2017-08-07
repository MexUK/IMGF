#ifndef CGraphicsLibrary_GDIPlus_H
#define CGraphicsLibrary_GDIPlus_H

#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "String/CGUIString.h"
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <Gdiplus.h>

// Gdiplus::Pen is for lines
// Gdiplus::Brush is for backgrounds and text

class CStyleManager;
class bxcf::CColour;

class CGraphicsLibrary_GDIPlus : public CGraphicsLibrary
{
public:
	CGraphicsLibrary_GDIPlus(void);

	void					init(void);

	void					drawLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2);

	void					drawSquare(bxcf::CPoint2D& vecPosition, uint32 uiSize);
	void					drawSquareBorder(bxcf::CPoint2D& vecPosition, uint32 uiSize);
	void					drawSquareFill(bxcf::CPoint2D& vecPosition, uint32 uiSize);

	void					drawRectangle(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	void					drawRectangleBorder(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	void					drawRectangleFill(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);

	void					drawCircle(bxcf::CPoint2D& vecPosition, float32 fRadius);
	void					drawCircleBorder(bxcf::CPoint2D& vecPosition, float32 fRadius);
	void					drawCircleFill(bxcf::CPoint2D& vecPosition, float32 fRadius);

	void					drawEllipse(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	void					drawEllipseBorder(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	void					drawEllipseFill(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);

	void					drawTriangle(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3);
	void					drawEquilateralTriangle(bxcf::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint);
	void					drawEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	void					drawIsoscelesTriangle(bxcf::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawIsoscelesTriangle(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth);
	void					drawIsoscelesTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	void					drawTriangleBorder(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3);
	void					drawTriangleFill(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3);

	void					drawPolygon(std::vector<bxcf::CPoint2D>& vecPoints);
	void					drawPolygonBorder(std::vector<bxcf::CPoint2D>& vecPoints);
	void					drawPolygonFill(std::vector<bxcf::CPoint2D>& vecPoints);

	void					drawText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIString& gstrString);
	void					drawText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string& strText, bxcf::CSize2D vecTextSize = bxcf::CSize2D(0, 0));
	bxcf::CSize2D			getTextSize(std::string& strText);

	void					drawImage(bxcf::CPoint2D& vecPosition, std::string& strImagePath, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0));
	void					drawImage(bxcf::CPoint2D& vecPosition, Gdiplus::Image *pImage, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0));

	void					setGraphics(Gdiplus::Graphics* pGraphics) { m_pGraphics = pGraphics; }
	Gdiplus::Graphics*		getGraphics(void) { return m_pGraphics; }

	bxcf::CPoint2D			getTextPositionFromStyles(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string& strText, bxcf::CSize2D& vecTextSize);
	uint32					getTextCenterPositionX(std::string& strText, uint32 uiAreaStartX, uint32 uiAreaWidth);
	uint32					getTextCenterPositionY(std::string& strText, uint32 uiAreaStartY, uint32 uiAreaHeight);

private:
	Gdiplus::Pen*			createPenFromStyles(void);
	Gdiplus::Brush*			createBackgroundBrushFromStyles(void);
	Gdiplus::Brush*			createTextBrushFromStyles(void);
	Gdiplus::Font*			getFontFromStyles(void);

	Gdiplus::Point*			getGdiplusPointsFromVectorPoints(std::vector<bxcf::CPoint2D>& vecPoints);
	Gdiplus::Rect			getGdiplusRect(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	Gdiplus::Color			getGdiplusColourFromColour(bxcf::CColour *pColour);

private:
	Gdiplus::Graphics*									m_pGraphics;
	CStyleManager*										m_pStyleManager;
	std::unordered_map<std::string, Gdiplus::Font*>		m_umapFonts;
};

#endif