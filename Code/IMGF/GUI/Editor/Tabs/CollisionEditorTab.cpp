#include "CollisionEditorTab.h"
#include "nsbxgi.h"
#include "Format/COL/COLFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/Text.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/DropDown.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/Path.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLVersionManager.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "GUI/Editor/Entries/TextureEditorTabEntry.h"
#include "GraphicsLibrary/Base/ImageObject.h"
#include "Style/Parts/EStyleStatus.h"
#include "Stream/DataReader.h"
#include "../BXGI/Event/EEvent.h"
#include "Event/EInputEvent.h"
#include "GUI/Editor/Editors/CollisionEditor.h"
#include "GUI/Window/windows/MainWindow/MainWindow.h"
#include "Static/DataPath.h"
#include "Static/StdVector.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

recursive_mutex mutexInitializing3DRender_CollisionEditor; // todo
recursive_mutex mutex3DRender; // todo

CollisionEditorTab::CollisionEditorTab(void) :
	m_pGLEntity(nullptr),
	m_pCOLFile(nullptr),
	m_pActiveEntry(nullptr),

	m_pVScrollBar(nullptr),

	m_bInitializing(false),
	m_bInitialized(false),
	m_bPanningCamera(false),

	m_uiDisplayedEntryCount(0)
{
}

// events
void					CollisionEditorTab::bindEvents(void)
{
	bindEvent(AFTER_RENDER, &CollisionEditorTab::afterRender);
	bindEvent(SELECT_DROP_DOWN_ITEM, &CollisionEditorTab::onSelectDropDownItem);
	bindEvent(LEFT_MOUSE_DOWN, &CollisionEditorTab::onLeftMouseDown);
	bindEvent(KEY_DOWN, &CollisionEditorTab::onKeyDown2);
	bindEvent(MOVE_MOUSE_WHEEL, &CollisionEditorTab::onMouseWheelMove2);
	bindEvent(RESIZE_WINDOW, &CollisionEditorTab::onResizeWindow);
	
	_3DEditorTab::bindEvents();
	EditorTab::bindEvents();
}

void					CollisionEditorTab::unbindEvents(void)
{
	unbindEvent(AFTER_RENDER, &CollisionEditorTab::afterRender);
	unbindEvent(SELECT_DROP_DOWN_ITEM, &CollisionEditorTab::onSelectDropDownItem);
	unbindEvent(LEFT_MOUSE_DOWN, &CollisionEditorTab::onLeftMouseDown);
	unbindEvent(KEY_DOWN, &CollisionEditorTab::onKeyDown2);
	unbindEvent(MOVE_MOUSE_WHEEL, &CollisionEditorTab::onMouseWheelMove2);
	unbindEvent(RESIZE_WINDOW, &CollisionEditorTab::onResizeWindow);
	
	_3DEditorTab::unbindEvents();
	EditorTab::unbindEvents();
}

// controls
void					CollisionEditorTab::storeControls(void)
{
	m_pVScrollBar = (ScrollBar*)getLayer()->getItemById(95);
}

void					CollisionEditorTab::onResizeWindow(Vec2i& vecSizeChange)
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
void					CollisionEditorTab::initLayer(void)
{
	setLayer(m_pEditor->getMainWindow()->getLayerById(102));
}

// gfx lib context
void					CollisionEditorTab::makeCurrent(void)
{
	if (m_gl.m_uiShaderProgram != 0) // todo: use m_gl.isInitialized
	{
		m_gl.makeCurrent();
	}
}

// event callbacks
void					CollisionEditorTab::onSelectDropDownItem(DropDownItem *pItem)
{
}

