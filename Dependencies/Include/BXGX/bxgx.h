#pragma once

#include "Type/Types.h"

namespace bxgx
{
	// classes
	class CGUIManager;

	// functions
	inline CGUIManager*		get(void);

	// events
	namespace events
	{
		// window
		const uint32		WINDOW_GAIN_FOCUS			= 1000;
		const uint32		WINDOW_LOSE_FOCUS			= 1001;

		// mouse
		const uint32		MOUSE_MOVE					= 2000;

		const uint32		MOUSE_LEFT_DOWN				= 2001;
		const uint32		MOUSE_LEFT_UP				= 2002;
		const uint32		MOUSE_DOUBLE_LEFT_DOWN		= 2003;
		const uint32		MOUSE_DOUBLE_LEFT_UP		= 2004;

		const uint32		MOUSE_RIGHT_DOWN			= 2100;
		const uint32		MOUSE_RIGHT_UP				= 2101;
		const uint32		MOUSE_DOUBLE_RIGHT_DOWN		= 2102;
		const uint32		MOUSE_DOUBLE_RIGHT_UP		= 2103;

		const uint32		MOUSE_WHEEL_MOVE			= 2200;
		const uint32		MOUSE_WHEEL_DOWN			= 2201;
		const uint32		MOUSE_WHEEL_UP				= 2202;
		const uint32		MOUSE_DOUBLE_WHEEL_DOWN		= 2203;
		const uint32		MOUSE_DOUBLE_WHEEL_UP		= 2204;

		const uint32		MOUSE_ENTER					= 2300;
		const uint32		MOUSE_EXIT					= 2301;

		// key
		const uint32		KEY_DOWN					= 3000;
		const uint32		KEY_UP						= 3001;
		const uint32		KEY_HELD					= 3002;
		const uint32		KEY_DOUBLE_DOWN				= 3003;
		const uint32		KEY_DOUBLE_UP				= 3004;

		// render
		const uint32		RENDER						= 4000;
		const uint32		RENDER_BEFORE				= 4001;
		const uint32		RENDER_AFTER				= 4002;
	};

	namespace control
	{
		namespace events
		{
			enum EInputEvents;
		};
	};

	namespace controls
	{
		namespace components
		{
			const uint32		DEFAULT_CONTROL_COMPONENT	= 0;
			const uint32		HEADER_ROW					= 1;
			const uint32		HEADER_CELL					= 2;
			const uint32		TAB							= 3;
			const uint32		ICON						= 4;
			const uint32		LIST						= 5;
			const uint32		LIST_ROW					= 6;
			const uint32		ARROW						= 7;
			const uint32		CARET						= 8;
			const uint32		SELECTION					= 9;
			const uint32		ROW							= 10;
			const uint32		CELL						= 11;
			const uint32		INNER_BAR					= 12;
			const uint32		SEEK_BAR					= 13;
		};
	};

	namespace styles
	{
		namespace statuses
		{
			const uint32		DEFAULT_STATUS				= 0;
			const uint32		HOVER						= 1;
			const uint32		HOVER2						= 2;
			const uint32		CHECKED						= 3;
			const uint32		UNCHECKED					= 4;
			const uint32		N1							= 5;
			const uint32		N2							= 6;
			const uint32		SELECTED					= 7;
			const uint32		MAIN_SELECTED				= 8;
		};

		namespace components
		{
			const uint32		FILL						= 0;
			const uint32		LINE						= 1;
			const uint32		TEXT						= 2;
			const uint32		SPACING						= 3;
		};

		namespace properties
		{
			const uint32		COLOUR						= 0;
			const uint32		RADIUS						= 1;
			const uint32		LENGTH						= 2;
			const uint32		FONT						= 3;
			const uint32		WEIGHT						= 4;
			const uint32		STYLE						= 5;
			const uint32		ALIGN						= 6;
			const uint32		STATUS						= 7;
		};

		namespace fragments
		{
			const uint32		ALL_STYLE_FRAGMENTS			= 0;
			const uint32		LEFT						= 1;
			const uint32		RIGHT						= 2;
			const uint32		TOP							= 3;
			const uint32		BOTTOM						= 4;
			const uint32		TOP_LEFT					= 5;
			const uint32		TOP_RIGHT					= 6;
			const uint32		BOTTOM_LEFT					= 7;
			const uint32		BOTTOM_RIGHT				= 8;
			const uint32		START						= 9; // e.g. start colour for gradient
			const uint32		STOP						= 10; // e.g. stop colour for gradient
			const uint32		X							= 11; // e.g. x align for text
			const uint32		Y							= 12; // e.g. y align for text
			const uint32		MIN							= 13; // e.g. min spacing for text
			const uint32		MAX							= 14; // e.g. max spacing for text
		};

		namespace values
		{
			const uint32		BOLD						= 0;
			const uint32		ITALIC						= 1;
			const uint32		UNDERLINE					= 2;
			const uint32		STRIKETHROUGH				= 3;
			const uint32		LEFT						= 4;
			const uint32		RIGHT						= 5;
			const uint32		CENTER						= 6;
			const uint32		TOP							= 7;
			const uint32		BOTTOM						= 8;
		};

		// functions
		//template <typename ...T>
		//CGUIStyles*		make(T...); // in CGUIStyles.h
	};

	namespace item
	{
		const uint32		WINDOW			= 0;
		const uint32		LAYER			= 1;
		const uint32		CONTROL			= 2;
		const uint32		SHAPE			= 3;

		namespace window
		{
			const uint32		TYPE_1			= 0;
		};

		namespace layer
		{
			const uint32		TYPE_1			= 0;
		};
	};
};