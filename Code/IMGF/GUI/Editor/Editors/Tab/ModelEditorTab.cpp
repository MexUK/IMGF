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
		zoomCamera((float32)-iDelta * fMouseWheelScrollMultiplier);
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
void						ModelEditorTab::render_Type1(void)
{
}

// render 3d
void						ModelEditorTab::render(void)
{
	//mutexRendering2.lock();
	//render3D();
	//mutexRendering2.unlock();
}

void						ModelEditorTab::onProcess(void)
{
	if (!getLayer()->getWindow()->isWindowDisplayed())
	{
		return;
	}

	//mutexInitializing3DRender_ModelEditor.lock();
	render3D();
	//mutexInitializing3DRender_ModelEditor.unlock();
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

		m_gl.setRenderSize(m_vecRenderSize);
		m_gl.setWindow(getLayer()->getWindow()->getWindowHandle());
		m_gl.setVersion(3, 0);
		m_gl.initOpenGL();
		m_gl.setAxisShown(true);
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

	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	int c = glGetError();
	if (c != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	m_gl.render();

	// render opengl to bitmap

	//HDC hdcScreen = GetDC(NULL);
	HDC hdc2 = CreateCompatibleDC(GetWindowDC(m_gl.m_hWindow));
	//HBITMAP hbm2 = CreateCompatibleBitmap(m_hdcWindow, vecRenderSize.x, vecRenderSize.y);

	BITMAPINFO bitmapInfo;
	{
		::memset(&bitmapInfo, 0, sizeof(BITMAPINFO));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		bitmapInfo.bmiHeader.biWidth = m_vecRenderSize.x;
		bitmapInfo.bmiHeader.biHeight = m_vecRenderSize.y;
		bitmapInfo.bmiHeader.biSizeImage = m_vecRenderSize.x * m_vecRenderSize.y * 4; // Size 4, assuming RGBA from OpenGL
	}

	void *pixels2 = nullptr;
	HBITMAP hbm2 = ::CreateDIBSection(GetWindowDC(m_gl.m_hWindow), &bitmapInfo, DIB_RGB_COLORS, &pixels2, NULL, 0);

	glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_PACK_LSB_FIRST, GL_TRUE);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	//memcpy(pixels2, pixels, vecRenderSize.x * vecRenderSize.y * 4);
	//delete[] pixels;

	//-------------------------
	//GLubyte *pixels = new GLubyte[vecRenderSize.x * vecRenderSize.y * 4];
	glReadPixels(0, 0, m_vecRenderSize.x, m_vecRenderSize.y, GL_BGRA, GL_UNSIGNED_BYTE, pixels2);
	/*
	if (memchr(pixels2, '\x01', m_vecRenderSize.x * m_vecRenderSize.y * 4))
	{
		bool b = true;
		b = !b;
	}
	if (memchr(pixels2, '\x02', m_vecRenderSize.x * m_vecRenderSize.y * 4))
	{
		bool b = true;
		b = !b;
	}
	*/

	// Bind 0, which means render to back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_gl.postRender();

	glFinish();

	// gdi - draw 2d bitmap
	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);
	BitBlt(GetWindowDC(m_gl.m_hWindow), 120+250, 130, m_vecRenderSize.x, m_vecRenderSize.y, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOld2);

	// clean up gdi
	DeleteObject(hbm2);
	DeleteDC(hdc2);
}

// camera
void						ModelEditorTab::zoomCamera(float32 fRadius)
{
	glm::vec3 vecCameraRotation = m_gl.getCameraRotation();
	float32 fXAngle = vecCameraRotation.x;// Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z - Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fRadius, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	///////////m_vecCameraPosition = m_vecCameraPosition + vecCameraPositionOffset;
	///////////m_vecCameraLookAtPosition = m_vecCameraLookAtPosition + vecCameraPositionOffset;
}

// entity preparation
void						ModelEditorTab::prepareScene(void)
{
	glUseProgram(m_gl.m_uiShaderProgram);

	prepareFBO();
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

void									ModelEditorTab::prepareFBO(void)
{
	glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_2D, color_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_vecRenderSize.x, m_vecRenderSize.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	//-------------------------
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	//Attach 2D texture to this FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);
	//-------------------------
	glGenRenderbuffers(1, &depth_rb);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_vecRenderSize.x, m_vecRenderSize.y);
	//-------------------------
	//Attach depth buffer to FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rb);
	//-------------------------
	//Does the GPU support current FBO configuration?
	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	int b;
	///*
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		b = 1;
		b++;
		break;
		//default:
		//HANDLE_THE_ERROR;
	}
	//*/
}