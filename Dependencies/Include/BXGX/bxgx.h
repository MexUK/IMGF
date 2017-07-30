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
	namespace event
	{
		// window
		const uint16		WINDOW_GAIN_FOCUS			= 1000;
		const uint16		WINDOW_LOSE_FOCUS			= 1001;

		// mouse
		const uint16		MOUSE_MOVE					= 2000;

		const uint16		MOUSE_LEFT_PRESS			= 2001;
		const uint16		MOUSE_LEFT_RELEASE			= 2002;
		const uint16		MOUSE_DOUBLE_LEFT_RELEASE	= 2003;
		const uint16		MOUSE_DOUBLE_LEFT_HELD		= 2004;

		const uint16		MOUSE_RIGHT_PRESS			= 2100;
		const uint16		MOUSE_RIGHT_RELEASE			= 2101;
		const uint16		MOUSE_DOUBLE_RIGHT_RELEASE	= 2102;
		const uint16		MOUSE_DOUBLE_RIGHT_HELD		= 2103;

		const uint16		MOUSE_WHEEL_MOVE			= 2200;
		const uint16		MOUSE_WHEEL_PRESS			= 2201;
		const uint16		MOUSE_WHEEL_RELEASE			= 2202;
		const uint16		MOUSE_DOUBLE_WHEEL_RELEASE	= 2203;
		const uint16		MOUSE_DOUBLE_WHEEL_HELD		= 2204;

		// key
		const uint16		KEY_PRESS					= 3000;
		const uint16		KEY_RELEASE					= 3001;
		const uint16		KEY_HELD					= 3002;
		const uint16		KEY_DOUBLE_RELEASE			= 3003;
		const uint16		KEY_DOUBLE_HELD				= 3004;
	};
};