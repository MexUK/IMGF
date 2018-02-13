#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Static/StdVector.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "GUI/Editor/Base/Editor.h"
#include "Format/RW/Sections/RWSection_Geometry.h"
#include "Format/RW/Sections/RWSection_String.h"
#include "Format/RW/Sections/RWSection_BinMeshPLG.h"
#include "Format/RW/Sections/RWSection_Material.h"
#include "Format/RW/Sections/RWSection_FrameList.h"
#include "Format/RW/Sections/RWSection_Atomic.h"
#include "Format/RW/Sections/RWSection_Frame.h"
#include "BXGX.h"
#include "Event/EInputEvent.h"
#include "GUI/Window/windows/MainWindow/MainWindow.h"
#include "Static/DataPath.h"
#include <stack>
#include <mutex>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

recursive_mutex mutexRendering2; // todo
mutex mutexInitializing3DRender_ModelEditor; // todo
std::stack<glm::mat4> g_stkModels; // todo

ModelEditorTab::ModelEditorTab(void) :
	m_pDFFFile(nullptr),
	m_pGLEntity(nullptr),
	m_bInitialized(false),
	m_bInitializing(false)
{
}

// controls
void						ModelEditorTab::storeControls(void)
{
}

void						ModelEditorTab::onResizeWindow(Vec2i& vecSizeChange)
{
	if (!m_bInitialized)
	{
		return;
	}

	Vec2u vecRenderSize = Vec2u(getLayer()->getWindow()->getSize().x - 120 - 250 - 5, getLayer()->getWindow()->getSize().y - 130 - 30);

	mutexRendering.lock();
	m_gl.setRenderSize(vecRenderSize);
	m_gl.recreateBitmap();
	m_gl.resizeScene();
	mutexRendering.unlock();
}

// layer
void						ModelEditorTab::initLayer(void)
{
	setLayer(m_pEditor->getMainWindow()->getLayerById(104));
}

// events
void						ModelEditorTab::bindEvents(void)
{
	bindEvent(AFTER_RENDER, &ModelEditorTab::afterRender);
	bindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);
	bindEvent(RESIZE_WINDOW, &ModelEditorTab::onResizeWindow);

	_3DEditorTab::bindEvents();
	EditorTab::bindEvents();
}

void						ModelEditorTab::unbindEvents(void)
{
	unbindEvent(AFTER_RENDER, &ModelEditorTab::afterRender);
	unbindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);
	unbindEvent(RESIZE_WINDOW, &ModelEditorTab::onResizeWindow);

	_3DEditorTab::unbindEvents();
	EditorTab::unbindEvents();
}

// gfx lib context
void						ModelEditorTab::makeCurrent(void)
{
	if (m_gl.m_uiShaderProgram != 0) // todo: use m_gl.isInitialized
	{
		m_gl.makeCurrent();
	}
}

// event callbacks
void						ModelEditorTab::afterRender(void)
{
	render2D();
	render3D();
}

void						ModelEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	//if (isPointOverEntryList(BXGX::get()->getCursorPosition()))
	if(false)
	{
		/*
		int iDelta = -(iRotationDistance / WHEEL_DELTA);
		float32 fNewProgress = m_pVScrollBar->getProgress() + ((float32)iDelta * m_pVScrollBar->getProgressFor1Item());
		fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
		m_pVScrollBar->setProgress(fNewProgress);
		*/
	}

	getLayer()->getWindow()->render();
}

// file loading
bool						ModelEditorTab::unserializeFile(void)
{
	return m_pDFFFile->unserialize();
}

void						ModelEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	//getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// load texture for model
	string strTextureFilePath = Path::replaceFileExtension(getFile()->getFilePath(), "TXD");
	if (File::doesFileExist(strTextureFilePath))
	{
		m_pTXDFile = TXDManager::unserializeFile(strTextureFilePath);
	}

	// render
	getLayer()->getWindow()->render();
}

// file info text
void						ModelEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	//m_pText_FileVersion->setText(getDFFFile()->getRWVersion()->getVersionText(), false);
	//m_pText_FileGame->setText(getDFFFile()->getRWVersion()->getGamesAsString());

	updateEntryCountText();
}

void						ModelEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getDFFFile()->getSectionCountByType(RW_SECTION_GEOMETRY),
		uiTotalEntryCount = uiDisplayedEntryCount;
	string
		strEntryCountText;

	if (uiDisplayedEntryCount == uiTotalEntryCount)
	{
		strEntryCountText = String::toString(uiTotalEntryCount);
	}
	else
	{
		strEntryCountText = String::toString(uiDisplayedEntryCount) + " of " + String::toString(uiTotalEntryCount);
	}

	m_pText_FileEntryCount->setText(strEntryCountText);
}

