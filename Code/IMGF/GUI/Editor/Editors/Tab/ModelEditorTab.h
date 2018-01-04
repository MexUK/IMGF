#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Type/Vector/Vec3f.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

//#include <windows.h>
//#include <algorithm>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

//#include "GLEE/GLee.h"
//#include "GL/glew.h"
//#include "GL/wglew.h"
//#include <Windows.h>

class imgf::ModelEditorTab : public imgf::EditorTab
{
public:
	ModelEditorTab(void);

	void						addControls(void);
	void						initControls(void);
	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

	void						initLayer(void);

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
	void						perspectiveGL_ModelEditor(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);




	void						createGLContext(void);
	void						prepareScene(void);
	void						reshape(void);
	void						drawScene(void);
	void						destroyScene(void);

	void						prepareShaders(void);
	void						prepareAxis(void);
	void						prepareMeshes(void);
	void						prepareTextures(void);
	void						prepareGLStates(void);
	void						prepareShaderData(void);
	void						prepareFBO(void);

private:
	bxgi::DFFFormat*			m_pDFFFile;
	bxgi::TXDFormat*			m_pTXDFile;
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

	std::vector<GLuint>			m_pGeometryVertexPositionBuffers;	// GLuint: gl buffer id
	std::vector<GLuint>			m_pGeometryVertexNormalBuffers;		// GLuint: gl buffer id
	std::vector<GLuint>			m_pGeometryTexturePositionBuffers;	// GLuint: gl buffer id
	std::vector<std::vector<GLuint>>	m_pBinMeshDataIndexBuffers;	// GLuint: gl buffer id

	std::vector<std::vector<GLuint>>	m_pGeometryVertexArrayBuffers;		// GLuint: gl vertex array buffer id

	//GLuint*						m_pGeometryVertexPositionBuffers;	// GLuint: gl buffer id

	std::vector<const char*>					m_pVertexPositionBuffer;
	std::vector<const char*>					m_pVertexNormalBuffer;
	std::vector<const char*>					m_pTextureCoordinateBuffer;
	std::vector<std::vector<const char*>>		m_pDataIndexBuffer;

	std::stack<glm::mat4>		m_matProjectionMatrix;
	std::stack<glm::mat4>		m_matModelViewMatrix;
	//glm::mat4					m_matModelViewProjectionMatrix;

	bxcf::Vec2u					m_vecRenderSize;

	GLuint						axisBuffer;
	GLuint						axisIndexBuffer;
	GLuint						fb;
	GLuint						color_tex;
	GLuint						depth_rb;
	GLuint						m_vboID;
	GLuint						m_vboColours;
	GLuint						m_iboID;
};