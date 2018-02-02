#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Static/StdVector.h"
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

ModelEditorTab::ModelEditorTab(void) :
	m_pDFFFile(nullptr),
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
	bindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);
	bindEvent(RESIZE_WINDOW, &ModelEditorTab::onResizeWindow);
	bindEvent(PROCESS, &ModelEditorTab::onProcess);

	EditorTab::bindEvents();
}

void						ModelEditorTab::unbindEvents(void)
{
	unbindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);
	unbindEvent(RESIZE_WINDOW, &ModelEditorTab::onResizeWindow);
	unbindEvent(PROCESS, &ModelEditorTab::onProcess);

	EditorTab::unbindEvents();
}

// event callbacks
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
	else
	{
		float32 fMouseWheelScrollMultiplier = 1.2f;
		int iDelta = -(iRotationDistance / WHEEL_DELTA);
		m_gl.zoomCamera((float32)-iDelta * fMouseWheelScrollMultiplier);
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

// render 2d
void						ModelEditorTab::render(void)
{
}

void						ModelEditorTab::render_Type1(void)
{
}

// render 3d
void						ModelEditorTab::onProcess(void)
{
	if (!getLayer()->getWindow()->isWindowDisplayed())
	{
		return;
	}

	render3D();
}

void						ModelEditorTab::render3D(void)
{
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

		m_gl.setRenderSize(vecRenderSize);
		m_gl.setWindow(getLayer()->getWindow()->getWindowHandle());
		m_gl.setVersion(3, 0);
		m_gl.initOpenGL();
		m_gl.setAxisShown(true);
		m_gl.setFBOEnabled(true);
		m_gl.setShaders(
			DataPath::getDataPath() + "Shaders/ModelEditor/shader1.vert",
			DataPath::getDataPath() + "Shaders/ModelEditor/shader1.frag"
		);
		m_gl.setCameraPosition(glm::vec3(-4.0f, -4.0f, 4.0f));
		m_gl.setCameraRotation(glm::vec3(45, 0, 135));
		m_gl.setModel(glm::mat4(1.0f));
		m_gl.prepareState();
		m_gl.init();

		prepareScene();
		m_gl.resizeScene();

		mutexInitializing3DRender_ModelEditor.unlock();

		m_bInitialized = true;
		m_bInitializing = false;
	}

	m_gl.preRender();
	m_gl.render();
	m_gl.postRender();

	// gdi - draw 2d bitmap
	HDC hdc2 = CreateCompatibleDC(GetWindowDC(m_gl.m_hWindow));
	HBITMAP hbm2 = m_gl.getFBOBitmap();

	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);
	BitBlt(GetWindowDC(m_gl.m_hWindow), 120+250, 130, m_gl.getRenderSize().x, m_gl.getRenderSize().y, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOld2);

	DeleteObject(hbm2);
	DeleteDC(hdc2);
}

// entity preparation
void						ModelEditorTab::prepareScene(void)
{
	glUseProgram(m_gl.m_uiShaderProgram);

	prepareTextures();
	prepareMeshes();
}

void					ModelEditorTab::prepareTextures(void)
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

		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void						ModelEditorTab::prepareMeshes(void)
{
	uint32 uiGeometryCount = m_pDFFFile->getSectionCountByType(RW_SECTION_GEOMETRY);

	/*
	RWSection_FrameList *pFrameList = (RWSection_FrameList *)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];
	uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];
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

		//glMultMatrixf(&vecMultMatrix[0]);
		m_stkModels.top() = matMultMatrix;

		//pGLMesh->setRotationMatrix(matMultMatrix);

		//glUniformMatrix4fv(glGetUniformLocation(m_gl.m_uiShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));
	}
	*/

	// prepare 3d buffers
	uint32 uiGeometryIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		RWSection_Geometry *pGeometry = (RWSection_Geometry*)pRWSection;
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		vector<RWSection*> vecStrings = pGeometry->getSectionsByType(RW_SECTION_STRING);
		bool bMeshUsesTexture = vecStrings.size() > 0;
		string strTextureNameLower;
		if (bMeshUsesTexture)
		{
			strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
			m_umapGeometryIndexByTextureNameLower[strTextureNameLower] = uiGeometryIndex;
		}

		GLMesh *pGLMesh = m_gl.addMesh(
			m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexPositions())),
			*(vector<glm::vec2>*)(&pGeometry->getTextureCoordinates()),
			StdVector::convertStdVectorBXCFVec4u8ToGLMVec3(pGeometry->getVertexColours()),
			m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexNormals()))
		);

		uint32 uiGeometryMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			pGLMesh->addFaceGroup(
				pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP,
				pMesh->getVertexIndices(),
				strTextureNameLower == "" ? nullptr : m_umapTexturesByNameLower[strTextureNameLower]
			);

			uiGeometryMeshIndex++;
		}

		uiGeometryIndex++;
	}

	m_gl.reset();
}