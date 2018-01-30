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
	m_vecRenderSize.x = 600;
	m_vecRenderSize.y = 600;
}

// init
bool						ModelEditorTab::init(bool bIsNewFile)
{
	EditorTab::init(bIsNewFile);

	

	return true;
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

	/*
	todo
	
	m_vecRenderSize = Vec2u(getLayer()->getWindow()->getSize().x - 120 - 250 - 5, getLayer()->getWindow()->getSize().y - 130 - 30);

	mutexRendering.lock();

	if (m_hbm)
	{
		DeleteObject(m_hbm);
	}

	m_hbm = CreateCompatibleBitmap(m_hdcWindow, m_vecRenderSize.x, m_vecRenderSize.y);
	SelectObject(m_hDC, m_hbm);

	reshape();

	mutexRendering.unlock();
	*/
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
	//mutexInitializing3DRender_ModelEditor.lock();
	render3D();
	//mutexInitializing3DRender_ModelEditor.unlock();
}

void						ModelEditorTab::render3D(void)
{
	if (!m_bInitialized)
	{
		return;
	}

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

	


	mutexInitializing3DRender_ModelEditor.lock();

	m_bInitializing = true;

	m_gl.setRenderSize(m_vecRenderSize);
	m_gl.setWindow(getLayer()->getWindow()->getWindowHandle());
	m_gl.setVersion(3, 0);
	m_gl.setAxisShown(true);
	m_gl.init();

	prepareScene();
	reshape();

	mutexInitializing3DRender_ModelEditor.unlock();

	m_bInitialized = true;
	m_bInitializing = false;





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	int c = glGetError();
	if (c != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	m_stkModels.push(m_stkModels.top());

	renderCamera();
	renderModel();
	renderAxis();

	m_stkModels.pop();

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

	glFinish();

	// gdi - draw 2d bitmap
	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);
	BitBlt(GetWindowDC(m_gl.m_hWindow), 120+250, 130, m_vecRenderSize.x, m_vecRenderSize.y, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOld2);

	// clean up gdi
	DeleteObject(hbm2);
	DeleteDC(hdc2);
}

// render components
void						ModelEditorTab::renderAxis(void)
{
	glUseProgram(m_program2);

	glBindVertexArray(axisBuffer);		// select first VAO
										//glVertexAttrib3f((GLuint)1, 0.8f, 0.0, 0.0); // set constant color attribute
	glDrawArrays(GL_LINES, 0, 6);	// draw first object
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// camera
void						ModelEditorTab::zoomCamera(float32 fRadius)
{
	glm::vec3 vecCameraRotation = getCameraRotation();
	float32 fXAngle = vecCameraRotation.x;// Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z - Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fRadius, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	///////////m_vecCameraPosition = m_vecCameraPosition + vecCameraPositionOffset;
	///////////m_vecCameraLookAtPosition = m_vecCameraLookAtPosition + vecCameraPositionOffset;
}

glm::vec3					ModelEditorTab::getCameraRotation(void)
{
	/*
	Vec3f vecCameraRotation = Vec3f{
		Math::getAngleBetweenPoints(Vec3f(m_vecCameraPosition.x, m_vecCameraPosition.z, 0.0f), Vec3f(m_vecCameraLookAtPosition.x, m_vecCameraLookAtPosition.z, 0.0f)) + Math::convertDegreesToRadians(90.0f), // X
		0.0f, // Y
		Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f) // Z
	};
	while (vecCameraRotation.x > 3.142) vecCameraRotation.x -= 3.142;
	while (vecCameraRotation.x < -3.142) vecCameraRotation.x += 3.142;
	while (vecCameraRotation.y > 3.142) vecCameraRotation.y -= 3.142;
	while (vecCameraRotation.y < -3.142) vecCameraRotation.y += 3.142;
	while (vecCameraRotation.z > 3.142) vecCameraRotation.z -= 3.142;
	while (vecCameraRotation.z < -3.142) vecCameraRotation.z += 3.142;
	return vecCameraRotation;
	*/
	return m_vecCameraRotation;
}

float32						ModelEditorTab::getCameraZRotation(void)
{
	//return Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f); // Z
	return m_vecCameraRotation.z;
}

// render 3d components
void						ModelEditorTab::renderCamera(void)
{
	glm::vec3 vecCameraRotation = getCameraRotation();
	//f += 0.03f;

	//vecCameraRotation.z = -vecCameraRotation.z;

	// camera rotation
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.x), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.z), 0.0f, 1.0f, 0.0f); // Rotate our camera on the y-axis (looking left and right)
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.y), 0.0f, 0.0f, 1.0f);

	// camera position
	glTranslatef(-m_vecCameraPosition.x, -m_vecCameraPosition.z, -m_vecCameraPosition.y);

	//vecCameraRotation.x += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.03f);
}

