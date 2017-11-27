#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "nsbxgx.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Pool/VectorPool.h"
#include "Type/Vector/Vec3f.h"

#include "GL/glew.h"
#include "GL/wglew.h"
#include <Windows.h>

void						perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar); // todo - namespace

class imgf::CollisionEditorTab : public imgf::EditorTab
{
public:
	CollisionEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setCOLFile(bxgi::COLFormat *pCOLFile) { m_pCOLFile = pCOLFile; }
	bxgi::COLFormat*			getCOLFile(void) { return m_pCOLFile; }

	void						render(void);

	void						render2D(void);
	void						render3D(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

protected:
	void						addControls(void);
	void						initControls(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onMouseMove2(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

private:
	bool						prepareRenderData(void);

	void						setActiveEntry(bxgi::COLEntry *pCOLEntry) { m_pActiveEntry = pCOLEntry; }
	bxgi::COLEntry*				getActiveEntry(void) { return m_pActiveEntry; }

	void						setZoomLevel(float32 fZoomLevel) { m_fZoomLevel = fZoomLevel; }
	float32						getZoomLevel(void) { return m_fZoomLevel; }

	void						update3DRenderSize(bxcf::Vec2u& vecRenderSize);

	void						prepareInitial3DRender(void);
	void						prepare3DRender(void);
	void						renderCamera(void);
	void						renderCollisionObjects(void);
	void						renderAxis(void);
	void						renderBoundingSphere(void);
	void						renderBoundingCuboid(void);

	void						renderCollisionMeshes(void);
	void						renderCollisionCuboids(void);
	void						renderCollisionSpheres(void);

	void						moveCamera(float32 fAngleDeg, float32 fRadius);
	void						zoomCamera(float32 fRadius);
	bxcf::Vec3f					getCameraRotation(void);
	float32						getCameraZRotation(void); // result is in radians

private:
	bxgi::COLFormat*			m_pCOLFile;
	bxgi::COLEntry*				m_pActiveEntry;

	bxgx::DropDown*				m_pZoomDropDown;
	bxgx::ScrollBar*			m_pVScrollBar;

	float32						m_fZoomLevel;

	bool						m_bInitialized;

	bxcf::Vec3f					m_vecCameraPosition;
	bxcf::Vec3f					m_vecCameraLookAtPosition;
	HDC							m_hdcWindow;
	HDC							m_hDC;
	HBITMAP						m_hbm;
};