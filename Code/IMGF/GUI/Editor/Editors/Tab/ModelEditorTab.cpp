#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
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
#include <stack>

/*
#include <include/GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 1
#define GLFW_EXPOSE_NATIVE_WGL 1
#include <include/GLFW/glfw3native.h>
*/

//#define GL_GLEXT_PROTOTYPES 1
//#define GL3_PROTOTYPES 1


//#include "GL3.h"
//#include <gl\glu.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

ModelEditorTab::ModelEditorTab(void) :
	m_pDFFFile(nullptr),
	m_bInitialized(false),
	m_bInitializing(false)
{
	m_vecRenderSize.x = 200;
	m_vecRenderSize.y = 200;
}

// controls
void						ModelEditorTab::addControls(void)
{
}

void						ModelEditorTab::initControls(void)
{
	repositionAndResizeControls(Vec2i(0, 0));
}

void						ModelEditorTab::repositionAndResizeControls(Vec2i& vecSizeChange)
{
	EditorTab::repositionAndResizeControls(vecSizeChange);

	if (!m_bInitialized)
	{
		return;
	}

	//Vec2u vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);
	m_vecRenderSize = Vec2u(300, 300);

	mutexRendering.lock();

	if (m_hbm)
	{
		DeleteObject(m_hbm);
	}

	m_hbm = CreateCompatibleBitmap(m_hdcWindow, m_vecRenderSize.x, m_vecRenderSize.y);
	SelectObject(m_hDC, m_hbm);

	reshape();

	mutexRendering.unlock();
}

// events
void						ModelEditorTab::bindEvents(void)
{
	bindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void						ModelEditorTab::unbindEvents(void)
{
	unbindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);

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

	m_pWindow->render();
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
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// load texture for model
	string strTextureFilePath = Path::replaceFileExtension(getFile()->getFilePath(), "TXD");
	if (File::doesFileExist(strTextureFilePath))
	{
		m_pTXDFile = TXDManager::unserializeFile(strTextureFilePath);
	}

	// render
	m_pWindow->render();
}

// file info text
void						ModelEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	m_pText_FileVersion->setText(getDFFFile()->getRWVersion()->getVersionText(), false);
	m_pText_FileGame->setText(getDFFFile()->getRWVersion()->getGamesAsString());

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
mutex mutexInitializing3DRender_ModelEditor; // todo

void						ModelEditorTab::render(void)
{
	render3D();
}

void						ModelEditorTab::render3D(void)
{
	if (!m_pTXDFile)
	{
		return;
	}

	if (m_bInitializing)
	{
		return;
	}

	mutexInitializing3DRender_ModelEditor.lock();
	if (!m_bInitialized)
	{
		m_bInitializing = true;
		
		m_vecRenderSize = Vec2u(300, 300);
		//m_vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);
		m_hdcWindow = GetDC(m_pWindow->getWindowHandle());

		createGLContext();
		prepareScene();
		reshape();

		m_bInitialized = true;
		m_bInitializing = false;
	}
	mutexInitializing3DRender_ModelEditor.unlock();





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	int c = glGetError();
	if (c != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	///glBindVertexArray(axisBuffer);		// select first VAO
	//glVertexAttrib3f((GLuint)1, 0.8f, 0.0, 0.0); // set constant color attribute
	///glDrawArrays(GL_LINES, 0, 6*3);	// draw first object

	///glBindVertexArray(0);

	renderModel();

	glBindVertexArray(0);

	//SwapBuffers(m_hDC);

	

	



	

	// render opengl to bitmap

	//HDC hdcScreen = GetDC(NULL);
	HDC hdc2 = CreateCompatibleDC(m_hdcWindow);
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
	HBITMAP hbm2 = ::CreateDIBSection(m_hdcWindow, &bitmapInfo, DIB_RGB_COLORS, &pixels2, NULL, 0);

	glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_PACK_LSB_FIRST, GL_TRUE);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	//SetBitmapBits(hbm2, vecRenderSize.x * vecRenderSize.y * 4, pixels);

	//memcpy(pixels2, pixels, vecRenderSize.x * vecRenderSize.y * 4);
	//delete[] pixels;

	//glReadBuffer(GL_BACK);

	//-------------------------
	//GLubyte *pixels = new GLubyte[vecRenderSize.x * vecRenderSize.y * 4];
	glReadPixels(0, 0, m_vecRenderSize.x, m_vecRenderSize.y, GL_BGRA, GL_UNSIGNED_BYTE, pixels2);
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
	//pixels 0, 1, 2 should be white
	//pixel 4 should be black
	//----------------
	//Bind 0, which means render to back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glFinish();

	// gdi - draw 2d bitmap
	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);
	BitBlt(m_hdcWindow, 139 + 139 + 250, 192, m_vecRenderSize.x, m_vecRenderSize.y, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOld2);

	// clean up gdi
	DeleteObject(hbm2);
	DeleteDC(hdc2);
}