void					CollisionEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
	if (!m_pCOLFile)
	{
		return;
	}

	COLEntry
		*pActiveCOLEntry = nullptr;
	uint32
		uiActiveImageIndex,
		uiRowHeight = 55;
	float32
		fVProgress = m_pVScrollBar ? m_pVScrollBar->getProgress() : 0.0f;
	RECT
		rectCOLEntry;

	rectCOLEntry.left = 120;
	rectCOLEntry.top = 130;
	rectCOLEntry.right = rectCOLEntry.left + 250;
	rectCOLEntry.bottom = rectCOLEntry.top + 55;

	for (uint32
			uiMaxEntryCount = Math::getMaxEntryCount(getLayer()->getWindow()->getSize().y - 160, uiRowHeight),
			uiEntryIndex = Math::getEntryStartIndex(m_pCOLFile->getEntryCount(), uiMaxEntryCount, fVProgress),
			uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(m_pCOLFile->getEntryCount(), uiEntryIndex, uiMaxEntryCount);
		uiEntryIndex < uiEntryEndIndexExclusive;
		uiEntryIndex++
	)
	{
		COLEntry *pCOLEntry = m_pCOLFile->getEntryByIndex(uiEntryIndex);
		if (!pCOLEntry)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

		if (vecCursorPosition.x >= rectCOLEntry.left
			&& vecCursorPosition.y >= rectCOLEntry.top
			&& vecCursorPosition.x <= (rectCOLEntry.right - m_pVScrollBar->getSize().x)
			&& vecCursorPosition.y <= rectCOLEntry.bottom)
		{
			uiActiveImageIndex = uiEntryIndex;
			pActiveCOLEntry = pCOLEntry;
			break;
		}

		rectCOLEntry.top += 55;
		rectCOLEntry.bottom += 55;
	}
	if (pActiveCOLEntry != nullptr)
	{
		setActiveEntry(pActiveCOLEntry);
		prepareEntities();
	}
}

Vec2f g_vecLastMousePosition = Vec2f(0.0f, 0.0f); // todo

bool					CollisionEditorTab::onMouseMove(Vec2i& vecCursorPosition)
{
	// todo

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		m_bPanningCamera = true;

		//Vec2f vecNewPosition = Vec2f((float32)xpos, ypos);
		Vec2i vecNewPosition = BXGX::get()->getCursorPosition();
		if (g_vecLastMousePosition.x != 0.0f && g_vecLastMousePosition.y != 0.0f)
		{
			const Vec2f vecCursorMoveMultiplier = { 0.3f, 0.3f };

			Vec2f vecPositionDifference = Vec2f(vecNewPosition.x - g_vecLastMousePosition.x, vecNewPosition.y - g_vecLastMousePosition.y);
			// todo m_gl.rotateCameraLookAt(vecPositionDifference.x * vecCursorMoveMultiplier.x, vecPositionDifference.y * vecCursorMoveMultiplier.y);

			/*
			Vec3f vecCameraRotation = getCameraRotation();
			//Vec2f vecPositionDifference = Vec2f(0.0f, 0.0f);
			vecCameraRotation.z += Math::convertDegreesToRadians(vecPositionDifference.x * vecCursorMoveMultiplier.x);
			vecCameraRotation.x += Math::convertDegreesToRadians(vecPositionDifference.y * vecCursorMoveMultiplier.y);

			Vec3f vecPos2 = Math::getPositionInFrontOfPosition(m_vecCameraPosition, vecCameraRotation.z, Math::getDistanceBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition));
			m_vecCameraLookAtPosition.x = vecPos2.x;
			m_vecCameraLookAtPosition.y = vecPos2.y;
			*/

			//render3D();
		}

		g_vecLastMousePosition = Vec2f(vecNewPosition.x, vecNewPosition.y);

		return true;
	}
	else
	{
		m_bPanningCamera = false;
	}
}

