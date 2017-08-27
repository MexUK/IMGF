#pragma once

#include "Type/Types.h"

namespace bxgx
{
	// enums

	// events
	namespace events
	{
		enum EInternalEvent;
	};

	namespace control
	{
		namespace events
		{
			enum EInputEvent;
		};
	};

	// controls
	namespace controls
	{
		namespace components
		{
			enum EControlComponent;
		};
	};

	// styles
	namespace styles
	{
		namespace statuses
		{
			enum EStyleStatus;
		};

		namespace components
		{
			enum EStyleComponent;
		};

		namespace properties
		{
			enum EStyleProperty;
		};

		namespace fragments
		{
			enum EStyleFragment;
		};

		namespace values
		{
			enum EStyleValue;
		};
	};

	// items
	namespace item
	{
		enum ERenderable;

		namespace window
		{
			enum EWindowType;
		};

		namespace layer
		{
			enum ELayerType;
		};
	};

	// class forwards
	class BXGX;

	// functions
	inline BXGX*		get(void);

	// general
	class Control;
	class CScrollBarPool;
	enum EControl;
	enum E2DAxis;

	class TextComponent;

	class CDropDownItem;
	class CGridRow;
	class CGridHeader;
	class CMenuEntry;
	class CTab;

	class CButton;
	class CCheckBox;
	class CDropDown;
	class CGrid;
	class CImage;
	class CMenu;
	class CProgressBar;
	class CRadioButton;
	class CScrollBar;
	class CTabBar;
	class CTextBox;
	class CText;

	class CBXSFormat;

	class CGDIPlus;;

	class CGraphicsLibrary;

	template <class Item>
	class CRectangleItemPlacement;

	class CLayerItem;

	class CLayer;

	class CRectangleRenderable;
	class CRenderable;

	enum EGeometry;
	class CShape;
	enum EShape;

	class C1Point1LengthGeometry;
	class C1Point2LengthGeometry;
	class C2PointGeometry;
	class C3PointGeometry;
	class CNPointGeometry;

	class CCircle;
	class CEllipse;
	class CLine;
	class CPolygon;
	class CRectangle;
	class CSquare;
	class CTriangle;

	class CRenderableBlank;

	class CSizedString;

	class CStyleGroup;
	class CControlStyleGroup;
	class CCustomStyleGroup;

	class CCoordinate;
	class CCoordinateWithSign;
	class CCoordinateExpression;
	class CStyleManager;
	class CStyleManager_MapUtility_Uint32;
	class CStyleManager_MapUtility_CRenderablePointer;

	class CWindow;
};