// render events
void						ModelEditorTab::render(void)
{
	//render2D();
}

// render 2d
void						ModelEditorTab::render2D(void)
{
}

// render 3d
void						ModelEditorTab::onProcess(void)
{
	if (!getLayer()->getWindow()->isWindowDisplayed())
	{
		return;
	}

	//render3D();
}

void						ModelEditorTab::render3D(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (!m_pDFFFile)
	{
		return;
	}

	if (!m_pTXDFile)
	{
		return;
	}

	if (m_bInitializing)
	{
		return;
	}

	if (!m_bInitialized)
	{
		mutexInitializing3DRender_ModelEditor.lock();
		m_bInitializing = true;

		Vec2u vecRenderSize = Vec2u(getLayer()->getWindow()->getSize().x - 120 - 250 - 5, getLayer()->getWindow()->getSize().y - 130 - 30);

		m_gl.setRenderPosition(Vec2i(120 + 250, 130));
		m_gl.setRenderSize(vecRenderSize);
		m_gl.setWindow(getLayer()->getWindow()->getWindowHandle());
		m_gl.setVersion(3, 3);
		m_gl.initOpenGL();
		m_gl.setAxisShown(true);
		m_gl.setFBOEnabled(true);
		m_gl.setShaders(
			DataPath::getDataPath() + "Shaders/3DEditors/shader1.vert",
			DataPath::getDataPath() + "Shaders/3DEditors/shader1.frag"
		);
		m_gl.setCameraPosition(glm::vec3(-4.0f, -4.0f, 4.0f));
		m_gl.setCameraRotation(glm::vec3(45, 0, 135));
		m_gl.setModel(glm::mat4(1.0f));
		m_gl.prepareState();
		m_gl.resizeScene();
		m_gl.init();

		prepareScene();

		mutexInitializing3DRender_ModelEditor.unlock();

		m_bInitialized = true;
		m_bInitializing = false;
	}

	// render to opengl
	m_gl.preRender();
	m_gl.render();
	m_gl.postRender();

	// render to gdi
	HDC hdcWindow = GetWindowDC(m_gl.m_hWindow);
	HDC hdc2 = CreateCompatibleDC(hdcWindow);

	HBITMAP hbm2 = m_gl.getFBOBitmap();
	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);

	BitBlt(pGFX->getMemoryDC(), 120+250, 130, m_gl.getRenderSize().x, m_gl.getRenderSize().y, hdc2, 0, 0, SRCCOPY);
	
	SelectObject(hdc2, hOld2);
	DeleteObject(hbm2);
	DeleteDC(hdc2);
	ReleaseDC(m_gl.m_hWindow, hdcWindow);
	m_gl.resetFBOBitmap();

	// finalize render
	m_gl.finalizeRender();
}

// entity preparation
void						ModelEditorTab::prepareScene(void)
{
	glUseProgram(m_gl.m_uiShaderProgram);

	prepareCamera();

	prepareTextures();
	prepareEntities();
}

void						ModelEditorTab::unloadScene(void)
{
	/*
	todo
	for (GLTexture *pTexture : m_vecGLTextures)
	{
		m_gl.removeTexture(pTexture);
	}
	for (GLMesh *pMesh : m_vecGLMeshes)
	{
		m_gl.removeMesh(pMesh);
	}
	*/
}

void						ModelEditorTab::prepareCamera(void)
{
	Vec3f vecCenterPos2 = Vec3f(0.0f, 0.0f, 0.0f);
	glm::vec3 vecCenterPos = glm::vec3(vecCenterPos2.x, vecCenterPos2.y, vecCenterPos2.z);

	float32 fDFFRadius = 4.0f;
	float32 fRadius = fDFFRadius * 3.0f;
	if (fRadius < 5.0f) fRadius = 5.0f;
	glm::vec2 vecCameraPosOffset = Math::getCartesianFromPolarGLM(fRadius, Math::convertDegreesToRadians(m_fCameraOrbitZRot));
	glm::vec3 vecCameraPos = vecCenterPos + glm::vec3(vecCameraPosOffset.x, vecCameraPosOffset.y, 3.0f);

	m_gl.setCameraPosition(vecCameraPos);
	m_gl.setCameraLookAt(vecCenterPos);
}