void					CollisionEditorTab::onKeyDown2(uint16 uiKey)
{
	if (isPointOverEntryList(BXGX::get()->getCursorPosition()))
	{
		// texture list
		int32 iNextTextureIndex;
		int32 wScrollNotify;
		uint32 uiMinTextureIndex = 0;
		uint32 uiMaxTextureIndex = m_pCOLFile->getEntryCount() - 1;
		uint32 yCurrentScroll = 0;
		COLEntry *pCOLEntry;

		switch (uiKey)
		{
		case VK_PRIOR:
			iNextTextureIndex = m_pCOLFile->getIndexByEntry(getActiveEntry()) - 5;
			if (iNextTextureIndex < 0)
			{
				iNextTextureIndex = 0;
			}
			pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
			setActiveEntry(pCOLEntry);
			getLayer()->getWindow()->render();
			break;

		case VK_NEXT:
			iNextTextureIndex = m_pCOLFile->getIndexByEntry(getActiveEntry()) + 5;
			if (iNextTextureIndex > (int32)uiMaxTextureIndex)
			{
				iNextTextureIndex = uiMaxTextureIndex;
			}
			pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
			setActiveEntry(pCOLEntry);
			getLayer()->getWindow()->render();
			break;

		case VK_UP:
			iNextTextureIndex = ((int32)m_pCOLFile->getIndexByEntry(getActiveEntry())) - 1;
			if (iNextTextureIndex >= 0)
			{
				pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
				setActiveEntry(pCOLEntry);
				getLayer()->getWindow()->render();
			}
			break;

		case VK_DOWN:
			iNextTextureIndex = m_pCOLFile->getIndexByEntry(getActiveEntry()) + 1;
			if (iNextTextureIndex <= (int32)uiMaxTextureIndex)
			{
				pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
				setActiveEntry(pCOLEntry);
				getLayer()->getWindow()->render();
			}
			break;

		case VK_HOME:
			if (m_pCOLFile->getEntryCount() > 0)
			{
				setActiveEntry(m_pCOLFile->getFirstEntry());
				getLayer()->getWindow()->render();
			}
			wScrollNotify = SB_TOP;
			break;

		case VK_END:
			if (m_pCOLFile->getEntryCount() > 0)
			{
				setActiveEntry(m_pCOLFile->getLastEntry());
				getLayer()->getWindow()->render();
			}
			wScrollNotify = SB_BOTTOM;
			break;
		}
	}
	else
	{
		// 3d item
	}
}

void					CollisionEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	if (isPointOverEntryList(BXGX::get()->getCursorPosition()))
	{
		int iDelta = -(iRotationDistance / WHEEL_DELTA);
		float32 fNewProgress = m_pVScrollBar->getProgress() + ((float32)iDelta * m_pVScrollBar->getProgressFor1Item());
		fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
		m_pVScrollBar->setProgress(fNewProgress);
	}

	getLayer()->getWindow()->render();
}

// file unserialization
bool					CollisionEditorTab::unserializeFile(void)
{
	COLFormat *col = new COLFormat;

	if (!col->openFile())
	{
		return false;
	}
	if (!col->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(col->getErrorCode()) + "\r\n\r\n" + col->getFilePath(), "Can't Open COL File");
		delete col;
		return false;
	}

	uint32 uiProgressBarMax = col->m_reader.getSize();
	getProgressBar()->setMax(uiProgressBarMax);

	if (!col->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(col->getErrorCode()) + "\r\n\r\n" + col->getFilePath(), "Can't Open COL File");
		delete col;
		return false;
	}

	setCOLFile(col);
	return true;
}

void					CollisionEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	//getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), strFilePath);

	// prepare render data
	prepareRenderData();

	// display TXD info
	calculateDisplayedEntryCount();
	setFileInfoText();

	// render
	getLayer()->getWindow()->render();
}