// camera
void						ModelEditorTab::zoomCamera(float32 fRadius)
{
	Vec3f vecCameraRotation = getCameraRotation();
	float32 fXAngle = vecCameraRotation.x;// Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z - Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fRadius, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	m_vecCameraPosition = m_vecCameraPosition + vecCameraPositionOffset;
	m_vecCameraLookAtPosition = m_vecCameraLookAtPosition + vecCameraPositionOffset;
}

Vec3f						ModelEditorTab::getCameraRotation(void)
{
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
}

float32						ModelEditorTab::getCameraZRotation(void)
{
	return Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f); // Z
}

// render 3d components
void						ModelEditorTab::renderCamera(void)
{
	Vec3f vecCameraRotation = getCameraRotation();
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
	//glPushMatrix();
	m_matModelViewMatrix.push(m_matModelViewMatrix.top());
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

	//if not TheParent then with Clump[in_clump].FrameList.Data.Frame[in_frame] do
	// rotate offset

	//uiFrameIndex = pAtomic->getFrameIndex();

	if (!bIsParentFrame)
	{
		//float32 vecMultMatrix[16];
		glm::mat4 matMultMatrix;

		///*
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
		//*/

		/*
		matMultMatrix[0].x = pFrameList->m_vecMatRow1[uiFrameIndex].x;
		matMultMatrix[0].y = pFrameList->m_vecMatRow1[uiFrameIndex].y;
		matMultMatrix[0].z = pFrameList->m_vecMatRow1[uiFrameIndex].z;
		matMultMatrix[0].w = 0;

		matMultMatrix[1].x = pFrameList->m_vecMatRow3[uiFrameIndex].x;
		matMultMatrix[1].y = pFrameList->m_vecMatRow3[uiFrameIndex].y;
		matMultMatrix[1].z = pFrameList->m_vecMatRow3[uiFrameIndex].z;
		matMultMatrix[1].w = 0;

		matMultMatrix[2].x = pFrameList->m_vecMatRow2[uiFrameIndex].x;
		matMultMatrix[2].y = pFrameList->m_vecMatRow2[uiFrameIndex].y;
		matMultMatrix[2].z = pFrameList->m_vecMatRow2[uiFrameIndex].z;
		matMultMatrix[2].w = 0;

		matMultMatrix[3].x = pFrameList->m_vecPosition[uiFrameIndex].x;
		matMultMatrix[3].y = pFrameList->m_vecPosition[uiFrameIndex].y;
		matMultMatrix[3].z = pFrameList->m_vecPosition[uiFrameIndex].z;
		matMultMatrix[3].w = 1;
		*/

		//glMultMatrixf(&vecMultMatrix[0]);
		m_matModelViewMatrix.top() *= matMultMatrix;
		//m_matProjectionMatrix *= matMultMatrix;
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
			//RWSection_Geometry *pGeometry = (RWSection_Geometry*)pMaterial->getParentNode()->getParentNode();
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY)[uiGeometryIndex];
			vector<RWSection*> vecStrings = pMaterial->getSectionsByType(RW_SECTION_STRING);
			bool bMeshUsesTexture = vecStrings.size() > 0;
			bool bUsesNormals = pGeometry->getBoundingInfo().doesHaveNormals();

			if (bMeshUsesTexture)
			{
				string strTextureName = ((RWSection_String*)vecStrings[0])->getData();
				string strTextureNameLower = String::toLowerCase(strTextureName);

				bMeshUsesTexture = strTextureName != "";
				if (bMeshUsesTexture)
				{
					bMeshUsesTexture = textureIndices.count(strTextureNameLower) > 0;

					if (bMeshUsesTexture)
					{
						GLuint uiTextureID = textureIndices[strTextureNameLower];
						glBindTexture(GL_TEXTURE_2D, uiTextureID);
					}
				}
			}

			
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex]);
			//glVertexAttrib3f((GLuint)1, 0.8f, 0.0, 0.0); // set constant color attribute
			
			/*
			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[uiGeometryIndex]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiMeshIndex]);

			
			glEnableClientState(GL_NORMAL_ARRAY);
			

			glTexCoordPointer(3, GL_FLOAT, 0, 0);
			glNormalPointer(GL_FLOAT, 0, 0);
			*/

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiMeshIndex]);

			//glDrawArrays(pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP, 0, pGeometry->getVertexPositions().size());
			glDrawElements(pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP, pMesh->getVertexIndices().size(), GL_UNSIGNED_INT, 0);

			///*
			glDisableClientState(GL_VERTEX_ARRAY);
			//glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//*/

			/*
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[uiGeometryIndex]);
			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);
			glBindBuffer(GL_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiMeshIndex]);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			//glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[uiGeometryIndex]);

			glTexCoordPointer(3, GL_FLOAT, sizeof(GLfloat) * 8, (float*)(sizeof(GLfloat) * 5));
			glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 8, (float*)(sizeof(GLfloat) * 3));
			glVertexPointer(3, GL_FLOAT, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[uiGeometryIndex][uiMeshIndex]);

			//glVertexAttrib3f((GLuint)1, 1.0, 0.5f, 0.0); // set constant color attribute

			glDrawElements(pBinMeshPLG->getFlags() == 0 ? GL_TRIANGLES : GL_TRIANGLE_STRIP, pMesh->getVertexIndices().size(), GL_UNSIGNED_INT, 0);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			*/

			/*
			if (pBinMeshPLG->getFlags() == 0)
			{
				// triangle list
				glBegin(GL_TRIANGLES);
			}
			else
			{
				// triangle strip
				glBegin(GL_TRIANGLE_STRIP);
			}

			uint32 uiTriangleIndex = 0;
			uint32 uiVertexIndex = 0;
			for (uint32 uiIndex : pMesh->getVertexIndices())
			{
				Vec3f& vecPoint = pGeometry->getVertexPositions()[uiIndex];
				Vec2f& vecTexCoords = pGeometry->getTextureCoordinates()[uiIndex];
				Vec3f vecNormal;
				if (bUsesNormals)
				{
					//vecNormal = pGeometry->getVertexNormals()[uiVertexIndex / 3];
					vecNormal = pGeometry->getVertexNormals()[uiIndex];
				}

				if (bMeshUsesTexture)
				{
					glTexCoord2f(vecTexCoords.x, vecTexCoords.y);
				}
				//glColor4ub(vecColour3.x, vecColour3.y, vecColour3.z, vecColour3.w);
				//glColor4ub(0, 0, 255, 255);
				if (bUsesNormals)
				{
					//if ((uiVertexIndex % 3) == 0)
					//{
					glNormal3f(vecNormal.x, vecNormal.z, vecNormal.y);
					//}
				}
				glVertex3f(vecPoint.x, vecPoint.z, vecPoint.y);
				uiVertexIndex++;
			}
			glEnd();
			*/

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

	//glPopMatrix();
	m_matModelViewMatrix.pop();
}



