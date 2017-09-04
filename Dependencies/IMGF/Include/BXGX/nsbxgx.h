#pragma once

#include "Type/Types.h"

namespace bxgx
{
	// enums

	// events
	namespace events
	{
		enum EInternalEvent;
		enum EInputEvent;
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
		enum ERenderItem;

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
	enum EControl;

	class TextComponent;
	class ScrollBarPool;

	class DropDownItem;
	class GridRow;
	class GridHeader;
	class MenuItem;
	class Tab;

	class Button;
	class CheckBox;
	class DropDown;
	class Grid;
	class Image;
	class Menu;
	class ProgressBar;
	class RadioButton;
	class ScrollBar;
	class TabBar;
	class TextBox;
	class Text;

	class BXSFormat;

	class GDIPlus;
	class D3D8;

	class GraphicsLibrary;
	class ImageObject;

	template <class Item>
	class RectangleItemPlacement;

	class LayerItem;

	class Layer;

	class RectangleItem;
	class RenderItem;

	enum EGeometry;
	class Shape;
	enum EShape;

	class _1Point1LengthGeometry;
	class _1Point2LengthGeometry;
	class _2PointGeometry;
	class _3PointGeometry;
	class NPointGeometry;

	class Circle;
	class Ellipse;
	class Line;
	class Polygon;
	class Rectangle;
	class Square;
	class Triangle;

	class RenderItemBlank;

	class SizedString;

	class StyleGroup;
	class ControlStyleGroup;
	class CustomStyleGroup;

	class Coordinate;
	class CoordinateWithSign;
	class CoordinateExpression;
	class StyleManager;
	class StyleManager_MapUtility_Uint32;
	class StyleManager_MapUtility_RenderItemPointer;

	class Window;
};