void						ModelEditorTab::renderModel(void)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));

	glEnable(GL_TEXTURE_2D);

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

	uint32 uiFrameIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_FRAME))
	{
		RWSection_Frame *pFrame = (RWSection_Frame*)pRWSection;
		uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

		if (uiParentFrameIndex == -1)
		{
			renderFrame(uiFrameIndex, pFrame, true);
		}

		uiFrameIndex++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
}

void						ModelEditorTab::renderFrame(uint32 uiFrameIndex, RWSection_Frame *pFrame, bool bIsParentFrame)
{
	m_stkModels.push(m_stkModels.top());
	glColor4f(1.0, 0.2, 1.0, 1.0);

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

		glUseProgram(m_program2);
		glUniformMatrix4fv(glGetUniformLocation(m_program2, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));

		glUseProgram(m_program);
		glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));
	}

	if (umapAtomics.count(uiFrameIndex) != 0)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic*)umapAtomics[uiFrameIndex];
		uint32 uiGeometryIndex = pAtomic->getGeometryIndex();
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		uint32 uiMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			uint32 uiMaterialIndex = pMesh->getMaterialIndex();
			vector<RWSection*> vecMaterials = pBinMeshPLG->getParentNode()->getParentNode()->getSectionsByType(RW_SECTION_MATERIAL);
			RWSection_Material *pMaterial = (RWSection_Material*)vecMaterials[uiMaterialIndex];
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY)[uiGeometryIndex];
			vector<RWSection*> vecStrings = pMaterial->getSectionsByType(RW_SECTION_STRING);
			bool bMeshUsesTexture = vecStrings.size() > 0;
			bool bUsesNormals = pGeometry->getBoundingInfo().doesHaveNormals();
			string strTextureNameLower;
			if (bMeshUsesTexture)
			{
				strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
			}

			glEnableClientState(GL_VERTEX_ARRAY);
			if (bUsesNormals)
			{
				glEnableClientState(GL_NORMAL_ARRAY);
			}
			if (bMeshUsesTexture)
			{
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			}

			glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex][uiMeshIndex]);
			/////glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[uiGeometryIndex]);
			/////glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
			if (bUsesNormals)
			{
				/////glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[uiGeometryIndex]);
				/////glVertexAttribPointer(glGetAttribLocation(m_program, "inNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
			}
			if (bMeshUsesTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textureIndices[strTextureNameLower]);
				glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

				/////glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);
				/////glVertexAttribPointer(glGetAttribLocation(m_program, "in_Texcoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiMeshIndex]);

			//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)0);
			//glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 3, (void*)0);
			//glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 2, (void*)0);

			//glDrawArrays(pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP, 0, pMesh->getVertexIndices().size() * 3);
			glDrawElements(pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP, pMesh->getVertexIndices().size(), GL_UNSIGNED_INT, (void*)0);

			//glBindVertexArray(0);

			if (bMeshUsesTexture)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			if (bUsesNormals)
			{
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glDisableClientState(GL_VERTEX_ARRAY);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			uiMeshIndex++;
		}
	}

	for (uint32 uiFrameIndex2 = 0, j = pFrameList->getFrameCount(); uiFrameIndex2 < j; uiFrameIndex2++)
	{
		RWSection_Frame *pFrame = (RWSection_Frame*) m_pDFFFile->getSectionsByType(RW_SECTION_FRAME)[uiFrameIndex2];
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
						renderFrame(uiFrameIndex2, pFrame, true);
					}
				}
				else if (strFrameName.substr(1, 3) != "Col")
				{
					renderFrame(uiFrameIndex2, pFrame, false);
				}
			}
			else
			{
				renderFrame(uiFrameIndex2, pFrame, false);
			}
		}
	}

	m_stkModels.pop();
}

