#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Type/Vector/Vec3f.h"

#include "GL/glew.h"
#include "GL/wglew.h"
#include <Windows.h>

void						perspectiveGL_ModelEditor(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar); // todo - namespace - duplicated too

class imgf::ModelEditorTab : public imgf::EditorTab
{
public:
	ModelEditorTab(void);

	void						addControls(void);
	void						initControls(void);
	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onMouseWheelMove2(int16 iRotationDistance);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						render_Type1(void);

	void						render(void);
	void						render3D(void);
	void						update3DRenderSize(bxcf::Vec2u& vecRenderSize);
	void						renderCamera(void);
	void						renderAxis(void);
	void						renderModel(void);
	void						renderFrame(uint32 uiFrameIndex, bxgi::RWSection_Frame *pFrame, bool bIsParentFrame);

	void						zoomCamera(float32 fRadius);
	bxcf::Vec3f					getCameraRotation(void);
	float32						getCameraZRotation(void); // result is in radians

	void						setDFFFile(bxgi::DFFFormat *pDFFFile) { m_pDFFFile = pDFFFile; }
	bxgi::DFFFormat*			getDFFFile(void) { return m_pDFFFile; }

private:
	bxgi::DFFFormat*			m_pDFFFile;
	bxgi::TXDFormat*			m_pTXDFile;
	bool						m_bInitialized;
	bool						m_bPanningCamera;

	bxcf::Vec3f					m_vecCameraPosition;
	bxcf::Vec3f					m_vecCameraLookAtPosition;
	HDC							m_hdcWindow;
	HDC							m_hDC;
	HBITMAP						m_hbm;
};