void						ModelEditorTab::createGLContext(void)
{
	//if (bGlewInitialized)return true;

	//RegisterSimpleOpenGLClass(hInstance);

	HWND hWndFake = CreateWindow(L"a", L"FAKE", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN,
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	HDC hDC = GetDC(hWndFake);

	// First, choose false pixel format

	PIXELFORMATDESCRIPTOR pfd2;
	memset(&pfd2, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd2.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd2.nVersion = 1;
	pfd2.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd2.iPixelType = PFD_TYPE_RGBA;
	pfd2.cColorBits = 32;
	pfd2.cDepthBits = 32;
	pfd2.iLayerType = PFD_MAIN_PLANE;

	int iPixelFormat = ChoosePixelFormat(hDC, &pfd2);
	if (iPixelFormat == 0)return;

	if (!SetPixelFormat(hDC, iPixelFormat, &pfd2))return;

	// Create the false, old style context (OpenGL 2.1 and before)

	HGLRC hRCFake = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRCFake);

	bool bResult = true;

	//if (!bGlewInitialized)
	//{
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		MessageBox(m_pWindow->getWindowHandle(), L"Couldn't initialize GLEW!", L"Fatal Error", MB_ICONERROR);
		bResult = false;
	}
	//bGlewInitialized = true;
	//}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCFake);
	DestroyWindow(hWndFake);










	int32 iMajorVersion = 3;
	int iMinorVersion = 0;

	//if (!initGLEW(hInstance))return false;

	m_hDC = CreateCompatibleDC(m_hdcWindow);
	m_hbm = CreateCompatibleBitmap(m_hdcWindow, m_vecRenderSize.x, m_vecRenderSize.y);
	SelectObject(m_hDC, m_hbm);

	//HWND hWnd = m_pWindow->getWindowHandle();
	//hDC = GetDC(hWnd);

	bool bError = false;
	PIXELFORMATDESCRIPTOR pfd3;

	if (iMajorVersion <= 2)
	{
		memset(&pfd3, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd3.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd3.nVersion = 1;
		pfd3.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pfd3.iPixelType = PFD_TYPE_RGBA;
		pfd3.cColorBits = 32;
		pfd3.cDepthBits = 32;
		pfd3.iLayerType = PFD_MAIN_PLANE;

		int iPixelFormat = ChoosePixelFormat(m_hDC, &pfd3);
		if (iPixelFormat == 0)return;

		if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd3))return;

		// Create the old style context (OpenGL 2.1 and before)
		m_hRC = wglCreateContext(m_hDC); // local?
		if (m_hRC)
			wglMakeCurrent(m_hDC, m_hRC);
		else
			bError = true;
	}
	else if (WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			//GL_ARB_framebuffer_object, GL_TRUE,
			0 // End of attributes list
		};
		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, iMajorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, iMinorVersion,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(m_hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

		// PFD seems to be only redundant parameter now
		if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd3))return;

		m_hRC = wglCreateContextAttribsARB(m_hDC, 0, iContextAttribs);
		// If everything went OK
		if (m_hRC) wglMakeCurrent(m_hDC, m_hRC);
		else bError = true;

	}





	int c = glGetError();
	if (c != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}
}

