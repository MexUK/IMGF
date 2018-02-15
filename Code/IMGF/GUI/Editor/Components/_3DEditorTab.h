#pragma once

#include "nsbxcf.h"
#include "nsimgf.h"
#include "Event/EventBindable.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "Type/Vector/Vec2i.h"
#include "3D/OpenGL/OpenGL.h"

class imgf::_3DEditorTab : public imgf::EditorTab
{
public:
	_3DEditorTab(void);

	void					bindEvents(void);
	void					unbindEvents(void);

protected:
	void					updateCamera(void);
	void					resetCamera(void);

private:
	void					onKeyDown(uint16 uiKey);
	void					onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void					onLeftMouseUp(bxcf::Vec2i vecCursorPosition);
	void					onMouseMove(bxcf::Vec2i vecCursorPosition);
	void					onMoveMouseWheel(int16 iRotationDistance);

	bool					isPointOver3D(bxcf::Vec2i& vecPoint);

protected:
	bxcf::OpenGL			m_gl;
	bool					m_bCameraRotationDragActive;
	glm::vec3				m_vecCenterPosition;
	float32					m_fCameraOrbitZRot;
	float32					m_fCameraToCenterRadius;
	float32					m_fMoveAcceleration;
};