#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "String/CSizedString.h"
#include <string>
#include <vector>
#include <Windows.h> // for Gdiplus
#include <gdiplus.h> // for Gdiplus::Image

class bxgx::CGraphicsLibrary
{
public:
	virtual void					init(void);
	virtual void					uninit(void);

	virtual void					drawLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2) = 0;

	virtual void					drawSquare(bxcf::Vec2i& vecPosition, uint32 uiSize) = 0;
	virtual void					drawSquareBorder(bxcf::Vec2i& vecPosition, uint32 uiSize) = 0;
	virtual void					drawSquareFill(bxcf::Vec2i& vecPosition, uint32 uiSize) = 0;

	virtual void					drawRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawRectangleBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawRectangleFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;

	virtual void					drawCircle(bxcf::Vec2i& vecPosition, float32 fRadius) = 0;
	virtual void					drawCircleBorder(bxcf::Vec2i& vecPosition, float32 fRadius) = 0;
	virtual void					drawCircleFill(bxcf::Vec2i& vecPosition, float32 fRadius) = 0;

	virtual void					drawEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawEllipseBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawEllipseFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	
	virtual void					drawTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3) = 0;
	virtual void					drawEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint) = 0;
	virtual void					drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle) = 0;
	virtual void					drawIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection) = 0; // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	virtual void					drawIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth) = 0;
	virtual void					drawIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle) = 0;
	virtual void					drawTriangleBorder(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3) = 0;
	virtual void					drawTriangleFill(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3) = 0;
	
	virtual void					drawPolygon(std::vector<bxcf::Vec2i>& vecPoints) = 0;
	virtual void					drawPolygonBorder(std::vector<bxcf::Vec2i>& vecPoints) = 0;
	virtual void					drawPolygonFill(std::vector<bxcf::Vec2i>& vecPoints) = 0;

	virtual void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, CSizedString& gstrString) = 0;
	virtual void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u vecTextSize = bxcf::Vec2u(0, 0)) = 0;
	virtual bxcf::Vec2u				getTextSize(std::string& strText) = 0;

	virtual void					drawImage(bxcf::Vec2i& vecPosition, std::string& strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0)) = 0; // size defaults to image size
	virtual void					drawImage(bxcf::Vec2i& vecPosition, Gdiplus::Image *pImage, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0)) = 0; // size defaults to image size

	virtual uint32					getTextCenterPositionX(std::string& strText, uint32 uiAreaStartX, uint32 uiAreaWidth) = 0;
	virtual uint32					getTextCenterPositionY(std::string& strText, uint32 uiAreaStartY, uint32 uiAreaHeight) = 0;
};