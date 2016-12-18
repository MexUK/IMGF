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

class mcore::CColour;

class CGraphicsLibrary_GDIPlus : public CGraphicsLibrary
{
public:
	CGraphicsLibrary_GDIPlus(void);

	void					drawLine(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr);

	void					drawSquare(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);
	void					drawSquareBorder(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);
	void					drawSquareFill(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr);

	void					drawRectangle(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawRectangleBorder(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawRectangleFill(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);

	void					drawCircle(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);
	void					drawCircleBorder(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);
	void					drawCircleFill(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr);

	void					drawEllipse(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawEllipseBorder(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);
	void					drawEllipseFill(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr);

	void					drawTriangle(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);
	void					drawEquilateralTriangle(mcore::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, mcore::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr);
	void					drawEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);
	void					drawIsoscelesTriangle(mcore::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void					drawIsoscelesTriangle(mcore::CPoint2D& vecBaseCenterPoint, mcore::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr);
	void					drawIsoscelesTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr);
	void					drawTriangleBorder(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);
	void					drawTriangleFill(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr);

	void					drawPolygon(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);
	void					drawPolygonBorder(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);
	void					drawPolygonFill(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr);

	void					drawText(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIString& gstrString, CGUIStyles *pStyles = nullptr);
	void					drawText(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string& strText, CGUIStyles *pStyles = nullptr, mcore::CSize2D vecTextSize = mcore::CSize2D(0, 0));
	mcore::CSize2D					getTextSize(std::string& strText, CGUIStyles *pStyles = nullptr);

	void					drawImage(mcore::CPoint2D& vecPosition, std::string& strImagePath, mcore::CSize2D vecSize = mcore::CSize2D(0, 0));
	void					drawImage(mcore::CPoint2D& vecPosition, Gdiplus::Image *pImage, mcore::CSize2D vecSize = mcore::CSize2D(0, 0));

	void					setGraphics(Gdiplus::Graphics* pGraphics) { m_pGraphics = pGraphics; }
	Gdiplus::Graphics*		getGraphics(void) { return m_pGraphics; }

	mcore::CPoint2D			getTextPositionFromStyles(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string& strText, mcore::CSize2D& vecTextSize, CGUIStyles *pStyles);

private:
	Gdiplus::Pen*			createPenFromStyles(CGUIStyles *pStyles);
	Gdiplus::Brush*			createBackgroundBrushFromStyles(CGUIStyles *pStyles);
	Gdiplus::Brush*			createTextBrushFromStyles(CGUIStyles *pStyles);
	Gdiplus::Font*			createFontFromStyles(CGUIStyles *pStyles);

	Gdiplus::Point*			getGdiplusPointsFromVectorPoints(std::vector<mcore::CPoint2D>& vecPoints);
	Gdiplus::Rect			getGdiplusRect(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize);
	Gdiplus::Color			getGdiplusColourFromColour(mcore::CColour *pColour);

private:
	Gdiplus::Graphics*		m_pGraphics;
};

#endif