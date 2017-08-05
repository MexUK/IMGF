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

	namespace controls // bits: 0-7 (8 bits)
	{
		const uint32		ANY_CONTROL					= 0;
		const uint32		BUTTON						= 1;
		const uint32		CHECK						= 2;
		const uint32		DROP						= 3;
		const uint32		EDIT						= 4;
		const uint32		IMAGE						= 5;
		const uint32		LIST						= 6;
		const uint32		MENU						= 7;
		const uint32		PROGRESS					= 8;
		const uint32		RADIO						= 9;
		const uint32		SCROLL						= 10;
		const uint32		TAB							= 11;
		const uint32		TEXT						= 12;

		namespace components // bits: 8-13 (6 bits)
		{
			const uint32		DEFAULT_CONTROL_COMPONENT	= 256;
			const uint32		HEADER_ROW					= 257;
			const uint32		HEADER_CELL					= 258;
		};
	};

	namespace styles
	{
		namespace statuses // bits: 14-19 (6 bits)
		{
			const uint32		DEFAULT_STATUS				= 16384;
			const uint32		HOVER						= 16385;
			const uint32		CHECKED						= 16386;
			const uint32		UNCHECKED					= 16387;
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

		namespace fragments // bits: 20-27 (8 bits)
		{
			const uint32		ALL_STYLE_FRAGMENTS			= 1048576;
			const uint32		LEFT						= 1048577;
			const uint32		RIGHT						= 1048578;
			const uint32		TOP							= 1048579;
			const uint32		BOTTOM						= 1048580;
			const uint32		TOP_LEFT					= 1048581;
			const uint32		TOP_RIGHT					= 1048582;
			const uint32		BOTTOM_LEFT					= 1048583;
			const uint32		BOTTOM_RIGHT				= 1048584;
			const uint32		START						= 1048585; // e.g. start colour for gradient
			const uint32		STOP						= 1048586; // e.g. stop colour for gradient
			const uint32		X							= 1048587; // e.g. x align for text
			const uint32		Y							= 1048588; // e.g. y align for text
			const uint32		MIN							= 1048589; // e.g. min spacing for text
			const uint32		MAX							= 1048590; // e.g. max spacing for text
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
		};

		// functions
		template <typename ...T>
		CGUIStyles*		make(T...); // in CGUIStyles.h
	};
};