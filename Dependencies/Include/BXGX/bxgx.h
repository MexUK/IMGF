#pragma once

#include "Type/Types.h"
#include "Type/String/CString2.h"
#include "Styles/CGUIStyles.h"
#include <string>

class CGUIStyles;
class CGUIManager;

namespace bxgx
{
	// functions
	template <typename ...T>
	CGUIStyles*		styles(T...); // in CGUIStyles.h

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
		const uint32		RENDER_BEFORE				= 4000;
		const uint32		RENDER						= 4001;
		const uint32		RENDER_AFTER				= 4002;
	};
};