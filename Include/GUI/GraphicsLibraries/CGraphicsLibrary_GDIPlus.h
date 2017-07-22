#ifndef CGraphicsLibrary_GDIPlus_H
#define CGraphicsLibrary_GDIPlus_H

#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "String/CGUIString.h"
#include <vector>
#include <Windows.h>
#include <Gdiplus.h>

// Gdiplus::Pen is for lines
// Gdiplus::Brush is for backgrounds and text

class bxa::CColour;

class CGraphicsLibrary_GDIPlus : public CGraphicsLibrary
{
public:
	CGraphicsLibrary_GDIPlus(void);

	void					drawLine(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr);

	void					drawSquare(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);
	void					drawSquareBorder(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);
	void					drawSquareFill(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);

	void					drawRectangle(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawRectangleBorder(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawRectangleFill(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);

	void					drawCircle(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);
	void					drawCircleBorder(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);
	void					drawCircleFill(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);

	void					drawEllipse(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawEllipseBorder(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawEllipseFill(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);

	void					drawTriangle(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);
	void					drawEquilateralTriangle(bxa::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawEquilateralTriangle(bxa::CPoint2D& vecBottomLeftPoint, bxa::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr);
	void					drawEquilateralTriangle(bxa::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);
	void					drawIsoscelesTriangle(bxa::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawIsoscelesTriangle(bxa::CPoint2D& vecBaseCenterPoint, bxa::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr);
	void					drawIsoscelesTriangle(bxa::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);
	void					drawTriangleBorder(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);
	void					drawTriangleFill(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);

	void					drawPolygon(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);
	void					drawPolygonBorder(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);
	void					drawPolygonFill(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);

	void					drawText(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIString& gstrString, CGUIStyles *pStyles = nullptr);
	void					drawText(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, std::string& strText, CGUIStyles *pStyles = nullptr, bxa::CSize2D vecTextSize = bxa::CSize2D(0, 0));
	bxa::CSize2D					getTextSize(std::string& strText, CGUIStyles *pStyles = nullptr);

	void					drawImage(bxa::CPoint2D& vecPosition, std::string& strImagePath, bxa::CSize2D vecSize = bxa::CSize2D(0, 0));
	void					drawImage(bxa::CPoint2D& vecPosition, Gdiplus::Image *pImage, bxa::CSize2D vecSize = bxa::CSize2D(0, 0));

	void					setGraphics(Gdiplus::Graphics* pGraphics) { m_pGraphics = pGraphics; }
	Gdiplus::Graphics*		getGraphics(void) { return m_pGraphics; }

	bxa::CPoint2D			getTextPositionFromStyles(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, std::string& strText, bxa::CSize2D& vecTextSize, CGUIStyles *pStyles);

private:
	Gdiplus::Pen*			createPenFromStyles(CGUIStyles *pStyles);
	Gdiplus::Brush*			createBackgroundBrushFromStyles(CGUIStyles *pStyles);
	Gdiplus::Brush*			createTextBrushFromStyles(CGUIStyles *pStyles);
	Gdiplus::Font*			createFontFromStyles(CGUIStyles *pStyles);

	Gdiplus::Point*			getGdiplusPointsFromVectorPoints(std::vector<bxa::CPoint2D>& vecPoints);
	Gdiplus::Rect			getGdiplusRect(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize);
	Gdiplus::Color			getGdiplusColourFromColour(bxa::CColour *pColour);

private:
	Gdiplus::Graphics*		m_pGraphics;
};

#endif