// prepare render data
bool						CollisionEditorTab::prepareRenderData(void)
{
	vector<COLEntry*> vecCollisions = m_pCOLFile->getEntries();

	m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, getLayer()->getWindow()->getSize().y - 160);
	m_pVScrollBar->setItemCount(VERTICAL, vecCollisions.size() * 50);

	/*
	todo

	uint32 uiTextureIndex = 0;
	for (COLEntry *pCOLEntry: vecCollisions)
	{
		TextureEditorTabEntry *pTabEntry = new TextureEditorTabEntry;

		if (pRWSection_TextureNative->getEntryCount() == 0)
		{
			// the texture does not have a mipmap
			pTabEntry->m_uiIndex = uiTextureIndex;
			pTabEntry->m_bTextureContainsNoMipmaps = true;
		}
		else
		{
			RWEntry_TextureNative_MipMap *pMipmap = pRWSection_TextureNative->getMipMaps().getEntryByIndex(0);
			string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
			const char *pBmpImageData = strBMPImageDataStr.c_str();

			HBITMAP hBitmap = CreateBitmap(pMipmap->getImageSize().x, pMipmap->getImageSize().y, 1, 32, pBmpImageData);

			pTabEntry->m_uiIndex = uiTextureIndex;
			pTabEntry->m_hBitmap = hBitmap;
			pTabEntry->m_uiWidth = pRWSection_TextureNative->getImageSize().x;
			pTabEntry->m_uiHeight = pRWSection_TextureNative->getImageSize().y;
			pTabEntry->m_strDiffuseName = pRWSection_TextureNative->getDiffuseName();
			pTabEntry->m_strAlphaName = pRWSection_TextureNative->getAlphaName();
			pTabEntry->m_ucBPP = pRWSection_TextureNative->getOriginalBPP() == 0 ? pRWSection_TextureNative->getBPP() : pRWSection_TextureNative->getOriginalBPP();
			pTabEntry->m_strTextureFormat = TXDManager::getTXDRasterFormatText(pRWSection_TextureNative->getTXDRasterDataFormat(), pRWSection_TextureNative->getDXTCompressionType());
		}

		uiTextureIndex++;
	}
	*/

	if (m_pCOLFile->getEntryCount() > 0)
	{
		setActiveEntry(m_pCOLFile->getFirstEntry());
	}

	return true;
}

// file info text
void						CollisionEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	if (getCOLFile()->getEntryCount() > 0)
	{
		m_pText_FileVersion->setText(COLManager::get()->getVersionManager()->getVersionText(getCOLFile()->getFirstEntry()->getCOLVersion()), false);
		m_pText_FileGame->setText(COLManager::get()->getVersionManager()->getGamesAsString(getCOLFile()->getFirstEntry()->getCOLVersion()));
	}
	else
	{
		m_pText_FileVersion->setText(string("COL 1"), false);
		m_pText_FileGame->setText(string("GTA III"));
	}
	updateEntryCountText();
}

void						CollisionEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = m_uiDisplayedEntryCount,
		uiTotalEntryCount = getCOLFile()->getEntryCount();
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

void						CollisionEditorTab::calculateDisplayedEntryCount(void)
{
	uint32 uiMatchCount = 0;
	for (COLEntry *pCOLEntry : getCOLFile()->getEntries())
	{
		if (doesTabEntryMatchFilter(pCOLEntry))
		{
			uiMatchCount++;
		}
	}
	m_uiDisplayedEntryCount = uiMatchCount;
}

// entry list
bool						CollisionEditorTab::isPointOverEntryList(Vec2i& vecPoint)
{
	int32 x, y;
	uint32 w, h;

	x = 120;
	y = 130;

	w = 250;
	h = getLayer()->getWindow()->getSize().y - y;

	return Math::isPointInRectangle(vecPoint, Vec2i(x, y), Vec2u(w, h));
}

// filter
bool						CollisionEditorTab::doesTabEntryMatchFilter(COLEntry *pCOLEntry)
{
	string strSearchTextUpper = String::toUpperCase(m_pSearchBox->getText());
	return strSearchTextUpper == "" || String::isIn(String::toUpperCase(pCOLEntry->getModelName()), strSearchTextUpper, false);
}

// render
void						CollisionEditorTab::render(void)
{
	//render2D();
}

void						CollisionEditorTab::afterRender(void)
{
	render2D();
	render3D();
}

void						CollisionEditorTab::renderNotOnProcess(void)
{
}

