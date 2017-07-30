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
	virtual void					init(void);
	virtual void					uninit(void);

	virtual void					drawLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawSquare(bxcf::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareBorder(bxcf::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawSquareFill(bxcf::CPoint2D& vecPosition, uint32 uiSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawRectangle(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleBorder(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawRectangleFill(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawCircle(bxcf::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleBorder(bxcf::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawCircleFill(bxcf::CPoint2D& vecPosition, float32 fRadius, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawEllipse(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseBorder(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEllipseFill(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawTriangle(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(bxcf::CPoint2D& vecPosition, float32 fSideLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawEquilateralTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(bxcf::CPoint2D& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection, CGUIStyles *pStyles = nullptr) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawIsoscelesTriangle(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawIsoscelesTriangle(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle = 25.0f, float32 fBaseAngle = 0.0f, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleBorder(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawTriangleFill(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2, bxcf::CPoint2D& vecPoint3, CGUIStyles *pStyles = nullptr) = 0;
	
	virtual void					drawPolygon(std::vector<bxcf::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonBorder(std::vector<bxcf::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawPolygonFill(std::vector<bxcf::CPoint2D>& vecPoints, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, CGUIString& gstrString, CGUIStyles *pStyles = nullptr) = 0;
	virtual void					drawText(bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, std::string& strText, CGUIStyles *pStyles = nullptr, bxcf::CSize2D vecTextSize = bxcf::CSize2D(0, 0)) = 0;
	virtual bxcf::CSize2D					getTextSize(std::string& strText, CGUIStyles *pStyles = nullptr) = 0;

	virtual void					drawImage(bxcf::CPoint2D& vecPosition, std::string& strImagePath, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0)) = 0; // size defaults to image size
	virtual void					drawImage(bxcf::CPoint2D& vecPosition, Gdiplus::Image *pImage, bxcf::CSize2D vecSize = bxcf::CSize2D(0, 0)) = 0; // size defaults to image size

	virtual uint32					getTextCenterPositionX(std::string& strText, uint32 uiAreaStartX, uint32 uiAreaWidth, CGUIStyles *pGUIStyles = nullptr) = 0;
	virtual uint32					getTextCenterPositionY(std::string& strText, uint32 uiAreaStartY, uint32 uiAreaHeight, CGUIStyles *pGUIStyles = nullptr) = 0;

protected:
	int32							resolveXCoordinate(int32 x, CGUIStyles *pStyles = nullptr, uint32 uiIndexX = 0, uint32 uiTextLength = 0);
	int32							resolveYCoordinate(int32 y, CGUIStyles *pStyles = nullptr, uint32 uiIndexY = 0, uint32 uiTextLength = 0);
};

#endif