void						ModelEditorTab::prepareTextures(void)
{
	vector<RWSection*> vecTextures = m_pTXDFile->getSectionsByType(RW_SECTION_TEXTURE_NATIVE);
	uint32 uiTextureCount = vecTextures.size();

	uint32 i = 0;
	for (RWSection *pRWSection : vecTextures)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pRWSection;
		string strTextureRasterData = pTextureNative->getMipMaps().getFirstEntry()->getRasterDataBGRA32();
		string strTextureNameLower = String::toLowerCase(pTextureNative->getDiffuseName());

		uint32 uiGeometryIndex = m_umapGeometryIndexByTextureNameLower[strTextureNameLower];

		GLTexture *pTexture = m_gl.addTexture(strTextureRasterData, pTextureNative->getMipMaps().getFirstEntry()->getImageSize());

		m_umapTexturesByNameLower[strTextureNameLower] = pTexture;
		m_vecGLTextures.push_back(pTexture);

		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void						ModelEditorTab::prepareEntities(void)
{
	prepareModel();
}

void						ModelEditorTab::prepareModel(void)
{
	m_pGLEntity = m_gl.addEntity();

	g_stkModels.push(glm::mat4(1.0f));

	prepareGeometries();
	prepareRenderData();
}

void						ModelEditorTab::prepareGeometries(void)
{
	uint32 uiGeometryIndex = 0;
	for (RWSection *pGeometry : m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		prepareGeometry(uiGeometryIndex, (RWSection_Geometry*)pGeometry);
		uiGeometryIndex++;
	}
}

void						ModelEditorTab::prepareGeometry(uint32 uiGeometryIndex, RWSection_Geometry *pGeometry)
{
	GLMesh *pGLMesh = m_pGLEntity->addMesh(
		m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexPositions())),
		*(vector<glm::vec2>*)(&pGeometry->getTextureCoordinates()),
		StdVector::convertStdVectorBXCFVec4u8ToGLMVec3(pGeometry->getVertexColours()),
		m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexNormals()))
	);
	m_vecGLMeshes.push_back(pGLMesh);

	RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

	vector<RWSection*> vecStrings = pGeometry->getSectionsByType(RW_SECTION_STRING);
	bool bMeshUsesTexture = vecStrings.size() > 0;
	string strTextureNameLower;
	if (bMeshUsesTexture)
	{
		strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
		m_umapGeometryIndexByTextureNameLower[strTextureNameLower] = uiGeometryIndex;
	}

	for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
	{
		pGLMesh->addFaceGroup(
			pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP,
			pMesh->getVertexIndices(),
			strTextureNameLower == "" ? nullptr : m_umapTexturesByNameLower[strTextureNameLower]
		);
	}
}

void						ModelEditorTab::prepareRenderData(void)
{
	RWSection_FrameList *pFrameList = (RWSection_FrameList *)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

	uint32 uiFrameIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_FRAME))
	{
		RWSection_Frame *pFrame = (RWSection_Frame*)pRWSection;
		uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

		if (uiParentFrameIndex == -1)
		{
			prepareFrame(uiFrameIndex, pFrame, true);
		}

		uiFrameIndex++;
	}
}

