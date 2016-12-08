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

	virtual void					drawLine(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawSquare(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareBorder(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareFill(mcore::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawRectangle(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleBorder(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleFill(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawCircle(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleBorder(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleFill(mcore::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawEllipse(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseBorder(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseFill(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawTriangle(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(mcore::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, mcore::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(mcore::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawIsoscelesTriangle(mcore::CPoint2D& vecBaseCenterPoint, mcore::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(mcore::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleBorder(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleFill(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2, mcore::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawPolygon(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonBorder(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonFill(std::vector<mcore::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawText(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, CGUIString& gstrString, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawText(mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, std::string& strText, CGUIStyles *pStyles = nullptr, mcore::CSize2D vecTextSize = mcore::CSize2D(0, 0)) = 0;
	virtual mcore::CSize2D					getTextSize(std::string& strText, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawImage(mcore::CPoint2D& vecPosition, std::string& strImagePath, mcore::CSize2D vecSize = mcore::CSize2D(0, 0)) = 0; // size defaults to image size
	virtual void					drawImage(mcore::CPoint2D& vecPosition, Gdiplus::Image *pImage, mcore::CSize2D vecSize = mcore::CSize2D(0, 0)) = 0; // size defaults to image size
};

#endif