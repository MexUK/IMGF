#include "_3DEditorTab.h"
#include "Event/EInternalEvent.h"
#include "BXGX.h"

using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

// event binding
void					_3DEditorTab::bindEvents(void)
{
	bindEvent(KEY_DOWN, &_3DEditorTab::onKeyDown);
	bindEvent(LEFT_MOUSE_DOWN, &_3DEditorTab::onLeftMouseDown);
	bindEvent(MOVE_MOUSE_WHEEL, &_3DEditorTab::onMoveMouseWheel);
}

void					_3DEditorTab::unbindEvents(void)
{
	unbindEvent(KEY_DOWN, &_3DEditorTab::onKeyDown);
	unbindEvent(LEFT_MOUSE_DOWN, &_3DEditorTab::onLeftMouseDown);
	unbindEvent(MOVE_MOUSE_WHEEL, &_3DEditorTab::onMoveMouseWheel);
}

// event callbacks
void					_3DEditorTab::onKeyDown(uint16 uiKey)
{
	if (!isPointOver3D(BXGX::get()->getCursorPosition()))
	{
		return;
	}

	bool bControlKey = (GetKeyState(VK_CONTROL) & 0x8000) == 0x8000;
	bool bShiftKey = (GetKeyState(VK_SHIFT) & 0x8000) == 0x8000;

	float32 fMoveRadius;
	if (bShiftKey)
	{
		fMoveRadius = 1.0f;
	}
	else
	{
		fMoveRadius = 0.1f;
	}

	switch (uiKey)
	{
	case VK_UP:
	case 'W':
		if (bControlKey)
		{
			m_gl.moveCameraZ(fMoveRadius);
		}
		else
		{
			m_gl.moveCameraXY(0.0f, -fMoveRadius);
		}
		break;
	case VK_DOWN:
	case 'S':
		if (bControlKey)
		{
			m_gl.moveCameraZ(-fMoveRadius);
		}
		else
		{
			m_gl.moveCameraXY(0.0f, fMoveRadius);
		}
		break;
	case VK_LEFT:
	case 'A':
		m_gl.moveCameraXY(-90.0f, -fMoveRadius);
		break;
	case VK_RIGHT:
	case 'D':
		m_gl.moveCameraXY(-90.0f, fMoveRadius);
		break;
	}

	getLayer()->getWindow()->render();
}

void					_3DEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
	if (!isPointOver3D(BXGX::get()->getCursorPosition()))
	{
		return;
	}

	// todo

	getLayer()->getWindow()->render();
}

void					_3DEditorTab::onMoveMouseWheel(int16 iRotationDistance)
{
	if (!isPointOver3D(BXGX::get()->getCursorPosition()))
	{
		return;
	}

	float32 fMouseWheelScrollMultiplier = 1.2f;
	int iDelta = -(iRotationDistance / WHEEL_DELTA);
	m_gl.zoomCamera((float32)iDelta * fMouseWheelScrollMultiplier);

	getLayer()->getWindow()->render();
}

// point testing
bool					_3DEditorTab::isPointOver3D(Vec2i& vecPoint)
{
	return Math::isPointInRectangle(vecPoint,  m_gl.getRenderPosition(), m_gl.getRenderSize());
}