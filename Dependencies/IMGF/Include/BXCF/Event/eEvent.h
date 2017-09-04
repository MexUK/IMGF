#ifndef eEvent_H
#define eEvent_H

#include "bxcf.h"

enum bxcf::eEvent
{
	EVENT_UNKNOWN,

	// general - bound to event type EVENT_TYPE_GENERAL
	EVENT_onToolReady,
	EVENT_onTaskProgress,
	EVENT_onParseIMGEntry,
	EVENT_onStoreIMGEntry,
	EVENT_onAddIMGEntry,
	EVENT_onRemoveIMGEntry,
	EVENT_onAddIMGEntryExtension,
	EVENT_onRemoveIMGEntryExtension,

	// window - bound to event type EVENT_TYPE_WINDOW
	EVENT_onLeftMouseDown,
	EVENT_onLeftMouseUp,
	EVENT_onLeftMouseDoubleClick,
	EVENT_onMouseMove,
	EVENT_onKeyDown,
	EVENT_onKeyUp,
	EVENT_onCharacterDown,
	EVENT_onRender,
	EVENT_onRenderBefore,
	EVENT_onRenderAfter,
	EVENT_onResizeWindow,

	// window control base - bound to event type EVENT_TYPE_WINDOW
	EVENT_onControlGainFocus,
	EVENT_onCursorEnterControl,
	EVENT_onCursorLeaveControl,

	// window control derived - bound to event type EVENT_TYPE_WINDOW
	EVENT_onPressButton,
	EVENT_onMarkCheck,
	EVENT_onMarkRadio,
	EVENT_onShowDropList,
	EVENT_onHideDropList,
	EVENT_onStartMovingSeekBar,
	EVENT_onStopMovingSeekBar,
	EVENT_onMoveSeekBar,
	EVENT_onPressTab

	// todo - EVENT_onControlLoseFocus
	// todo - EVENT_onUnmarkCheck
	// todo - EVENT_onUnmarkRadio
};

#endif