#pragma once

#include "Type/Types.h"

namespace bxgx
{
	// classes
	class BXGXManager;

	// functions
	inline BXGXManager*		get(void);

	// events
	namespace events
	{
		enum EInternalEvent;
	};

	namespace control
	{
		namespace events
		{
			enum EInputEvents;
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
};