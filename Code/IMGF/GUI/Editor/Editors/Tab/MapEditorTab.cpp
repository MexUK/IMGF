#include "MapEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "Format/IDE/IDEFormat.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_OBJS.h"
#include "Format/IPL/IPLFormat.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_INST.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/TXD/TXDManager.h"
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
#include "Format/EFileType.h"
#include "Static/DataPath.h"
#include <stack>

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

MapEditorTab::MapEditorTab(void) :
	m_pDATLoaderFile(nullptr),
	m_bInitialized(false),
	m_bInitializing(false),
	m_bFilesAreInitialized(false)
{
	m_vecRenderSize.x = 800;
	m_vecRenderSize.y = 800;
}

// controls
void						MapEditorTab::storeControls(void)
{
	onResizeWindow(Vec2i(0, 0));
}

void						MapEditorTab::onResizeWindow(Vec2i& vecSizeChange)
{
	if (!m_bInitialized)
	{
		return;
	}

	// todo
	//Vec2u vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);
	m_vecRenderSize = Vec2u(800, 800);

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
void						MapEditorTab::bindEvents(void)
{
	bindEvent(MOVE_MOUSE_WHEEL, &MapEditorTab::onMouseWheelMove2);
	bindEvent(RESIZE_WINDOW, &MapEditorTab::onResizeWindow);

	EditorTab::bindEvents();
}

void						MapEditorTab::unbindEvents(void)
{
	unbindEvent(MOVE_MOUSE_WHEEL, &MapEditorTab::onMouseWheelMove2);
	unbindEvent(RESIZE_WINDOW, &MapEditorTab::onResizeWindow);
	
	EditorTab::unbindEvents();
}

// event callbacks
void						MapEditorTab::onMouseWheelMove2(int16 iRotationDistance)
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
bool						MapEditorTab::unserializeFile(void)
{
	string strGameFolderPath = Path::getDirectory(m_pDATLoaderFile->getFilePath()) + "../";

	// load DAT Loader file
	m_pDATLoaderFile->unserialize();

	// load IDE files
	unordered_map<string, bool> umapModelsUsedByIDE;
	unordered_map<string, bool> umapTexturesUsedByIDE;

	uint32 uiFileCount = 0;

	for (string& strRelativeIDEFilePath : m_pDATLoaderFile->getRelativeIDEPaths())
	{
		//if (uiFileCount == 4) break;

		if (String::toLowerCase(strRelativeIDEFilePath).find("golf") == string::npos)
		{
			continue;
		}

		IDEFormat ideFile(strGameFolderPath + strRelativeIDEFilePath, true);
		if (ideFile.unserialize())
		{
			// load IDE file
			for (IDEEntry *pIDEEntry : ideFile.getSectionEntries()[IDE_SECTION_OBJS])
			{
				if (pIDEEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
				{
					if (pIDEEntry->getSectionType() == IDE_SECTION_OBJS)
					{
						IDEEntry_OBJS *pEntry_OBJS = (IDEEntry_OBJS*)pIDEEntry;

						MapModel *pMapModel = new MapModel;
						pMapModel->m_uiObjectId = pEntry_OBJS->getObjectId();
						pMapModel->m_strModelName = String::toLowerCase(pEntry_OBJS->getModelName());
						pMapModel->m_strTXDName = String::toLowerCase(pEntry_OBJS->getTXDName());

						m_umapMapModels[pEntry_OBJS->getObjectId()] = pMapModel;
						umapModelsUsedByIDE[pMapModel->m_strModelName] = true;
						umapTexturesUsedByIDE[pMapModel->m_strTXDName] = true;
					}
				}
			}
		}

		uiFileCount++;
	}

	// load IPL files
	unordered_map<uint32, Vec3f> umapObjectPositionsByObjectId;

	uiFileCount = 0;

	for (string& strRelativeIPLFilePath : m_pDATLoaderFile->getRelativeIPLPaths())
	{
		//if (uiFileCount == 4) break;

		if (String::toLowerCase(strRelativeIPLFilePath).find("golf") == string::npos)
		{
			continue;
		}

		IPLFormat iplFile(strGameFolderPath + strRelativeIPLFilePath, true);
		if (iplFile.unserialize())
		{
			// load IPL file
			for (IPLEntry *pIPLEntry : iplFile.getSectionEntries()[IPL_SECTION_INST])
			{
				if (pIPLEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
				{
					if (pIPLEntry->getSectionType() == IPL_SECTION_INST)
					{
						IPLEntry_INST *pIPL_INST = (IPLEntry_INST*)pIPLEntry;

						MapObject *pMapObject = new MapObject;
						pMapObject->m_vecPosition = pIPL_INST->getPosition();
						m_umapMapObjects[pIPL_INST->getObjectId()] = pMapObject;
					}
				}
			}
		}

		uiFileCount++;
	}

	// load IMG files
	string strIMGFilePath = strGameFolderPath + "models/gta3.img";

	IMGFormat imgFileMeta(strIMGFilePath, true);
	if (imgFileMeta.readMetaData())
	{
		IMGFormat *pIMGFile = IMGFormat::createIMGFormat(imgFileMeta.getVersion(), strIMGFilePath, true);

		if (pIMGFile->unserialize())
		{
			// load DFF + TXD files
			for (IMGEntry *pIMGEntry : pIMGFile->getEntries())
			{
				string strEntryNameLower = String::toLowerCase(Path::removeFileExtension(pIMGEntry->getEntryName()));

				if (pIMGEntry->getEntryType() == MODEL)
				{
					if (umapModelsUsedByIDE.count(strEntryNameLower) == 0)
					{
						continue;
					}

					DFFFormat *pDFFFile = new DFFFormat(pIMGEntry->getEntryData(), false);
					if (pDFFFile->unserialize())
					{
						m_umapDFFsByModelNameLower[strEntryNameLower] = pDFFFile;
					}
				}
				else if (pIMGEntry->getEntryType() == TEXTURE)
				{
					if (umapTexturesUsedByIDE.count(strEntryNameLower) == 0)
					{
						continue;
					}

					TXDFormat *pTXDFile = new TXDFormat(pIMGEntry->getEntryData(), false);
					if (pTXDFile->unserialize())
					{
						m_umapTXDsByModelNameLower[strEntryNameLower] = pTXDFile;
					}
				}
			}
		}
	}

	m_bFilesAreInitialized = true;
	return true;
}

void						MapEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// render
	getLayer()->getWindow()->render();
}

// file info text
void						MapEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	//m_pText_FileVersion->setText(getDFFFile()->getRWVersion()->getVersionText(), false);
	//m_pText_FileGame->setText(getDFFFile()->getRWVersion()->getGamesAsString());

	updateEntryCountText();
}

void						MapEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = m_pDATLoaderFile->getEntryCount(),
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
void						MapEditorTab::render_Type1(void)
{
}

// render 3d
mutex mutexInitializing3DRender_MapEditor; // todo

void						MapEditorTab::render(void)
{
	render3D();
}

void						MapEditorTab::render3D(void)
{
	if (!m_bFilesAreInitialized)
	{
		return;
	}

	if (m_bInitializing)
	{
		return;
	}

	mutexInitializing3DRender_MapEditor.lock();
	if (!m_bInitialized)
	{
		m_bInitializing = true;
		
		m_vecRenderSize = Vec2u(800, 800);
		//m_vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);
		m_hdcWindow = GetDC(getLayer()->getWindow()->getWindowHandle());

		createGLContext();
		prepareScene();
		reshape();

		m_bInitialized = true;
		m_bInitializing = false;
	}
	mutexInitializing3DRender_MapEditor.unlock();





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	int c = glGetError();
	if (c != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}






	
	
	
	



	// render model
	glUseProgram(m_program);

	glUniformMatrix4fv(glGetUniformLocation(m_program, "Projection"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

	renderMap();

	//SwapBuffers(m_hDC);





	




	
	// render axis
	///*
	glUseProgram(m_program2);

	// Get the variables from the shader to which data will be passed
	GLint ploc = glGetUniformLocation(m_program2, "Projection");
	GLint mvloc = glGetUniformLocation(m_program2, "Model");

	// Pass the model-view matrix to the shader
	//GLfloat mvMat[16];
	//glGetFloatv(GL_MODELVIEW_MATRIX, mvMat);
	glUniformMatrix4fv(mvloc, 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

	// Pass the projection matrix to the shader
	//GLfloat pMat[16];
	//glGetFloatv(GL_PROJECTION_MATRIX, pMat);
	glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));

	glBindVertexArray(axisBuffer);		// select first VAO
										//glVertexAttrib3f((GLuint)1, 0.8f, 0.0, 0.0); // set constant color attribute
	glDrawArrays(GL_LINES, 0, 6);	// draw first object
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//*/


	

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
	//pixels 0, 1, 2 should be white
	//pixel 4 should be black
	//----------------
	//Bind 0, which means render to back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glFinish();

	// gdi - draw 2d bitmap
	HGDIOBJ hOld2 = SelectObject(hdc2, hbm2);
	BitBlt(m_hdcWindow, 0, 0, m_vecRenderSize.x, m_vecRenderSize.y, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hOld2);

	// clean up gdi
	DeleteObject(hbm2);
	DeleteDC(hdc2);
}

// camera
void						MapEditorTab::zoomCamera(float32 fRadius)
{
	Vec3f vecCameraRotation = getCameraRotation();
	float32 fXAngle = vecCameraRotation.x;// Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z - Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fRadius, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	m_vecCameraPosition = m_vecCameraPosition + vecCameraPositionOffset;
	m_vecCameraLookAtPosition = m_vecCameraLookAtPosition + vecCameraPositionOffset;
}

Vec3f						MapEditorTab::getCameraRotation(void)
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

float32						MapEditorTab::getCameraZRotation(void)
{
	return Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f); // Z
}

// render 3d components
void						MapEditorTab::renderCamera(void)
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

void						MapEditorTab::renderMap(void)
{
	// for each IPL entry, create object (IDE), IDE uses DFF and TXD, which came from IMG
	for (auto it : m_umapMapObjects)
	{
		uint32 uiObjectId = it.first;
		MapObject *pMapObject = it.second;

		if (m_umapMapModels.count(uiObjectId) == 0)
		{
			continue;
		}

		MapModel *pMapModel = m_umapMapModels[uiObjectId];




		



		string& strDFFNameLower = pMapModel->m_strModelName;
		string& strTXDNameLower = pMapModel->m_strTXDName;

		if (m_umapDFFsByModelNameLower.count(strDFFNameLower))
		{
			///*
			m_matModelViewMatrix.top() = glm::translate(m_matModelViewMatrix.top(), glm::vec3(pMapObject->m_vecPosition.x, pMapObject->m_vecPosition.z, pMapObject->m_vecPosition.y));
			//m_matModelViewMatrix.top() = glm::translate(m_matModelViewMatrix.top(), glm::vec3(654.1593018, 0, -1550.650391));

			glUseProgram(m_program2);
			glUniformMatrix4fv(glGetUniformLocation(m_program2, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

			glUseProgram(m_program);
			glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));
			//*/








			renderModel(m_umapDFFsByModelNameLower[strDFFNameLower]);








			m_matModelViewMatrix.top() = glm::translate(m_matModelViewMatrix.top(), glm::vec3(-pMapObject->m_vecPosition.x, -pMapObject->m_vecPosition.z, -pMapObject->m_vecPosition.y));

			glUseProgram(m_program2);
			glUniformMatrix4fv(glGetUniformLocation(m_program2, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

			glUseProgram(m_program);
			glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));
		}
	}
}

void						MapEditorTab::renderModel(DFFFormat *pDFFFile)
{
	glEnable(GL_TEXTURE_2D);

	vector<RWSection*> vecAtomics = pDFFFile->getSectionsByType(RW_SECTION_ATOMIC);
	unordered_map<uint32, RWSection_Atomic*> umapAtomics;
	unordered_map<uint32, uint32> umapGeometryIndices;
	for (RWSection *pRWSection : vecAtomics)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic *)pRWSection;
		int32 iFrameIndex = pAtomic->getFrameIndex();
		umapAtomics[iFrameIndex] = pAtomic;
		umapGeometryIndices[iFrameIndex] = pAtomic->getGeometryIndex();
	}

	RWSection_FrameList *pFrameList = (RWSection_FrameList *)pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

	uint32 uiFrameIndex = 0;
	for (RWSection *pRWSection : pDFFFile->getSectionsByType(RW_SECTION_FRAME))
	{
		RWSection_Frame *pFrame = (RWSection_Frame*)pRWSection;
		uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

		if (uiParentFrameIndex == -1)
		{
			renderFrame(pDFFFile, uiFrameIndex, pFrame, true);
		}

		uiFrameIndex++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
}

