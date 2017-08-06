#pragma once

#include "Type/Types.h"
#include "Type/String/CString2.h"
#include "Styles/CGUIStyles.h"
#include <string>

class CGUIStyles;
class CGUIManager;

namespace bxgx
{
	// classes
	class CGUIManager;

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

	namespace controls
	{
		const uint32		ANY_CONTROL					= 0;
		const uint32		BUTTON						= 1;
		const uint32		CHECK						= 2;
		const uint32		DROP						= 4;
		const uint32		EDIT						= 8;
		const uint32		IMAGE						= 16;
		const uint32		LIST						= 32;
		const uint32		MENU						= 64;
		const uint32		PROGRESS					= 128;
		const uint32		RADIO						= 256;
		const uint32		SCROLL						= 512;
		const uint32		TAB							= 1024;
		const uint32		TEXT						= 2048;

		namespace components
		{
			const uint32		DEFAULT_CONTROL_COMPONENT	= 4096;
			const uint32		HEADER_ROW					= 8192;
			const uint32		HEADER_CELL					= 16384;
		};
	};

	namespace styles
	{
		namespace statuses
		{
			const uint32		DEFAULT_STATUS				= 32768;
			const uint32		HOVER						= 65536;
			const uint32		HOVER2						= 131072;
			//const uint32		CHECKED						= 131072;
			const uint32		UNCHECKED					= 262144;
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
			const uint32		ALL_STYLE_FRAGMENTS			= 524288;
			const uint32		LEFT						= 1048576;
			const uint32		RIGHT						= 2097152;
			const uint32		TOP							= 4194304;
			const uint32		BOTTOM						= 8388608;

			const uint32		TOP_LEFT					= 1048581;
			const uint32		TOP_RIGHT					= 1048582;
			const uint32		BOTTOM_LEFT					= 1048583;
			const uint32		BOTTOM_RIGHT				= 1048584;
			const uint32		START						= 1048585; // e.g. start colour for gradient
			const uint32		STOP						= 1048586; // e.g. stop colour for gradient

			const uint32		X							= 16777216; // e.g. x align for text
			const uint32		Y							= 33554432; // e.g. y align for text
			const uint32		MIN							= 67108864; // e.g. min spacing for text
			const uint32		MAX							= 134217728; // e.g. max spacing for text
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
		template <typename ...T>
		CGUIStyles*		make(T...); // in CGUIStyles.h
	};
};