void						ModelEditorTab::prepareScene(void)
{
	prepareGLStates();
	prepareShaders();
	prepareShaderData();
	
	prepareFBO();

	prepareCamera();
	prepareAxis();
	prepareMeshes();
	prepareTextures();
}

void						ModelEditorTab::reshape(void)
{
	glViewport(0, 0, m_vecRenderSize.x, m_vecRenderSize.y);
}

void						ModelEditorTab::drawScene(void)
{
}

void						ModelEditorTab::destroyScene(void)
{
}

void						ModelEditorTab::prepareShaders(void)
{
	// setup program 1
	GLuint shader1 = m_gl.prepareShader(GL_VERTEX_SHADER, DataPath::getDataPath() + "Shaders/ModelEditor/VertexShader-Texture.glsl");
	GLuint shader2 = m_gl.prepareShader(GL_FRAGMENT_SHADER, DataPath::getDataPath() + "Shaders/ModelEditor/FragmentShader-Texture.glsl");

	// create opengl program
	m_program = glCreateProgram();

	glAttachShader(m_program, shader1);
	glAttachShader(m_program, shader2);

	glLinkProgram(m_program);
	glUseProgram(m_program);

	// setup program 2
	GLuint shader3 = m_gl.prepareShader(GL_VERTEX_SHADER, DataPath::getDataPath() + "Shaders/ModelEditor/VertexShader-Colour.glsl");
	GLuint shader4 = m_gl.prepareShader(GL_FRAGMENT_SHADER, DataPath::getDataPath() + "Shaders/ModelEditor/FragmentShader-Colour.glsl");

	m_program2 = glCreateProgram();

	glAttachShader(m_program2, shader3);
	glAttachShader(m_program2, shader4);

	glLinkProgram(m_program2);
	glUseProgram(m_program2);
}

void							ModelEditorTab::prepareCamera(void)
{
	m_vecCameraPosition = glm::vec3(-4.0f, -4.0f, 4.0f);
	m_vecCameraRotation = glm::vec3(45, 0, 135);

	updateCameraMatrix();
}

void							ModelEditorTab::updateCameraMatrix(void)
{
	glm::mat4 orientation;

	orientation = glm::rotate(orientation, Math::convertDegreesToRadians(m_vecCameraRotation.x), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, Math::convertDegreesToRadians(m_vecCameraRotation.z), glm::vec3(0, 1, 0));
	//orientation = glm::rotate(orientation, yAngle, glm::vec3(0, 0, 1));

	m_matCamera = glm::perspective(45.0f, (float)m_vecRenderSize.x / (float)m_vecRenderSize.y, 0.1f, 1500.0f);
	m_matCamera *= orientation;
	m_matCamera = glm::translate(m_matCamera, -glm::vec3(m_vecCameraPosition.x, m_vecCameraPosition.z, m_vecCameraPosition.y));

	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "camera"), 1, GL_FALSE, glm::value_ptr(m_matCamera));
	glUseProgram(m_program2);
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "camera"), 1, GL_FALSE, glm::value_ptr(m_matCamera));
	glUseProgram(m_program);
}

