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

std::stack<glm::mat4> g_stkModels_MapEditor; // todo

MapEditorTab::MapEditorTab(void) :
	m_pGLEntity(nullptr),
	m_pDATLoaderFile(nullptr),
	m_bInitialized(false),
	m_bInitializing(false),
	m_bFilesAreInitialized(false)
{
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

	Vec2u vecRenderSize = Vec2u(getLayer()->getWindow()->getSize().x - 120 - 250 - 5, getLayer()->getWindow()->getSize().y - 130 - 30);

	mutexRendering.lock();
	m_gl.setRenderSize(vecRenderSize);
	m_gl.recreateBitmap();
	m_gl.resizeScene();
	mutexRendering.unlock();
}

// events
void						MapEditorTab::bindEvents(void)
{
	bindEvent(RENDER, &MapEditorTab::render);
	bindEvent(END_RENDER, &MapEditorTab::endRender);
	bindEvent(MOVE_MOUSE_WHEEL, &MapEditorTab::onMouseWheelMove2);
	bindEvent(RESIZE_WINDOW, &MapEditorTab::onResizeWindow);

	EditorTab::bindEvents();
}

void						MapEditorTab::unbindEvents(void)
{
	unbindEvent(RENDER, &MapEditorTab::render);
	unbindEvent(END_RENDER, &MapEditorTab::endRender);
	unbindEvent(MOVE_MOUSE_WHEEL, &MapEditorTab::onMouseWheelMove2);
	unbindEvent(RESIZE_WINDOW, &MapEditorTab::onResizeWindow);
	
	EditorTab::unbindEvents();
}

// gfx lib context
void						MapEditorTab::makeCurrent(void)
{
	if (m_gl.m_uiShaderProgram != 0) // todo: use m_gl.isInitialized
	{
		m_gl.makeCurrent();
	}
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
		m_gl.zoomCamera((float32)-iDelta * fMouseWheelScrollMultiplier);
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
void						MapEditorTab::render2D(void)
{
}

// render 3d
mutex mutexInitializing3DRender_MapEditor; // todo

void						MapEditorTab::render(void)
{
	render2D();
}

void						MapEditorTab::endRender(void)
{
	render3D();
}

void						MapEditorTab::render3D(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (!m_bFilesAreInitialized)
	{
		return;
	}

	if (m_bInitializing)
	{
		return;
	}

	if (!m_bInitialized)
	{
		mutexInitializing3DRender_MapEditor.lock();
		m_bInitializing = true;

		Vec2u vecRenderSize = Vec2u(getLayer()->getWindow()->getSize().x - 120 - 250 - 5, getLayer()->getWindow()->getSize().y - 130 - 30);

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
		mutexInitializing3DRender_MapEditor.unlock();

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

	BitBlt(pGFX->getMemoryDC(), 120 + 250, 130, m_gl.getRenderSize().x, m_gl.getRenderSize().y, hdc2, 0, 0, SRCCOPY);

	SelectObject(hdc2, hOld2);
	DeleteObject(hbm2);
	DeleteDC(hdc2);
	ReleaseDC(m_gl.m_hWindow, hdcWindow);
	m_gl.resetFBOBitmap();

	// finalize render
	m_gl.finalizeRender();
}

// render 3d components
void						MapEditorTab::prepareScene(void)
{
	prepareMap();
}

void						MapEditorTab::drawScene(void)
{
}

void						MapEditorTab::prepareMap(void)
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

void						MapEditorTab::prepareModel(DFFFormat *pDFFFile)
{
	m_pGLEntity = m_gl.addEntity();

	g_stkModels_MapEditor.push(glm::mat4(1.0f));

	m_pDFFFile = pDFFFile;
	prepareGeometries();
	prepareRenderData();
}

void						MapEditorTab::prepareGeometries(void)
{
	uint32 uiGeometryIndex = 0;
	for (RWSection *pGeometry : m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY))
	{
		prepareGeometry(uiGeometryIndex, (RWSection_Geometry*)pGeometry);
		uiGeometryIndex++;
	}
}

void						MapEditorTab::prepareGeometry(uint32 uiGeometryIndex, RWSection_Geometry *pGeometry)
{
	GLMesh *pGLMesh = m_pGLEntity->addMesh(
		m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexPositions())),
		*(vector<glm::vec2>*)(&pGeometry->getTextureCoordinates()),
		StdVector::convertStdVectorBXCFVec4u8ToGLMVec3(pGeometry->getVertexColours()),
		m_gl.swapVec3YZ(*(vector<glm::vec3>*)(&pGeometry->getVertexNormals()))
	);

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

void						MapEditorTab::prepareRenderData(void)
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

void						MapEditorTab::prepareFrame(uint32 uiFrameIndex, RWSection_Frame *pFrame, bool bIsParentFrame)
{
	g_stkModels_MapEditor.push(g_stkModels_MapEditor.top());

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

		g_stkModels_MapEditor.top() *= matMultMatrix;

		//g_stkModels_MapEditor.top() = glm::translate(g_stkModels_MapEditor.top(), glm::vec3(pFrameList->m_vecPosition[uiFrameIndex].x, pFrameList->m_vecPosition[uiFrameIndex].z, pFrameList->m_vecPosition[uiFrameIndex].y));
		//g_stkModels_MapEditor.top() = glm::rotate(g_stkModels_MapEditor.top(), glm::vec3(pFrameList->m_vecPosition[uiFrameIndex].x, pFrameList->m_vecPosition[uiFrameIndex].z, pFrameList->m_vecPosition[uiFrameIndex].y));
	}

	//g_stkModels_MapEditor.top() *= matMultMatrix;

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
			renderData.m_matMultMatrix = g_stkModels_MapEditor.top();

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

	g_stkModels_MapEditor.pop();
}

void						MapEditorTab::prepareTXD(TXDFormat *pTXDFile)
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