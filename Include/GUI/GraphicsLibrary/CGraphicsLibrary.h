#ifndef CGraphicsLibrary_H
#define CGraphicsLibrary_H

#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "String/CGUIString.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <gdiplus.h>

class CGUIStyles;

class CGraphicsLibrary
{
public:
	void							init(void);
	void							uninit(void);

	virtual void					drawLine(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawSquare(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareBorder(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareFill(bxa::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawRectangle(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleBorder(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleFill(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawCircle(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleBorder(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleFill(bxa::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawEllipse(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseBorder(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseFill(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawTriangle(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(bxa::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawEquilateralTriangle(bxa::CPoint2D& vecBottomLeftPoint, bxa::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(bxa::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(bxa::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawIsoscelesTriangle(bxa::CPoint2D& vecBaseCenterPoint, bxa::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(bxa::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleBorder(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleFill(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2, bxa::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawPolygon(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonBorder(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonFill(std::vector<bxa::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawText(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, CGUIString& gstrString, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawText(bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, std::string& strText, CGUIStyles *pStyles = nullptr, bxa::CSize2D vecTextSize = bxa::CSize2D(0, 0)) = 0;
	virtual bxa::CSize2D					getTextSize(std::string& strText, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawImage(bxa::CPoint2D& vecPosition, std::string& strImagePath, bxa::CSize2D vecSize = bxa::CSize2D(0, 0)) = 0; // size defaults to image size
	virtual void					drawImage(bxa::CPoint2D& vecPosition, Gdiplus::Image *pImage, bxa::CSize2D vecSize = bxa::CSize2D(0, 0)) = 0; // size defaults to image size
};

#endif