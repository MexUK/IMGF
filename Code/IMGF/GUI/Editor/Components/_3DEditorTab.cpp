#include "_3DEditorTab.h"
#include "Event/EInternalEvent.h"
#include "BXGX.h"
#include "Static/Math.h"
#include "GUI/Editor/Base/Editor.h"

using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

_3DEditorTab::_3DEditorTab(void) :
	m_fCameraOrbitZRot(135.0f),
	m_bCameraRotationDragActive(false),
	m_fMoveAcceleration(0.1f)
{
}

// event binding
void					_3DEditorTab::bindEvents(void)
{
	bindWindowEvent(KEY_DOWN, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onKeyDown);
	bindWindowEvent(LEFT_MOUSE_DOWN, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onLeftMouseDown);
	bindWindowEvent(LEFT_MOUSE_UP, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onLeftMouseUp);
	bindWindowEvent(MOVE_MOUSE, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onMouseMove, -5);
	bindWindowEvent(MOVE_MOUSE_WHEEL, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onMoveMouseWheel);
}

void					_3DEditorTab::unbindEvents(void)
{
	unbindWindowEvent(KEY_DOWN, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onKeyDown);
	unbindWindowEvent(LEFT_MOUSE_DOWN, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onLeftMouseDown);
	unbindWindowEvent(LEFT_MOUSE_UP, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onLeftMouseUp);
	unbindWindowEvent(MOVE_MOUSE, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onMouseMove);
	unbindWindowEvent(MOVE_MOUSE_WHEEL, (uint32)getEditor()->getMainWindow(), &_3DEditorTab::onMoveMouseWheel);
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
		fMoveRadius = m_fMoveAcceleration;
	}
	else
	{
		fMoveRadius = m_fMoveAcceleration;
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
	case VK_SPACE:
		resetCamera();
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

	m_bCameraRotationDragActive = true;
}

void					_3DEditorTab::onLeftMouseUp(Vec2i vecCursorPosition)
{
	if (!m_bCameraRotationDragActive)
	{
		return;
	}
	
	m_bCameraRotationDragActive = false;
}

void					_3DEditorTab::onMouseMove(Vec2i vecCursorPosition)
{
	if (!m_bCameraRotationDragActive)
	{
		return;
	}

	Vec2i& vecCursorDiff = BXGX::get()->getCursorMoveDifference();

	m_fCameraOrbitZRot = Math::limitAngle(m_fCameraOrbitZRot + (float32)vecCursorDiff.x);
	m_gl.getCameraRotation().z = m_fCameraOrbitZRot;
	m_gl.updateCameraMatrix();
	//updateCamera();

	Events::setEventCancelled();

	getLayer()->getWindow()->render();
}

void					_3DEditorTab::onMoveMouseWheel(int16 iRotationDistance)
{
	if (!isPointOver3D(BXGX::get()->getCursorPosition()))
	{
		return;
	}

	float32 fMouseWheelScrollMultiplier = 0.05f;
	int iDelta = iRotationDistance / WHEEL_DELTA;
	float32 fScrollOffset = (float32)iDelta * fMouseWheelScrollMultiplier;

	m_fMoveAcceleration = Math::limit(m_fMoveAcceleration + fScrollOffset, -1000.0f, 1000.0f);
	//m_gl.zoomCamera(fScrollOffset);

	getLayer()->getWindow()->render();
}

// point testing
bool					_3DEditorTab::isPointOver3D(Vec2i& vecPoint)
{
	return Math::isPointInRectangle(vecPoint,  m_gl.getRenderPosition(), m_gl.getRenderSize());
}

// camera
void					_3DEditorTab::updateCamera(void)
{
	glm::vec2 vecCameraPosOffset = Math::getCartesianFromPolarGLM(m_fCameraToCenterRadius, Math::convertDegreesToRadians(m_fCameraOrbitZRot));
	glm::vec3 vecCameraPos = m_vecCenterPosition + glm::vec3(vecCameraPosOffset.x, vecCameraPosOffset.y, 3.0f);

	m_gl.setCameraPosition(vecCameraPos);
	m_gl.setCameraLookAt(m_vecCenterPosition);
}

void					_3DEditorTab::resetCamera(void)
{
	updateCamera();
	m_fMoveAcceleration = 0.1f;
}