void						MapEditorTab::renderFrame(DFFFormat *pDFFFile, uint32 uiFrameIndex, RWSection_Frame *pFrame, bool bIsParentFrame)
{
	m_matModelViewMatrix.push(m_matModelViewMatrix.top());
	glColor4f(1.0, 0.2, 1.0, 1.0);

	vector<RWSection*> vecAtomics = pDFFFile->getSectionsByType(RW_SECTION_ATOMIC);
	unordered_map<uint32, RWSection_Atomic*> umapAtomics;
	unordered_map<uint32, uint32> umapGeometryIndices;
	for (RWSection *pRWSection : vecAtomics)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic *)pRWSection;
		int32 iFrameIndex = pAtomic->getFrameIndex();
		umapAtomics[iFrameIndex] = pAtomic;
		umapGeometryIndices[iFrameIndex] = pAtomic->getGeometryIndex();
	}

	RWSection_FrameList *pFrameList = (RWSection_FrameList *)pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

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
		m_matModelViewMatrix.top() *= matMultMatrix;
		//m_matProjectionMatrix *= matMultMatrix;

		glUseProgram(m_program2);
		glUniformMatrix4fv(glGetUniformLocation(m_program2, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

		glUseProgram(m_program);
		glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));
	}

	if (umapAtomics.count(uiFrameIndex) != 0)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic*)umapAtomics[uiFrameIndex];
		uint32 uiGeometryIndex = pAtomic->getGeometryIndex();
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		uint32 uiMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			uint32 uiMaterialIndex = pMesh->getMaterialIndex();
			vector<RWSection*> vecMaterials = pBinMeshPLG->getParentNode()->getParentNode()->getSectionsByType(RW_SECTION_MATERIAL);
			RWSection_Material *pMaterial = (RWSection_Material*)vecMaterials[uiMaterialIndex];
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY)[uiGeometryIndex];
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

			//glBindVertexArray(m_pGeometryVertexArrayBuffers[uiGeometryIndex][uiMeshIndex]);
			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[pDFFFile][uiGeometryIndex]);
			glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
			if (bUsesNormals)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[pDFFFile][uiGeometryIndex]);
				glVertexAttribPointer(glGetAttribLocation(m_program, "inNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
			}
			if (bMeshUsesTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textureIndices[strTextureNameLower]);
				glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[pDFFFile][uiGeometryIndex]);
				glVertexAttribPointer(glGetAttribLocation(m_program, "in_Texcoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[pDFFFile][uiGeometryIndex][uiMeshIndex]);

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
		RWSection_Frame *pFrame = (RWSection_Frame*)pDFFFile->getSectionsByType(RW_SECTION_FRAME)[uiFrameIndex2];
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
						renderFrame(pDFFFile, uiFrameIndex2, pFrame, true);
					}
				}
				else if (strFrameName.substr(1, 3) != "Col")
				{
					renderFrame(pDFFFile, uiFrameIndex2, pFrame, false);
				}
			}
			else
			{
				renderFrame(pDFFFile, uiFrameIndex2, pFrame, false);
			}
		}
	}

	m_matModelViewMatrix.pop();
}