void							ModelEditorTab::prepareAxis(void)
{
	glUseProgram(m_program2);

	float32 fMin = -5000.0f;
	float32 fMax = 5000.0f;

	float32 axisCoordinates[6][3];

	// X
	axisCoordinates[0][0] = fMin;
	axisCoordinates[0][1] = 0.0f;
	axisCoordinates[0][2] = 0.0f;

	axisCoordinates[1][0] = fMax;
	axisCoordinates[1][1] = 0.0f;
	axisCoordinates[1][2] = 0.0f;

	// Y
	axisCoordinates[2][0] = 0.0f;
	axisCoordinates[2][1] = 0.0f;
	axisCoordinates[2][2] = fMin;

	axisCoordinates[3][0] = 0.0f;
	axisCoordinates[3][1] = 0.0f;
	axisCoordinates[3][2] = fMax;

	// Z
	axisCoordinates[4][0] = 0.0f;
	axisCoordinates[4][1] = fMin;
	axisCoordinates[4][2] = 0.0f;

	axisCoordinates[5][0] = 0.0f;
	axisCoordinates[5][1] = fMax;
	axisCoordinates[5][2] = 0.0f;

	// axis colours
	float32 axisColours[6][3];
	
	// X
	axisColours[0][0] = 1.0f;
	axisColours[0][1] = 0.0f;
	axisColours[0][2] = 0.0f;

	axisColours[1][0] = 1.0f;
	axisColours[1][1] = 0.0f;
	axisColours[1][2] = 0.0f;

	// Y
	axisColours[2][0] = 0.0f;
	axisColours[2][1] = 1.0f;
	axisColours[2][2] = 0.0f;

	axisColours[3][0] = 0.0f;
	axisColours[3][1] = 1.0f;
	axisColours[3][2] = 0.0f;

	// Z
	axisColours[4][0] = 0.0f;
	axisColours[4][1] = 0.0f;
	axisColours[4][2] = 1.0f;

	axisColours[5][0] = 0.0f;
	axisColours[5][1] = 0.0f;
	axisColours[5][2] = 1.0f;

	//uint32 indexBuffer[6];
	//indexBuffer[0] = 0;
	//indexBuffer[1] = 2;
	//indexBuffer[2] = 1;
	//indexBuffer[3] = 3;
	//indexBuffer[4] = 4;
	//indexBuffer[5] = 5;

	glGenVertexArrays(1, &axisBuffer);
	glBindVertexArray(axisBuffer);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float32) * 3 * 6, &axisCoordinates[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(m_program2, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(m_program2, "in_Position"));
	
	glGenBuffers(1, &m_vboColours);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboColours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 6, axisColours, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(m_program2, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(m_program2, "in_Color"));

	//glGenBuffers(1, &m_iboID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * 6, indexBuffer, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void							ModelEditorTab::prepareMeshes(void)
{
	glUseProgram(m_program);

	uint32 uiGeometryCount = m_pDFFFile->getSectionCountByType(RW_SECTION_GEOMETRY);

	m_pGeometryVertexPositionBuffers.resize(uiGeometryCount);
	m_pGeometryVertexNormalBuffers.resize(uiGeometryCount);
	m_pGeometryTexturePositionBuffers.resize(uiGeometryCount);
	m_pBinMeshDataIndexBuffers.resize(uiGeometryCount);

	m_pGeometryVertexArrayBuffers.resize(uiGeometryCount);

	m_pVertexPositionBuffer.resize(uiGeometryCount);
	m_pVertexNormalBuffer.resize(uiGeometryCount);
	m_pTextureCoordinateBuffer.resize(uiGeometryCount);
	m_pDataIndexBuffer.resize(uiGeometryCount);

	// prepare 3d buffers
	uint32 uiGeometryIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		RWSection_Geometry *pGeometry = (RWSection_Geometry*)pRWSection;
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		vector<RWSection*> vecStrings = pGeometry->getSectionsByType(RW_SECTION_STRING);
		bool bMeshUsesTexture = vecStrings.size() > 0;
		if (bMeshUsesTexture)
		{
			string strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
			m_umapGeometryIndexByTextureNameLower[strTextureNameLower] = uiGeometryIndex;
		}

		uint32 uiSize1 = pGeometry->getVertexPositions().size() * sizeof(float32) * 3;
		string strData1 = "";
		for (Vec3f& vecPosition : pGeometry->getVertexPositions())
		{
			strData1 += String::packFloat32(vecPosition.x, false);
			strData1 += String::packFloat32(vecPosition.z, false);
			strData1 += String::packFloat32(vecPosition.y, false);
		}
		m_pVertexPositionBuffer[uiGeometryIndex] = strData1.c_str();

		uint32 uiSize4 = pGeometry->getVertexNormals().size() * sizeof(float32) * 3;
		string strData4 = "";
		for (Vec3f& vecNormal : pGeometry->getVertexNormals())
		{
			strData4 += String::packFloat32(vecNormal.x, false);
			strData4 += String::packFloat32(vecNormal.z, false);
			strData4 += String::packFloat32(vecNormal.y, false);
		}
		m_pVertexNormalBuffer[uiGeometryIndex] = strData4.c_str();

		uint32 uiSize3 = pGeometry->getTextureCoordinates().size() * sizeof(float32) * 2;
		string strData3 = "";
		for (Vec2f& vecTextureCoordinates : pGeometry->getTextureCoordinates())
		{
			strData3 += String::packFloat32(vecTextureCoordinates.x, false);
			strData3 += String::packFloat32(vecTextureCoordinates.y, false);
		}
		m_pTextureCoordinateBuffer[uiGeometryIndex] = strData3.c_str();

		
		

		
		

		// data indices
		m_pBinMeshDataIndexBuffers[uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());
		m_pDataIndexBuffer[uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());
		m_pGeometryVertexArrayBuffers[uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());

		uint32 uiGeometryMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			// VAO
			glGenVertexArrays(1, &m_pGeometryVertexArrayBuffers[uiGeometryIndex][uiGeometryMeshIndex]);
			glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex][uiGeometryMeshIndex]);

			// vertex positions
			m_pGeometryVertexPositionBuffers[uiGeometryIndex] = 0;
			glGenBuffers(1, &m_pGeometryVertexPositionBuffers[uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize1, m_pVertexPositionBuffer[uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Position"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// vertex normals
			glGenBuffers(1, &m_pGeometryVertexNormalBuffers[uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize4, m_pVertexNormalBuffer[uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "inNormal"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "inNormal"), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// texture coordinates
			glGenBuffers(1, &m_pGeometryTexturePositionBuffers[uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize3, m_pTextureCoordinateBuffer[uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Texcoord"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "in_Texcoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// data index
			uint32 uiSize2 = pMesh->getVertexIndices().size() * sizeof(uint32);
			string strData2 = "";
			for (uint32 uiDataIndex : pMesh->getVertexIndices())
			{
				strData2 += String::packUint32(uiDataIndex, false);
			}
			m_pDataIndexBuffer[uiGeometryIndex][uiGeometryMeshIndex] = strData2.c_str();





			glGenBuffers(1, &m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiGeometryMeshIndex]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiGeometryMeshIndex]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize2, m_pDataIndexBuffer[uiGeometryIndex][uiGeometryMeshIndex], GL_STATIC_DRAW);

			uiGeometryMeshIndex++;
		}

		uiGeometryIndex++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void					ModelEditorTab::prepareTextures(void)
{
	glUseProgram(m_program);

	vector<RWSection*> vecTextures = m_pTXDFile->getSectionsByType(RW_SECTION_TEXTURE_NATIVE);
	uint32 uiTextureCount = vecTextures.size();

	textureIDs = new GLuint[uiTextureCount];
	textureIndices.clear();

	// Create multiple OpenGL textures
	glGenTextures(uiTextureCount, &textureIDs[0]);

	uint32 i = 0;
	for (RWSection *pRWSection : vecTextures)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pRWSection;
		string strTextureRasterData = pTextureNative->getMipMaps().getFirstEntry()->getRasterDataBGRA32();
		string strTextureNameLower = String::toLowerCase(pTextureNative->getDiffuseName());

		uint32 uiGeometryIndex = m_umapGeometryIndexByTextureNameLower[strTextureNameLower];

		//glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex]);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

		// Give the image to OpenGL
		char * a = new char[strTextureRasterData.length()];
		memcpy(a, strTextureRasterData.c_str(), strTextureRasterData.length());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, pTextureNative->getImageSize().x, pTextureNative->getImageSize().y, 0, GL_BGRA, GL_UNSIGNED_BYTE, a);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (pTextureNative->getEntryCount() > 1)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		else
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		textureIndices[strTextureNameLower] = textureIDs[i];

		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void					ModelEditorTab::prepareGLStates(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void							ModelEditorTab::prepareShaderData(void)
{
	m_stkModels.push(glm::mat4(1.0f));
	//m_stkModels.top() *= glm::lookAt(glm::vec3(-4.0f, 1.5f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0); // Texture unit 0

	glUseProgram(m_program2);
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "model"), 1, GL_FALSE, glm::value_ptr(m_stkModels.top()));

	int rr = glGetError();
	if (rr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}
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