// render editor 2d
void						CollisionEditorTab::render2D(void)
{
	HWND hwnd = getLayer()->getWindow()->getWindowHandle();

	HDC memDC, hdc = GetWindowDC(hwnd);
	HGDIOBJ old = nullptr;
	PAINTSTRUCT ps;
	RECT clientRect;
	int width, height;

	uint32 x, y;
	Vec2i vecMainPanelPosition;

	x = 120;
	y = 130;
	vecMainPanelPosition = Vec2i(x, y);

	float32 yCurrentScroll = 0;

	GetClientRect(hwnd, &clientRect);
	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;

	memDC = CreateCompatibleDC(NULL);

	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();
	
	// display type: Single
	const uint32
		uiImagePaddingRight = 10,
		uiImagePaddingBottom = 10,
		uiEntryViewerWindowClientAreaWidth = 494;
	uint32
		uiEntryRectX = x,// uiSingleDisplayTypeTopScrollbarXCurrentScroll,
		uiEntryRectY = y,
		uiHighestImageInRow = 0,
		uiCalculatedWidth,
		uiTextureIndex = 0,
		uiRowHeight = 55;
	COLEntry
		*pActiveCOLEntry = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = false;
	float32
		fVProgress = m_pVScrollBar->getProgress();
	RECT
		rectCOLEntry;

	rectCOLEntry.left = 120;
	rectCOLEntry.top = 130;
	rectCOLEntry.right = rectCOLEntry.left + 250;
	rectCOLEntry.bottom = rectCOLEntry.top + 55;

	for(uint32
			uiMaxEntryCount = Math::getMaxEntryCount(getLayer()->getWindow()->getSize().y - 160, uiRowHeight),
			uiEntryIndex = Math::getEntryStartIndex(m_pCOLFile->getEntryCount(), uiMaxEntryCount, fVProgress),
			uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(m_pCOLFile->getEntryCount(), uiEntryIndex, uiMaxEntryCount);
		uiEntryIndex < uiEntryEndIndexExclusive;
		uiEntryIndex++
	)
	{
		COLEntry *pCOLEntry = m_pCOLFile->getEntryByIndex(uiEntryIndex);
		if (!pCOLEntry)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

		if (!doesTabEntryMatchFilter(pCOLEntry))
		{
			continue;
		}

		uiCalculatedWidth = 0;

		// calculate max width out of: image, diffuse text and alpha text
		SIZE textSize;
		GetTextExtentPoint32(hdc, String::convertStdStringToStdWString(pCOLEntry->getModelName()).c_str(), pCOLEntry->getModelName().length(), &textSize);
		uiCalculatedWidth = textSize.cx;

		// draw active texture background colour
		getLayer()->getWindow()->setRenderingStyleGroups("leftEntryPanel");
		
		if (pCOLEntry == getActiveEntry())
		{
			getLayer()->getWindow()->setRenderingStyleStatus(EStyleStatus::ACTIVE);
		}
		else
		{
			getLayer()->getWindow()->setRenderingStyleStatus(EStyleStatus::DEFAULT_STYLE_STATUS);
		}

		pGFX->drawRectangle(Vec2i(rectCOLEntry.left, rectCOLEntry.top), Vec2u(rectCOLEntry.right - rectCOLEntry.left, rectCOLEntry.bottom - rectCOLEntry.top));
		getLayer()->getWindow()->resetRenderingStyleGroups();
		getLayer()->getWindow()->resetRenderingStyleStatus();
		
		// draw collision number
		HFONT hFont = CreateFont(22, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
		HGDIOBJ old2 = SelectObject(hdc, hFont);

		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);

		RECT rect;

		rect.left = uiEntryRectX + 5;
		rect.top = uiEntryRectY + 13 - yCurrentScroll;
		string strText = String::toString(uiEntryIndex + 1);
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture name
		uint32 uiXOffset1 = 50;

		rect.left = uiEntryRectX + uiXOffset1;
		rect.top = uiEntryRectY + 5 - yCurrentScroll;
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), pCOLEntry->getModelName());
		uiEntryRectY += 15;
		uiEntryRectY += 15;

		uiEntryRectY += 15;
		uiEntryRectY += 10;

		// horizontal line below texture image
		pGFX->drawLine(Vec2i(vecMainPanelPosition.x, uiEntryRectY - 1 - yCurrentScroll), Vec2i(vecMainPanelPosition.x + 250, uiEntryRectY - 1 - yCurrentScroll));

		uiTextureIndex++;
		rectCOLEntry.top += 55;
		rectCOLEntry.bottom += 55;

		SelectObject(hdc, old2);
		DeleteObject(hFont);
	}

	SelectObject(memDC, old);
	DeleteDC(memDC);
	
	ReleaseDC(hwnd, hdc);
}

