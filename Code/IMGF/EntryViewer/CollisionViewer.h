#pragma once

#include "nsimgf.h"
#include "EntryViewer.h"
#include "Format/COL/COLFormat.h"
#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

void							timer(int extra);
void							render(void);
void							glutKeyboardInputCallback(uint8 ucKey, int x, int y);
void							glutSpecialInputCallback(int iKey, int x, int y);

struct GLFWwindow;
class SolidSphere;

class imgf::CollisionViewer : public EntryViewer
{
public:
	CollisionViewer(void);
	~CollisionViewer(void);

	void						reset(void);
	void						prepareRenderData(void);
	void						render(void);
	void						loadThreadAndWindow(void);
	void						unloadThreadAndWindow(void);
	void						openWindow(void);
	void						closeWindow(void);

	void						init(void);
	void						uninit(void);

	void						initGLFW(void);
	void						initGLEW(void);

	void						setCOLFile(bxgi::COLFormat *pCOLFile) { m_pCOLFile = pCOLFile; }
	bxgi::COLFormat*					getCOLFile(void) { return m_pCOLFile; }

	void						setActiveCOLEntry(bxgi::COLEntry *pCOLEntry) { m_pActiveCOLEntry = pCOLEntry; }
	bxgi::COLEntry*					getActiveCOLEntry(void) { return m_pActiveCOLEntry; }

	void						setCOLFileName(std::string strCOLFileName) { m_strCOLFileName = strCOLFileName; }
	std::string					getCOLFileName(void) { return m_strCOLFileName; }

	void						moveCamera(uint8 ucAxisIndex, bool bPositivePositionChange, float32 fMoveDistance);
	void						zoomCamera(float32 fMoveDistance);

	void						setWindow(GLFWwindow *pWindow) { m_pWindow = pWindow; }
	GLFWwindow*					getWindow(void) { return m_pWindow; }

	void						applyWindowTitle(void);

	void						setEntryChanging(bool bState) { m_bEntryIsChanging = bState; }
	bool						isEntryChanging(void) { return m_bEntryIsChanging; }

	static DWORD WINAPI			onThreadStarted_CollisionViewer(LPVOID lpParam);
	void						onThreadStarted(void);

	void						setWindowIsOpening(bool bState) { m_bWindowIsOpening = bState; }
	bool						isWindowOpening(void) { return m_bWindowIsOpening; }

	std::vector<SolidSphere*>	m_vecCollisionSpheresGL;

private:
	void						initTextStuff(void);
	void						init3DSceneShader(void);

	void						processWindow(void);
	
	void						processKeys(void);

	void						prepare2DRender(void);
	void						prepare3DRender(void);

	void						renderBackground(void);
	void						renderCamera(void);
	void						renderAxis(void);
	void						renderBoundingSphere(void);
	void						renderBoundingCuboid(void);
	void						renderCollisionObjects(void);
	void						render2DObjects(void);
	void						render2DText(void);

	void						renderCollisionMeshes(void);
	void						renderCollisionCuboids(void);
	void						renderCollisionSpheres(void);

	void						renderLeftPanelBackground(void);
	void						renderBottomPanelBackground(void);
	void						renderPanelLineSeparators(void);

private:
	bxgi::COLFormat*					m_pCOLFile;
	bxgi::COLEntry*					m_pActiveCOLEntry;
	std::string					m_strCOLFileName;
	GLFWwindow*					m_pWindow;
	FT_Library*					m_pFTLibrary;
	uint32				m_uiLastKeyProcessTime;
	uint8				m_bWindowIsOpening : 1;
	uint8				m_bEntryIsChanging : 1;
};