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
	void					bindEvents(void);
	void					unbindEvents(void);

private:
	void					onKeyDown(uint16 uiKey);
	void					onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void					onMoveMouseWheel(int16 iRotationDistance);

	bool					isPointOver3D(bxcf::Vec2i& vecPoint);

protected:
	bxcf::OpenGL			m_gl;
};