// prepare initial render
void						CollisionEditorTab::prepareInitial3DRender(void)
{

}

// render editor 3d
void						CollisionEditorTab::render3D(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (!m_pActiveEntry)
	{
		return;
	}

	if (m_bInitializing)
	{
		return;
	}

	mutex3DRender.lock();

	// initialize opengl
	if (!m_bInitialized)
	{
		mutexInitializing3DRender_CollisionEditor.lock();
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

		mutexInitializing3DRender_CollisionEditor.unlock();

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

	mutex3DRender.unlock();
}

// entity colours
glm::vec3						CollisionEditorTab::getItemColour(uint32 uiItemIndex)
{
	vector<glm::vec3> vecItemColours = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },

		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f }
	};
	return vecItemColours[uiItemIndex % 6];
}

// entity preparation
void						CollisionEditorTab::prepareScene(void)
{
	glUseProgram(m_gl.m_uiShaderProgram);

	prepareEntities();
}

void						CollisionEditorTab::prepareEntities(void)
{
	mutex3DRender.lock();
	prepareCollisionEntry();
	mutex3DRender.unlock();
}

void						CollisionEditorTab::prepareCollisionEntry(void)
{
	m_gl.reset();
	if (m_pGLEntity)
	{
		m_gl.removeEntity(m_pGLEntity);
	}

	m_pGLEntity = m_gl.addEntity();

	prepareCamera(m_pActiveEntry);

	prepareBoundingSphere(m_pActiveEntry);
	prepareBoundingCuboid(m_pActiveEntry);

	prepareLines(m_pActiveEntry);
	prepareCones(m_pActiveEntry);
	prepareSpheres(m_pActiveEntry);
	prepareCuboids(m_pActiveEntry);
	prepareMeshes(m_pActiveEntry);
}

void						CollisionEditorTab::prepareCamera(COLEntry *pCOLEntry)
{
	Vec3f vecCenterPos2 = pCOLEntry->getBoundingObjects().m_vecCenter;
	m_vecCenterPosition = glm::vec3(vecCenterPos2.x, vecCenterPos2.y, vecCenterPos2.z);

	m_fCameraToCenterRadius = pCOLEntry->getBoundingObjects().m_fRadius * 2.0f * 1.5f;
	if (m_fCameraToCenterRadius < 5.0f) m_fCameraToCenterRadius = 5.0f;

	updateCamera();
}

void						CollisionEditorTab::prepareBoundingSphere(COLEntry *pCOLEntry)
{
	glm::vec3 pos = glm::vec3(pCOLEntry->getBoundingObjects().m_vecCenter.x, pCOLEntry->getBoundingObjects().m_vecCenter.z, pCOLEntry->getBoundingObjects().m_vecCenter.y);
	glm::vec3 vecColour = glm::vec3(1.0f, 0.5f, 0.0f);

	vector<GLMesh*> vecSpheres = m_pGLEntity->addBoundingSphere(pos, pCOLEntry->getBoundingObjects().m_fRadius, vecColour);
}

void						CollisionEditorTab::prepareBoundingCuboid(COLEntry *pCOLEntry)
{
	Vec3f& min = pCOLEntry->getBoundingObjects().m_vecMin;
	Vec3f& max = pCOLEntry->getBoundingObjects().m_vecMax;
	glm::vec3 vecColour = glm::vec3(0.0f, 0.5f, 1.0f);

	GLMesh *pCuboid = m_pGLEntity->addBoundingCuboid(glm::vec3(min.x, min.z, min.y), glm::vec3(max.x, max.z, max.y), vecColour);
}

