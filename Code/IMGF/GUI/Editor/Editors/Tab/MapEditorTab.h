#pragma once

#include "nsbxcf.h"
#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Type/Vector/Vec3f.h"
#include "3D/OpenGL/OpenGL.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

struct MapModel // todo - namespace
{
	uint32			m_uiObjectId;
	std::string		m_strModelName;
	std::string		m_strTXDName;
};

struct MapObject // todo - namespace
{
	bxcf::Vec3f		m_vecPosition;
};

class imgf::MapEditorTab : public imgf::EditorTab
{
public:
	MapEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onMouseWheelMove2(int16 iRotationDistance);
	void						onChangeTab(bxgx::TabBar *pTabBar);
	void						onRemoveTab(bxgx::Tab *pTab);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						onResizeWindow(bxcf::Vec2i& vecSizeChange);

	void						render(void);
	void						endRender(void);

	void						render2D(void);
	void						render3D(void);

protected:
	void						storeControls(void);

private:
	void						prepareScene(void);
	void						drawScene(void);

	void						prepareMap(void);
	void						prepareModel(bxgi::DFFFormat *pDFFFile);
	void						prepareTXD(bxgi::TXDFormat *pTXDFile);

	void						prepareGeometries(void);
	void						prepareGeometry(uint32 uiGeometryIndex, bxgi::RWSection_Geometry *pGeometry);
	
	void						prepareRenderData(void);
	void						prepareFrame(uint32 uiFrameIndex, bxgi::RWSection_Frame *pFrame, bool bIsParentFrame);

private:
	bxcf::OpenGL				m_gl;
	bxcf::GLEntity*				m_pGLEntity;

public: // todo
	bxgi::DATLoaderFormat*			m_pDATLoaderFile;
	bxgi::DFFFormat*				m_pDFFFile;
	std::vector<bxgi::IDEFormat*>	m_vecIDEFiles;
	std::vector<bxgi::IPLFormat*>	m_vecIPLFiles;
	std::vector<bxgi::DFFFormat*>	m_vecDFFFiles;
	std::vector<bxgi::TXDFormat*>	m_vecTXDFiles;
	std::unordered_map<std::string, bxcf::GLTexture*>		m_umapTexturesByNameLower;

private:
	bool						m_bInitialized;
	bool						m_bPanningCamera;
	bool						m_bInitializing;

	bxcf::Vec3f					m_vecCameraPosition;
	bxcf::Vec3f					m_vecCameraLookAtPosition;
	HDC							m_hdcWindow;
	HDC							m_hDC;
	HBITMAP						m_hbm;
	HGLRC						m_hRC;

	GLuint						m_program;
	GLuint						m_program2;
	GLuint*						textureIDs; // todo - prefix
	std::unordered_map<std::string, GLuint>		textureIndices; // todo - prefix // GLuint: gl texture id
	std::unordered_map<std::string, uint32>		m_umapGeometryIndexByTextureNameLower;

	std::unordered_map<bxgi::DFFFormat*, std::vector<GLuint>>				m_pGeometryVertexPositionBuffers;	// GLuint: gl buffer id
	std::unordered_map<bxgi::DFFFormat*, std::vector<GLuint>>				m_pGeometryVertexNormalBuffers;		// GLuint: gl buffer id
	std::unordered_map<bxgi::DFFFormat*, std::vector<GLuint>>				m_pGeometryTexturePositionBuffers;	// GLuint: gl buffer id
	std::unordered_map<bxgi::DFFFormat*, std::vector<std::vector<GLuint>>>	m_pBinMeshDataIndexBuffers;	// GLuint: gl buffer id

	std::unordered_map<bxgi::DFFFormat*, std::vector<std::vector<GLuint>>>	m_pGeometryVertexArrayBuffers;		// GLuint: gl vertex array buffer id

	std::unordered_map<bxgi::DFFFormat*, std::vector<const char*>>					m_pVertexPositionBuffer;
	std::unordered_map<bxgi::DFFFormat*, std::vector<const char*>>					m_pVertexNormalBuffer;
	std::unordered_map<bxgi::DFFFormat*, std::vector<const char*>>					m_pTextureCoordinateBuffer;
	std::unordered_map<bxgi::DFFFormat*, std::vector<std::vector<const char*>>>		m_pDataIndexBuffer;

	bxcf::Vec2u					m_vecRenderSize;

	GLuint						m_vboID;
	GLuint						m_vboColours;
	GLuint						m_iboID;

	bool													m_bFilesAreInitialized;
	std::unordered_map<uint32, MapModel*>					m_umapMapModels;
	std::unordered_map<uint32, MapObject*>					m_umapMapObjects;
	std::unordered_map<std::string, bxgi::DFFFormat*>		m_umapDFFsByModelNameLower;
	std::unordered_map<std::string, bxgi::TXDFormat*>		m_umapTXDsByModelNameLower;
};