void						ModelEditorTab::prepareScene(void)
{
	prepareGLStates();
	prepareShaders();
	prepareShaderData();
	prepareFBO();
	//prepareAxis();
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
	// setup shader 1

	string strVertexShader = File::getFileContent(string("C:\\Users\\James Baxter\\Desktop\\GitHub Repos\\IMGF\\Code\\IMGF\\GUI\\Editor\\Editors\\Tab\\Shader\\VertexShader.glsl"), false); // todo
	const char *pVertexShader = strVertexShader.c_str();
	const GLint uiVertexShaderLength = strVertexShader.length();

	GLuint shader = glCreateShader(GL_VERTEX_SHADER);

	int ee4 = glGetError();
	if (ee4 != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	glShaderSource(shader, 1, &pVertexShader, NULL);

	int ee3 = glGetError();
	if (ee3 != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	glCompileShader(shader);

	int ee = glGetError();
	if (ee != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	int h = 0;
	h++;

	// setup shader 2

	string strFragmentShader = File::getFileContent(string("C:\\Users\\James Baxter\\Desktop\\GitHub Repos\\IMGF\\Code\\IMGF\\GUI\\Editor\\Editors\\Tab\\Shader\\FragmentShader.glsl"), false); // todo
	const char *pFragmentShader = strFragmentShader.c_str();
	const GLint uiFragmentShaderLength = strFragmentShader.length();

	GLuint shader2 = glCreateShader(GL_FRAGMENT_SHADER);

	int ee41 = glGetError();
	if (ee41 != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	glShaderSource(shader2, 1, &pFragmentShader, NULL);

	int ee31 = glGetError();
	if (ee31 != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	glCompileShader(shader2);

	int ee33 = glGetError();
	if (ee33 != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	GLint isCompiled2 = 0;
	glGetShaderiv(shader2, GL_COMPILE_STATUS, &isCompiled2);
	int h2 = 0;
	h2++;

	// create opengl program

	m_program = glCreateProgram();
	
	glAttachShader(m_program, shader);
	glAttachShader(m_program, shader2);

	glBindAttribLocation(m_program, 0, "in_Position");
	glBindAttribLocation(m_program, 1, "in_Color");

	glLinkProgram(m_program);

	glUseProgram(m_program);
}

void							ModelEditorTab::prepareAxis(void)
{
	float32 axisCoordinates[6][3];

	// X
	axisCoordinates[0][0] = -5000.0f;
	axisCoordinates[0][1] = 0.0f;
	axisCoordinates[0][2] = 0.0f;

	axisCoordinates[1][0] = 5000.0f;
	axisCoordinates[1][1] = 0.0f;
	axisCoordinates[1][2] = 0.0f;

	// Y
	axisCoordinates[2][0] = 0.0f;
	axisCoordinates[2][1] = 0.0f;
	axisCoordinates[2][2] = -5000.0f;

	axisCoordinates[3][0] = 0.0f;
	axisCoordinates[3][1] = 0.0f;
	axisCoordinates[3][2] = 5000.0f;

	// Z
	axisCoordinates[4][0] = 0.0f;
	axisCoordinates[4][1] = -5000.0f;
	axisCoordinates[4][2] = 0.0f;

	axisCoordinates[5][0] = 0.0f;
	axisCoordinates[5][1] = 5000.0f;
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

	glGenVertexArrays(1, &axisBuffer);
	glBindVertexArray(axisBuffer);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float32) * 3 * 6, &axisCoordinates[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Position"));
	
	glGenBuffers(1, &m_vboColours);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboColours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 6, axisColours, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(m_program, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Color"));
}

void							ModelEditorTab::prepareMeshes(void)
{
	uint32 uiGeometryCount = m_pDFFFile->getSectionCountByType(RW_SECTION_GEOMETRY);

	//m_pGeometryVertexPositionBuffers = new GLuint[uiGeometryCount];

	m_pGeometryVertexPositionBuffers.resize(uiGeometryCount);
	m_pGeometryVertexNormalBuffers.resize(uiGeometryCount);
	m_pGeometryTexturePositionBuffers.resize(uiGeometryCount);
	m_pBinMeshDataIndexBuffers.resize(uiGeometryCount);

	m_pGeometryVertexArrayBuffers.resize(uiGeometryCount);

	m_pVertexPositionBuffer.resize(uiGeometryCount);
	m_pDataIndexBuffer.resize(uiGeometryCount);

	//GetAnyGLFuncAddress("glGenBuffers");
	//glGenBuffers(uiGeometryCount, &m_pGeometryVertexPositionBuffers[0]);
	//glGenBuffers(uiGeometryCount, &m_pGeometryVertexPositionBuffers[0]);

	// prepare 3d buffers
	uint32 uiGeometryIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		RWSection_Geometry *pGeometry = (RWSection_Geometry*)pRWSection;
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];



		//GLuint g[2] = { 0, 0 };
		//glGenBuffers(2, &g[0]);

		//GLuint h = 12345;
		//glGenBuffers(1, &h);

		//int c = glGetError();



		// vertex positions
		uint32 uiSize1 = pGeometry->getVertexPositions().size() * sizeof(float32) * 3;
		string strData1 = "";
		for (Vec3f& vecPosition : pGeometry->getVertexPositions())
		{
			strData1 += String::packFloat32(vecPosition.x, false);
			strData1 += String::packFloat32(vecPosition.z, false);
			strData1 += String::packFloat32(vecPosition.y, false);
		}
		m_pVertexPositionBuffer[uiGeometryIndex] = strData1.c_str();

		m_pGeometryVertexPositionBuffers[uiGeometryIndex] = 0;
		glGenVertexArrays(1, &m_pGeometryVertexArrayBuffers[uiGeometryIndex]);
		glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex]);
		glGenBuffers(1, &m_pGeometryVertexPositionBuffers[uiGeometryIndex]);

		glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[uiGeometryIndex]);
		glBufferData(GL_ARRAY_BUFFER, uiSize1, m_pVertexPositionBuffer[uiGeometryIndex], GL_STATIC_DRAW);

		glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Position"));

		// vertex normals
		glGenBuffers(1, &m_pGeometryVertexNormalBuffers[uiGeometryIndex]);

		glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[uiGeometryIndex]);
		glBufferData(GL_ARRAY_BUFFER, pGeometry->getVertexNormals().size() * sizeof(float32) * 3, pGeometry->getVertexNormals().data(), GL_STATIC_DRAW);

		glVertexAttribPointer(glGetAttribLocation(m_program, "inNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(m_program, "inNormal"));

		// texture coordinates
		glGenBuffers(1, &m_pGeometryTexturePositionBuffers[uiGeometryIndex]);

		glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[uiGeometryIndex]);
		glBufferData(GL_ARRAY_BUFFER, pGeometry->getTextureCoordinates().size() * sizeof(float32) * 2, pGeometry->getTextureCoordinates().data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(glGetAttribLocation(m_program, "in_Texcoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Texcoord"));

		// data indices
		m_pBinMeshDataIndexBuffers[uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());
		m_pDataIndexBuffer[uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());

		uint32 uiGeometryMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
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
}

void					ModelEditorTab::prepareTextures(void)
{
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

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

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
}

void					ModelEditorTab::prepareGLStates(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void							ModelEditorTab::prepareShaderData(void)
{
	//return;

	// setup projection matrix

	m_matProjectionMatrix.push(glm::mat4(1.0f));
	m_matProjectionMatrix.top() *= glm::perspective(45.0f, (float32)m_vecRenderSize.x / (float32)m_vecRenderSize.y, 0.1f, 200.0f);


	// setup modelview matrix (look down the negative z-axis)

	m_matModelViewMatrix.push(glm::mat4(1.0f));
	m_matModelViewMatrix.top() *= glm::lookAt(glm::vec3(-2.0f, -2.0f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	// create and upload modelviewprojection matrix

	int rrr = glGetError();
	if (rrr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	//m_matModelViewProjectionMatrix = m_matProjectionMatrix * m_matModelViewMatrix;
	GLint vvv = glGetUniformLocation(m_program, "Projection");

	int rrrr = glGetError();
	if (rrrr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	glUniformMatrix4fv(glGetUniformLocation(m_program, "Projection"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "ModelView"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));
	
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