void						CollisionEditorTab::prepareLines(COLEntry *pCOLEntry)
{
	if (!pCOLEntry->areLinesSupported())
	{
		return;
	}

	for (TLine& line : pCOLEntry->getCollisionLines())
	{
		vector<glm::vec3> vecLineVertices = {
			glm::vec3(line.m_vecPosition1.x, line.m_vecPosition1.z, line.m_vecPosition1.y),
			glm::vec3(line.m_vecPosition2.x, line.m_vecPosition2.z, line.m_vecPosition2.y),
		};
		GLMesh *pMesh = m_pGLEntity->addMesh(m_gl.swapVec3YZ(vecLineVertices), vector<glm::vec2>(), vector<glm::vec3>(), vector<glm::vec3>(), GL_LINES);
	}
}

void						CollisionEditorTab::prepareCones(COLEntry *pCOLEntry)
{
	if (!pCOLEntry->areConesSupported())
	{
		return;
	}

	for (TCone& cone : pCOLEntry->getCollisionCones())
	{
		// todo
		//vector<glm::vec3> vecConeVertices = Math::getConeVertices(sphere.m_vecCenter, sphere.m_fRadius, 100);
		//GLMesh *pMesh = m_pGLEntity->addMesh(m_gl.swapVec3YZ(vecConeVertices), vector<glm::vec2>(), vector<glm::vec3>(), vector<glm::vec3>(), GL_TRIANGLES);
	}
}

void						CollisionEditorTab::prepareSpheres(COLEntry *pCOLEntry)
{
	uint32 uiSphereIndex = 0;
	for (TSphere& sphere : pCOLEntry->getCollisionSpheres())
	{
		glm::vec3 pos = glm::vec3(sphere.m_vecCenter.x, sphere.m_vecCenter.z, sphere.m_vecCenter.y);
		glm::vec3 colour = getItemColour(uiSphereIndex);

		GLMesh *pSphere = m_pGLEntity->addSphere(pos, sphere.m_fRadius, 100, colour);
		uiSphereIndex++;
	}
}

void						CollisionEditorTab::prepareCuboids(COLEntry *pCOLEntry)
{
	uint32 uiCuboidIndex = 0;
	for (TBox& box : pCOLEntry->getCollisionBoxes())
	{
		glm::vec3 colour = getItemColour(uiCuboidIndex);

		GLMesh *pCuboid = m_pGLEntity->addCuboid(glm::vec3(box.m_min.x, box.m_min.z, box.m_min.y), glm::vec3(box.m_max.x, box.m_max.z, box.m_max.y), colour);
		uiCuboidIndex++;
	}
}

void						CollisionEditorTab::prepareMeshes(COLEntry *pCOLEntry)
{
	vector<glm::vec3> vecVertices = *(std::vector<glm::vec3>*)&pCOLEntry->getCollisionMeshVertices();
	GLMesh *pMesh = m_pGLEntity->addMesh(m_gl.swapVec3YZ(vecVertices), vector<glm::vec2>(), vector<glm::vec3>(), vector<glm::vec3>(), pCOLEntry->doesUseFaceGroups() ? 0 : GL_TRIANGLE_STRIP);

	if (pCOLEntry->doesUseFaceGroups())
	{
		for (TFaceGroup& faceGroup : pCOLEntry->getCollisionMeshFaceGroups())
		{
			vector<uint16> vecIndices;
			for (uint32 i = faceGroup.m_startFace, j = faceGroup.m_endFace; i <= j; i++)
			{
				vecIndices.push_back(i);
			}
			pMesh->addFaceGroup(GL_TRIANGLE_STRIP, vecIndices, nullptr);
		}
	}
}

void						CollisionEditorTab::recreateEntryList(void)
{
	calculateDisplayedEntryCount();
	updateEntryCountText();
	getLayer()->getWindow()->render();
}