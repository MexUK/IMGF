#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "nsbxgi.h"
#include "GUI/Editor/Components/_3DEditorTab.h"
#include "Pool/VectorPool.h"
#include "Type/Vector/Vec3f.h"
#include "3D/OpenGL/OpenGL.h"

class imgf::CollisionEditorTab : public imgf::_3DEditorTab
{
public:
	CollisionEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						initLayer(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setCOLFile(bxgi::COLFormat *pCOLFile) { m_pCOLFile = pCOLFile; }
	bxgi::COLFormat*			getCOLFile(void) { return m_pCOLFile; }

	void						render(void);
	void						endRender(void);
	void						renderNotOnProcess(void);

	void						render2D(void);
	void						render3D(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	bool						doesTabEntryMatchFilter(bxgi::COLEntry *pCOLEntry);

	void						onResizeWindow(bxcf::Vec2i& vecSizeChange);
	
	void						makeCurrent(void);

	void						recreateEntryList(void);
	void						calculateDisplayedEntryCount(void);

protected:
	void						storeControls(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	//void						onMouseMove2(bxcf::Vec2i vecCursorPosition);
	bool						onMouseMove(bxcf::Vec2i& vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

private:
	glm::vec3					getItemColour(uint32 uiItemIndex);

	bool						prepareRenderData(void);

	void						prepareScene(void);
	void						prepareEntities(void);
	void						prepareCollisionEntry(void);
	
	void						prepareBoundingSphere(bxgi::COLEntry *pCOLEntry);
	void						prepareBoundingCuboid(bxgi::COLEntry *pCOLEntry);

	void						prepareLinesOrCones(bxgi::COLEntry *pCOLEntry);
	void						prepareSpheres(bxgi::COLEntry *pCOLEntry);
	void						prepareCuboids(bxgi::COLEntry *pCOLEntry);
	void						prepareMeshes(bxgi::COLEntry *pCOLEntry);

	void						setActiveEntry(bxgi::COLEntry *pCOLEntry) { m_pActiveEntry = pCOLEntry; }
	bxgi::COLEntry*				getActiveEntry(void) { return m_pActiveEntry; }

	void						prepareInitial3DRender(void);

	bool						isPointOverEntryList(bxcf::Vec2i& vecPoint);

private:
	bxcf::GLEntity*				m_pGLEntity;

	bxgi::COLFormat*			m_pCOLFile;
	bxgi::COLEntry*				m_pActiveEntry;

	bxgx::ScrollBar*			m_pVScrollBar;

	bool						m_bInitializing;
	bool						m_bInitialized;
	bool						m_bPanningCamera;

	uint32						m_uiDisplayedEntryCount;
};