void						MapEditorTab::createGLContext(void)
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
		MessageBox(getLayer()->getWindow()->getWindowHandle(), L"Couldn't initialize GLEW!", L"Fatal Error", MB_ICONERROR);
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

void						MapEditorTab::prepareScene(void)
{
	prepareGLStates();
	prepareShaders();
	prepareShaderData();
	prepareFBO();
	prepareAxis();
	prepareMap();
}

void						MapEditorTab::reshape(void)
{
	glViewport(0, 0, m_vecRenderSize.x, m_vecRenderSize.y);
}

void						MapEditorTab::drawScene(void)
{
}

void						MapEditorTab::destroyScene(void)
{
}

void						MapEditorTab::prepareShaders(void)
{
	// setup program 1
	GLuint shader1 = m_gl.prepareShader(GL_VERTEX_SHADER, DataPath::getDataPath() + "Shaders/MapEditor/VertexShader-Texture.glsl");
	GLuint shader2 = m_gl.prepareShader(GL_FRAGMENT_SHADER, DataPath::getDataPath() + "Shaders/MapEditor/FragmentShader-Texture.glsl");

	// create opengl program
	m_program = glCreateProgram();

	glAttachShader(m_program, shader1);
	glAttachShader(m_program, shader2);

	glLinkProgram(m_program);
	glUseProgram(m_program);

	// setup program 2
	GLuint shader3 = m_gl.prepareShader(GL_VERTEX_SHADER, DataPath::getDataPath() + "Shaders/MapEditor/VertexShader-Colour.glsl");
	GLuint shader4 = m_gl.prepareShader(GL_FRAGMENT_SHADER, DataPath::getDataPath() + "Shaders/MapEditor/FragmentShader-Colour.glsl");

	m_program2 = glCreateProgram();

	glAttachShader(m_program2, shader3);
	glAttachShader(m_program2, shader4);

	glLinkProgram(m_program2);
	glUseProgram(m_program2);
}

