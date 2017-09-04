#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "String/SizedString.h"
#include "Event/EventBindable.h"
#include <string>
#include <vector>
#include <Windows.h> // temp - for Gdiplus
#include <gdiplus.h> // temp - for Gdiplus::Image

class bxgx::Window;
class bxgx::StyleManager;
class bxgx::ImageObject;

class bxgx::GraphicsLibrary : public bxcf::EventBindable
{
public:
	GraphicsLibrary(void);

	virtual void					init(void);
	virtual void					uninit(void);

	virtual void					onBeginRender(bxcf::Vec2u& vecBitmapSize) = 0;
	virtual void					onResizeWindow(bxcf::Vec2i& vecSizeDifference) = 0;
	virtual void					onRenderRectangleArea(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					onEndRender(void) = 0;

	void							setWindow(Window *pWindow) { m_pWindow = pWindow; }
	Window*							getWindow(void) { return m_pWindow; }

	void							setStyleManager(StyleManager *pStyleManager) { m_pStyleManager = pStyleManager; }
	StyleManager*					getStyleManager(void) { return m_pStyleManager; }

	virtual void					drawLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2) = 0;

	void							drawSquare(bxcf::Vec2i& vecPosition, uint32 uiSize);
	void							drawSquareBorder(bxcf::Vec2i& vecPosition, uint32 uiSize);
	void							drawSquareFill(bxcf::Vec2i& vecPosition, uint32 uiSize);

	void							drawRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	virtual void					drawRectangleBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawRectangleFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;

	void							drawCircle(bxcf::Vec2i& vecPosition, float32 fRadius);
	virtual void					drawCircleBorder(bxcf::Vec2i& vecPosition, float32 fRadius) = 0;
	virtual void					drawCircleFill(bxcf::Vec2i& vecPosition, float32 fRadius) = 0;

	void							drawEllipse(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	virtual void					drawEllipseBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	virtual void					drawEllipseFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) = 0;
	
	void							drawTriangle(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);
	void							drawEquilateralTriangle(bxcf::Vec2i& vecPosition, float32 fSideLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void							drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint);
	void							drawEquilateralTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	void							drawIsoscelesTriangle(bxcf::Vec2i& vecPosition, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection); // [parameter uiPointingDirection] Left=1,Top=2,Right=3,Bottom=4,TopLeft=5,TopRight=6,BottomRight=7,BottomLeft=8
	void							drawIsoscelesTriangle(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth);
	void							drawIsoscelesTriangle(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	void							drawTriangleBorder(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);
	void							drawTriangleFill(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2, bxcf::Vec2i& vecPoint3);
	
	void							drawPolygon(std::vector<bxcf::Vec2i>& vecPoints);
	virtual void					drawPolygonBorder(std::vector<bxcf::Vec2i>& vecPoints) = 0;
	virtual void					drawPolygonFill(std::vector<bxcf::Vec2i>& vecPoints) = 0;

	virtual void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, SizedString& gstrString) = 0;
	virtual void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u vecTextSize = bxcf::Vec2u(0, 0)) = 0;
	virtual bxcf::Vec2u				getTextSize(std::string& strText) = 0;

	virtual bxgx::ImageObject*		createImageObject(std::string& strFilePath) = 0;
	virtual void					drawImage(bxcf::Vec2i& vecPosition, std::string& strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0)) = 0; // size defaults to image size
	virtual void					drawImage(bxcf::Vec2i& vecPosition, ImageObject *pImageObject, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0)) = 0; // size defaults to image size

	uint32							getTextCenterPositionX(std::string& strText, uint32 uiAreaStartX, uint32 uiAreaWidth);
	uint32							getTextCenterPositionY(std::string& strText, uint32 uiAreaStartY, uint32 uiAreaHeight);

protected:
	Window*							m_pWindow;
	StyleManager*					m_pStyleManager;
};