void						ModelEditorTab::prepareFrame(uint32 uiFrameIndex, RWSection_Frame *pFrame, bool bIsParentFrame)
{
	g_stkModels.push(g_stkModels.top());

	vector<RWSection*> vecAtomics = m_pDFFFile->getSectionsByType(RW_SECTION_ATOMIC);
	unordered_map<uint32, RWSection_Atomic*> umapAtomics;
	unordered_map<uint32, uint32> umapGeometryIndices;
	for (RWSection *pRWSection : vecAtomics)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic *)pRWSection;
		int32 iFrameIndex = pAtomic->getFrameIndex();
		umapAtomics[iFrameIndex] = pAtomic;
		umapGeometryIndices[iFrameIndex] = pAtomic->getGeometryIndex();
	}

	RWSection_FrameList *pFrameList = (RWSection_FrameList *)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

	uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

	//glm::mat4 matMultMatrix = glm::mat4(1.0f);
	if (!bIsParentFrame)
	{
		glm::mat4 matMultMatrix;

		matMultMatrix[0].x = pFrameList->m_vecMatRow1[uiFrameIndex].x;
		matMultMatrix[0].y = pFrameList->m_vecMatRow1[uiFrameIndex].z;
		matMultMatrix[0].z = pFrameList->m_vecMatRow1[uiFrameIndex].y;
		matMultMatrix[0].w = 0;

		matMultMatrix[1].x = pFrameList->m_vecMatRow3[uiFrameIndex].x;
		matMultMatrix[1].y = pFrameList->m_vecMatRow3[uiFrameIndex].z;
		matMultMatrix[1].z = pFrameList->m_vecMatRow3[uiFrameIndex].y;
		matMultMatrix[1].w = 0;

		matMultMatrix[2].x = pFrameList->m_vecMatRow2[uiFrameIndex].x;
		matMultMatrix[2].y = pFrameList->m_vecMatRow2[uiFrameIndex].z;
		matMultMatrix[2].z = pFrameList->m_vecMatRow2[uiFrameIndex].y;
		matMultMatrix[2].w = 0;

		matMultMatrix[3].x = pFrameList->m_vecPosition[uiFrameIndex].x;
		matMultMatrix[3].y = pFrameList->m_vecPosition[uiFrameIndex].z;
		matMultMatrix[3].z = pFrameList->m_vecPosition[uiFrameIndex].y;
		matMultMatrix[3].w = 1;

		g_stkModels.top() *= matMultMatrix;

		//g_stkModels.top() = glm::translate(g_stkModels.top(), glm::vec3(pFrameList->m_vecPosition[uiFrameIndex].x, pFrameList->m_vecPosition[uiFrameIndex].z, pFrameList->m_vecPosition[uiFrameIndex].y));
		//g_stkModels.top() = glm::rotate(g_stkModels.top(), glm::vec3(pFrameList->m_vecPosition[uiFrameIndex].x, pFrameList->m_vecPosition[uiFrameIndex].z, pFrameList->m_vecPosition[uiFrameIndex].y));
	}

	//g_stkModels.top() *= matMultMatrix;

	if (umapAtomics.count(uiFrameIndex) != 0)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic*)umapAtomics[uiFrameIndex];
		uint32 uiGeometryIndex = pAtomic->getGeometryIndex();
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			uint32 uiMaterialIndex = pMesh->getMaterialIndex();
			vector<RWSection*> vecMaterials = pBinMeshPLG->getParentNode()->getParentNode()->getSectionsByType(RW_SECTION_MATERIAL);
			vector<RWSection*> vecGeometries = m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY);
			RWSection_Material *pMaterial = (RWSection_Material*)vecMaterials[uiMaterialIndex];
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)vecGeometries[uiGeometryIndex];// todo (RWSection_Geometry*)pBinMeshPLG->getParentNode()->getParentNode();
			vector<RWSection*> vecStrings = pMaterial->getSectionsByType(RW_SECTION_STRING);
			bool bMeshUsesTexture = vecStrings.size() > 0;
			bool bUsesNormals = pGeometry->getBoundingInfo().doesHaveNormals();
			string strTextureNameLower;
			if (bMeshUsesTexture)
			{
				strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
			}

			GLTexture *pGLTexture = strTextureNameLower == "" ? nullptr : m_umapTexturesByNameLower[strTextureNameLower];

			GLRenderData renderData;
			renderData.m_uiGeometryIndex = uiGeometryIndex;
			renderData.m_pGLTexture = pGLTexture;
			renderData.m_matMultMatrix = g_stkModels.top();

			m_pGLEntity->m_vecRenderData.push_back(renderData);

			//m_gl.reset();
		}
	}

	for (uint32 uiFrameIndex2 = 0, j = pFrameList->getFrameCount(); uiFrameIndex2 < j; uiFrameIndex2++)
	{
		RWSection_Frame *pFrame = (RWSection_Frame*)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME)[uiFrameIndex2];
		if (uiFrameIndex == pFrameList->m_uiCurrentFrameIndex[uiFrameIndex2])
		{
			string strFrameName = String::trim(pFrame->getData());
			uint32 uiFrameNameLength = strFrameName.length();
			if (uiFrameNameLength >= 3)
			{
				if (strFrameName.c_str()[uiFrameNameLength - 2] == '_' && (String::toUpperCase(strFrameName).c_str()[uiFrameNameLength - 1] == 'L'))
				{
					int32 iFrameValue = String::toInt32(strFrameName);
					if (iFrameValue <= 0)
					{
						prepareFrame(uiFrameIndex2, pFrame, true);
					}
				}
				else if (strFrameName.substr(1, 3) != "Col")
				{
					prepareFrame(uiFrameIndex2, pFrame, false);
				}
			}
			else
			{
				prepareFrame(uiFrameIndex2, pFrame, false);
			}
		}
	}

	g_stkModels.pop();
}