void							MapEditorTab::prepareAxis(void)
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

void							MapEditorTab::prepareMap(void)
{
	// for each IDE entry, create object (IDE), IDE uses DFF and TXD, which came from IMG
	for (auto it : m_umapMapModels)
	{
		uint32 uiObjectId = it.first;
		MapModel *pMapModel = it.second;

		string& strDFFNameLower = pMapModel->m_strModelName;
		string& strTXDNameLower = pMapModel->m_strTXDName;

		if (m_umapDFFsByModelNameLower.count(strDFFNameLower))
		{
			prepareModel(m_umapDFFsByModelNameLower[strDFFNameLower]);
		}
		if (m_umapTXDsByModelNameLower.count(strTXDNameLower))
		{
			prepareTXD(m_umapTXDsByModelNameLower[strTXDNameLower]);
		}
	}
}

void							MapEditorTab::prepareModel(DFFFormat *pDFFFile)
{
	glUseProgram(m_program);

	uint32 uiGeometryCount = pDFFFile->getSectionCountByType(RW_SECTION_GEOMETRY);

	m_pGeometryVertexPositionBuffers[pDFFFile].resize(uiGeometryCount);
	m_pGeometryVertexNormalBuffers[pDFFFile].resize(uiGeometryCount);
	m_pGeometryTexturePositionBuffers[pDFFFile].resize(uiGeometryCount);
	m_pBinMeshDataIndexBuffers[pDFFFile].resize(uiGeometryCount);

	m_pGeometryVertexArrayBuffers[pDFFFile].resize(uiGeometryCount);

	m_pVertexPositionBuffer[pDFFFile].resize(uiGeometryCount);
	m_pVertexNormalBuffer[pDFFFile].resize(uiGeometryCount);
	m_pTextureCoordinateBuffer[pDFFFile].resize(uiGeometryCount);
	m_pDataIndexBuffer[pDFFFile].resize(uiGeometryCount);

	// prepare 3d buffers
	uint32 uiGeometryIndex = 0;
	for (RWSection *pRWSection : pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		RWSection_Geometry *pGeometry = (RWSection_Geometry*)pRWSection;
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		vector<RWSection*> vecStrings = pGeometry->getSectionsByType(RW_SECTION_STRING);
		bool bMeshUsesTexture = vecStrings.size() > 0;
		if (bMeshUsesTexture)
		{
			string strTextureNameLower = String::toLowerCase(((RWSection_String*)vecStrings[0])->getData());
			m_umapGeometryIndexByTextureNameLower[strTextureNameLower] = uiGeometryIndex;
		}

		/*
		uint32 uiSize1 = pGeometry->getVertexPositions().size() * sizeof(float32) * 3;
		string strData1 = "";
		for (Vec3f& vecPosition : pGeometry->getVertexPositions())
		{
			strData1 += String::packFloat32(vecPosition.x, false);
			strData1 += String::packFloat32(vecPosition.z, false);
			strData1 += String::packFloat32(vecPosition.y, false);
		}
		m_pVertexPositionBuffer[pDFFFile][uiGeometryIndex] = strData1.c_str();

		uint32 uiSize4 = pGeometry->getVertexNormals().size() * sizeof(float32) * 3;
		string strData4 = "";
		for (Vec3f& vecNormal : pGeometry->getVertexNormals())
		{
			strData4 += String::packFloat32(vecNormal.x, false);
			strData4 += String::packFloat32(vecNormal.z, false);
			strData4 += String::packFloat32(vecNormal.y, false);
		}
		m_pVertexNormalBuffer[pDFFFile][uiGeometryIndex] = strData4.c_str();

		uint32 uiSize3 = pGeometry->getTextureCoordinates().size() * sizeof(float32) * 2;
		string strData3 = "";
		for (Vec2f& vecTextureCoordinates : pGeometry->getTextureCoordinates())
		{
			strData3 += String::packFloat32(vecTextureCoordinates.x, false);
			strData3 += String::packFloat32(vecTextureCoordinates.y, false);
		}
		m_pTextureCoordinateBuffer[pDFFFile][uiGeometryIndex] = strData3.c_str();
		*/

		uint32 uiSize1 = pGeometry->getVertexPositions().size() * sizeof(float32) * 3;
		m_pVertexPositionBuffer[pDFFFile][uiGeometryIndex] = (char*) pGeometry->getVertexPositions().data();

		uint32 uiSize4 = pGeometry->getVertexNormals().size() * sizeof(float32) * 3;
		m_pVertexNormalBuffer[pDFFFile][uiGeometryIndex] = (char*) pGeometry->getVertexNormals().data();

		uint32 uiSize3 = pGeometry->getTextureCoordinates().size() * sizeof(float32) * 2;
		m_pTextureCoordinateBuffer[pDFFFile][uiGeometryIndex] = (char*) pGeometry->getTextureCoordinates().data();

		
		

		
		

		// data indices
		m_pBinMeshDataIndexBuffers[pDFFFile][uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());
		m_pDataIndexBuffer[pDFFFile][uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());
		m_pGeometryVertexArrayBuffers[pDFFFile][uiGeometryIndex].resize(pBinMeshPLG->getMeshCount());

		uint32 uiGeometryMeshIndex = 0;
		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			// VAO
			//glGenVertexArrays(1, &m_pGeometryVertexArrayBuffers[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex]);
			//glBindVertexArray(m_pGeometryVertexArrayBuffers[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex]);

			// vertex positions
			m_pGeometryVertexPositionBuffers[pDFFFile][uiGeometryIndex] = 0;
			glGenBuffers(1, &m_pGeometryVertexPositionBuffers[pDFFFile][uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexPositionBuffers[pDFFFile][uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize1, m_pVertexPositionBuffer[pDFFFile][uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Position"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// vertex normals
			glGenBuffers(1, &m_pGeometryVertexNormalBuffers[pDFFFile][uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryVertexNormalBuffers[pDFFFile][uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize4, m_pVertexNormalBuffer[pDFFFile][uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "inNormal"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "inNormal"), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// texture coordinates
			glGenBuffers(1, &m_pGeometryTexturePositionBuffers[pDFFFile][uiGeometryIndex]);

			glBindBuffer(GL_ARRAY_BUFFER, m_pGeometryTexturePositionBuffers[pDFFFile][uiGeometryIndex]);
			glBufferData(GL_ARRAY_BUFFER, uiSize3, m_pTextureCoordinateBuffer[pDFFFile][uiGeometryIndex], GL_STATIC_DRAW);

			glEnableVertexAttribArray(glGetAttribLocation(m_program, "in_Texcoord"));
			glVertexAttribPointer(glGetAttribLocation(m_program, "in_Texcoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// data index
			uint32 uiSize2 = pMesh->getVertexIndices().size() * sizeof(uint32);
			string strData2 = "";
			for (uint32 uiDataIndex : pMesh->getVertexIndices())
			{
				strData2 += String::packUint32(uiDataIndex, false);
			}
			m_pDataIndexBuffer[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex] = strData2.c_str();





			glGenBuffers(1, &m_pBinMeshDataIndexBuffers[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBinMeshDataIndexBuffers[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize2, m_pDataIndexBuffer[pDFFFile][uiGeometryIndex][uiGeometryMeshIndex], GL_STATIC_DRAW);

			uiGeometryMeshIndex++;
		}

		uiGeometryIndex++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void					MapEditorTab::prepareTXD(TXDFormat *pTXDFile)
{
	glUseProgram(m_program);

	vector<RWSection*> vecTextures = pTXDFile->getSectionsByType(RW_SECTION_TEXTURE_NATIVE);
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

		delete[] a;

		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void					MapEditorTab::prepareGLStates(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void							MapEditorTab::prepareShaderData(void)
{
	//return;

	// setup projection matrix

	m_matProjectionMatrix.push(glm::mat4(1.0f));
	m_matProjectionMatrix.top() *= glm::perspective(45.0f, (float32)m_vecRenderSize.x / (float32)m_vecRenderSize.y, 0.1f, 1500.0f);
	
	/*
	GLdouble fovY = 45.0;
	GLdouble aspect = (float32)m_vecRenderSize.x / (float32)m_vecRenderSize.y;
	GLdouble zNear = 1.0;
	GLdouble zFar = 1500.0;
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;
	m_matProjectionMatrix.top() *= glm::frustum<float32>(-fW, fW, -fH, fH, zNear, zFar);
	*/




	// setup modelview matrix (look down the negative z-axis)

	//Vec3f vecCameraPosition = Vec3f(-700, 1200, 180);
	m_matModelViewMatrix.push(glm::mat4(1.0f));
	//m_matModelViewMatrix.top() *= glm::lookAt(glm::vec3(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y), glm::vec3(-700, 1200, 0), glm::vec3(0.0f, 1.0f, 0.0f));


	// render camera
	//Vec3f vecCameraPosition = Vec3f(-700, 1200, 180);
	//Vec3f vecCameraLookAtPosition = Vec3f(-700, 1200, 0);
	//Vec3f vecCameraPosition = Vec3f(-654.1593018, 1550.650391, 50.0);
	//Vec3f vecCameraLookAtPosition = Vec3f(-654.1593018, 1550.650391, 10.0);
	Vec3f vecCameraPosition = Vec3f(5, 5, 5);
	Vec3f vecCameraLookAtPosition = Vec3f(0, 0, 0);

	//m_matModelViewMatrix.push(glm::mat4(1.0f));
	//m_matModelViewMatrix.top() *= glm::lookAt(glm::vec3(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y), glm::vec3(vecCameraLookAtPosition.x, vecCameraLookAtPosition.z, vecCameraLookAtPosition.y), glm::vec3(0.0f, 1.0f, 0.0f));

	static float zRot = 0.0f;
	m_vecCameraPosition = Vec3f(5, 5, 5);
	//zRot += 5.0f;

	float _verticalAngle = 45;
	float _horizontalAngle = Math::convertRadiansToDegrees(Math::getAngleBetweenPoints(vecCameraLookAtPosition, vecCameraPosition)) - 90;
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, _verticalAngle, glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, _horizontalAngle, glm::vec3(0, 1, 0));
	//_horizontalAngle += 20;
	//_verticalAngle += 20;

	glm::vec3 camPosition = glm::vec3(m_vecCameraPosition.x, m_vecCameraPosition.z, m_vecCameraPosition.y);
	glm::mat4 camera = glm::perspective(45.0f, (float32)m_vecRenderSize.x / (float32)m_vecRenderSize.y, 0.1f, 1500.0f);
	camera *= orientation;
	camera = glm::translate(camera, -camPosition);
	

	//glm::mat4 matCameraPosition = glm::mat4(1.0f) * glm::lookAt(glm::vec3(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y), glm::vec3(vecCameraLookAtPosition.x, vecCameraLookAtPosition.z, vecCameraLookAtPosition.y), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "Camera"), 1, GL_FALSE, glm::value_ptr(camera));

	glUseProgram(m_program2);
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "Model"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "Camera"), 1, GL_FALSE, glm::value_ptr(camera));

	//m_matModelViewMatrix.pop();












	// create and upload modelviewprojection matrix

	int rrr = glGetError();
	if (rrr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}

	//m_matModelViewProjectionMatrix = m_matProjectionMatrix * m_matModelViewMatrix;
	glUseProgram(m_program);
	
	GLint vvv = glGetUniformLocation(m_program, "Projection");

	int rrrr = glGetError();
	if (rrrr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}
	
	glUniformMatrix4fv(glGetUniformLocation(m_program, "Projection"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0); // Texture unit 0

	glUseProgram(m_program2);
	
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "Projection"), 1, GL_FALSE, glm::value_ptr(m_matProjectionMatrix.top()));
	glUniformMatrix4fv(glGetUniformLocation(m_program2, "Model"), 1, GL_FALSE, glm::value_ptr(m_matModelViewMatrix.top()));

	int rr = glGetError();
	if (rr != GL_NO_ERROR)
	{
		int d = 5;
		d++;
	}
}

void									MapEditorTab::prepareFBO(void)
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