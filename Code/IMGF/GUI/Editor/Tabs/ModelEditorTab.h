#pragma once

#include "nsbxcf.h"
#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Components/_3DEditorTab.h"
#include "Type/Vector/Vec3f.h"
#include "3D/OpenGL/OpenGL.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

class imgf::ModelEditorTab : public imgf::_3DEditorTab
{
public:
	ModelEditorTab(void);

	void						initLayer(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onMouseWheelMove2(int16 iRotationDistance);
	void						onProcess(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						render(void);
	void						afterRender(void);

	void						render2D(void);
	void						render3D(void);

	void						setDFFFile(bxgi::DFFFormat *pDFFFile) { m_pDFFFile = pDFFFile; }
	bxgi::DFFFormat*			getDFFFile(void) { return m_pDFFFile; }

	void						onResizeWindow(bxcf::Vec2i& vecSizeChange);
	
	void						makeCurrent(void);

protected:
	void						storeControls(void);

private:
	void						prepareScene(void);
	void						unloadScene(void);

	void						prepareCamera(void);

	void						prepareTextures(void);
	void						prepareEntities(void);

	void						prepareModel(void);

	void						prepareGeometries(void);
	void						prepareGeometry(uint32 uiGeometryIndex, bxgi::RWSection_Geometry *pGeometry);

	void						prepareRenderData(void);
	void						prepareFrame(uint32 uiFrameIndex, bxgi::RWSection_Frame *pFrame, bool bIsParentFrame);

private:
	bxcf::GLEntity*				m_pGLEntity;

	bxgi::DFFFormat*			m_pDFFFile;
	bxgi::TXDFormat*			m_pTXDFile;

	bool						m_bInitializing;
	bool						m_bInitialized;

	bool						m_bPanningCamera;

	std::unordered_map<std::string, bxcf::GLTexture*>		m_umapTexturesByNameLower;
	std::unordered_map<std::string, uint32>					m_umapGeometryIndexByTextureNameLower;

	std::vector<bxcf::GLTexture*>	m_vecGLTextures;
	std::vector<bxcf::GLMesh*>		m_vecGLMeshes;
};