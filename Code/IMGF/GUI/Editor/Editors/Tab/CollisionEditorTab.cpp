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
#include "GUI/Editor/Editors/Entry/TextureEditorTabEntry.h"
#include "GraphicsLibrary/Base/ImageObject.h"
#include "Style/Parts/EStyleStatus.h"
#include "Stream/DataReader.h"
#include "../BXGI/Event/EEvent.h"
#include "Event/EInputEvent.h"
#include "GUI/Editor/Editors/CollisionEditor.h"

#include <include/GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 1
#define GLFW_EXPOSE_NATIVE_WGL 1
#include <include/GLFW/glfw3native.h>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

Vec3f					vecCameraPosition = Vec3f(0.0f, 0.0f, 0.0f); // todo - namespace
Vec3f					vecCameraLookAtPosition = Vec3f(0.0f, 0.0f, 0.0f);
//Vec3f					vecCameraRotation = Vec3f(0.0f, 0.0f, 0.0f); // todo - namespace

CollisionEditorTab::CollisionEditorTab(void) :
	m_pCOLFile(nullptr),
	m_pActiveEntry(nullptr),

	m_pZoomDropDown(nullptr),
	m_pVScrollBar(nullptr),

	m_fZoomLevel(1.0f)
{
}

// events
void					CollisionEditorTab::bindEvents(void)
{
	bindEvent(SELECT_DROP_DOWN_ITEM, &CollisionEditorTab::onSelectDropDownItem);
	bindEvent(LEFT_MOUSE_DOWN, &CollisionEditorTab::onLeftMouseDown);
	bindEvent(KEY_DOWN, &CollisionEditorTab::onKeyDown2);
	bindEvent(MOVE_MOUSE_WHEEL, &CollisionEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void					CollisionEditorTab::unbindEvents(void)
{
	unbindEvent(SELECT_DROP_DOWN_ITEM, &CollisionEditorTab::onSelectDropDownItem);
	unbindEvent(LEFT_MOUSE_DOWN, &CollisionEditorTab::onLeftMouseDown);
	unbindEvent(KEY_DOWN, &CollisionEditorTab::onKeyDown2);
	unbindEvent(MOVE_MOUSE_WHEEL, &CollisionEditorTab::onMouseWheelMove2);

	EditorTab::unbindEvents();
}

// controls
void					CollisionEditorTab::addControls(void)
{
	int32 x, y;
	uint32 w, h, uiLogWidth;

	uiLogWidth = 335;

	x = 139 + 139 + 250 + 100 + 51;
	y = ((162 + 30) - 50) - 1;
	w = 80;
	h = 20;

	// zoom dropdown
	m_pZoomDropDown = addDropDown(Vec2i(x, y), Vec2u(w, h), "");
	vector<string> vecZoomDropDownItems = { "25%", "50%", "100%", "200%", "400%", "800%", "1600%" };
	m_pZoomDropDown->addItems(vecZoomDropDownItems);
	m_pZoomDropDown->setActiveItem(m_pZoomDropDown->getEntryByIndex(2));

	// vertical scroll bar
	x = 139 + 139 + 250;
	y = 192;
	w = 15;
	h = m_pWindow->getSize().y - y;
	x -= w;

	m_pVScrollBar = addScrollBar(x, y, w, h, "", -1, 50);
	m_pVScrollBar->setScrollOrientation(VERTICAL);
}

void					CollisionEditorTab::initControls(void)
{
}

// editor input
void					CollisionEditorTab::onSelectDropDownItem(DropDownItem *pItem)
{
	string strActiveZoomText = m_pZoomDropDown->getActiveItem()->getText();
	float32 fZoomLevel = ((float32)String::toUint32(strActiveZoomText.substr(0, strActiveZoomText.length() - 1))) / 100.0f;
	setZoomLevel(fZoomLevel);
}

void					CollisionEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
	COLEntry
		*pActiveCOLEntry = nullptr;
	uint32
		uiActiveImageIndex,
		uiRowHeight = 50;
	float32
		fVProgress = m_pVScrollBar->getProgress();
	RECT
		rectCOLEntry;

	rectCOLEntry.left = 139 + 139;
	rectCOLEntry.top = 192;
	rectCOLEntry.right = rectCOLEntry.left + 250;
	rectCOLEntry.bottom = rectCOLEntry.top + 55;

	for (uint32
			uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
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
		m_pWindow->render();
	}
}

void					CollisionEditorTab::onKeyDown2(uint16 uiKey)
{
	bool bTextureListIsActive = false;
	if (bTextureListIsActive)
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
			m_pWindow->render();
			break;

		case VK_NEXT:
			iNextTextureIndex = m_pCOLFile->getIndexByEntry(getActiveEntry()) + 5;
			if (iNextTextureIndex > (int32)uiMaxTextureIndex)
			{
				iNextTextureIndex = uiMaxTextureIndex;
			}
			pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
			setActiveEntry(pCOLEntry);
			m_pWindow->render();
			break;

		case VK_UP:
			iNextTextureIndex = ((int32)m_pCOLFile->getIndexByEntry(getActiveEntry())) - 1;
			if (iNextTextureIndex >= 0)
			{
				pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
				setActiveEntry(pCOLEntry);
				m_pWindow->render();
			}
			break;

		case VK_DOWN:
			iNextTextureIndex = m_pCOLFile->getIndexByEntry(getActiveEntry()) + 1;
			if (iNextTextureIndex <= (int32)uiMaxTextureIndex)
			{
				pCOLEntry = m_pCOLFile->getEntryByIndex(iNextTextureIndex);
				setActiveEntry(pCOLEntry);
				m_pWindow->render();
			}
			break;

		case VK_HOME:
			if (m_pCOLFile->getEntryCount() > 0)
			{
				setActiveEntry(m_pCOLFile->getFirstEntry());
				m_pWindow->render();
			}
			wScrollNotify = SB_TOP;
			break;

		case VK_END:
			if (m_pCOLFile->getEntryCount() > 0)
			{
				setActiveEntry(m_pCOLFile->getLastEntry());
				m_pWindow->render();
			}
			wScrollNotify = SB_BOTTOM;
			break;
		}
	}
	else
	{
		// 3d item
		bool bControlKey = (GetKeyState(VK_CONTROL) & 0x8000) == 0x8000;
		switch (uiKey)
		{
		case VK_DOWN:
			if (bControlKey)
			{
				vecCameraPosition.z -= 0.02f;
			}
			else
			{
				moveCamera(180.0f, 0.02f);
			}
			break;
		case VK_UP:
			if (bControlKey)
			{
				vecCameraPosition.z += 0.02f;
			}
			else
			{
				moveCamera(0.0f, 0.02f);
			}
			break;
		case VK_LEFT:
			moveCamera(-90.0f, -0.02f);
			break;
		case VK_RIGHT:
			moveCamera(-90.0f, 0.02f);
			break;
		}
	}
}

void					CollisionEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	int iDelta = -(iRotationDistance / WHEEL_DELTA);
	float32 fNewProgress = m_pVScrollBar->getProgress() + (iDelta * m_pVScrollBar->getProgressFor1Item());
	fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
	m_pVScrollBar->setProgress(fNewProgress);

	m_pWindow->render();
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
	string strFilePath = getFile()->getFilePath();

	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);

	// prepare render data
	prepareRenderData();

	// display TXD info
	setFileInfoText();

	// render
	m_pWindow->render();
}

// prepare render data
bool						CollisionEditorTab::prepareRenderData(void)
{
	vector<COLEntry*> vecCollisions = m_pCOLFile->getEntries();

	m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
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
	m_pText_FilePath->setText(getFile()->getFilePath());
	m_pText_FileVersion->setText(COLManager::get()->getVersionManager()->getVersionText(getCOLFile()->getFirstEntry()->getCOLVersion()), false);
	m_pText_FileGame->setText(COLManager::get()->getVersionManager()->getGamesAsString(getCOLFile()->getFirstEntry()->getCOLVersion()));

	updateEntryCountText();
}

void						CollisionEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getCOLFile()->getEntryCount(),
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

// render editor
void						CollisionEditorTab::render(void)
{
	render3D();
}

// render editor 2d
void						CollisionEditorTab::render2D(void)
{
	HWND hwnd = getWindow()->getWindowHandle();

	HDC memDC, hdc = GetWindowDC(hwnd);
	HGDIOBJ old = nullptr;
	PAINTSTRUCT ps;
	RECT clientRect;
	int width, height;

	uint32 x, y;
	Vec2i vecMainPanelPosition;

	x = 139 + 139;
	y = 162 + 30;
	vecMainPanelPosition = Vec2i(x, y);

	float32 yCurrentScroll = 0;

	/*
	todo
	BOOL bPremultipledAlphaApplied = FALSE; /////

	if (!bPremultipledAlphaApplied)
	{
		for (auto pImageData : getIMGF()->getEntryViewerManager()->getTextureViewer()->getEntries())
		{
			PremultiplyBitmapAlpha(hdc, pImageData->m_hBitmap);
		}
		bPremultipledAlphaApplied = true;
	}
	*/

	/*
	todo
	if (fSize)
	{
		BitBlt(ps.hdc,
			0, 0,
			800, getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowScrollbarMaxRange(),
			hdcScreenCompat,
			0, yCurrentScroll,
			SRCCOPY);

		fSize = FALSE;
	}
	*/

	//getIMGF()->getEntryViewerManager()->getTextureViewer()->clearWindowBackground(hdc);

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
		uiRowHeight = 50;
	COLEntry
		*pActiveCOLEntry = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = false;
	float32
		fVProgress = m_pVScrollBar->getProgress();
	RECT
		rectCOLEntry;

	rectCOLEntry.left = 139 + 139;
	rectCOLEntry.top = 192;
	rectCOLEntry.right = rectCOLEntry.left + 250;
	rectCOLEntry.bottom = rectCOLEntry.top + 55;

	for(uint32
			uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
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

		uiCalculatedWidth = 0;

		// calculate max width out of: image, diffuse text and alpha text
		SIZE textSize;
		GetTextExtentPoint32(hdc, String::convertStdStringToStdWString(pCOLEntry->getModelName()).c_str(), pCOLEntry->getModelName().length(), &textSize);
		uiCalculatedWidth = textSize.cx;

		//if (pImageData->m_uiWidth > uiCalculatedWidth)
		//{
		//	uiCalculatedWidth = pImageData->m_uiWidth;
		//}

		// draw active texture background colour
		m_pWindow->setRenderingStyleGroups("leftEntryPanel");
		if (pCOLEntry == getActiveEntry())
		{
			m_pWindow->setRenderingStyleStatus(EStyleStatus::ACTIVE);
		}
		pGFX->drawRectangle(Vec2i(rectCOLEntry.left, rectCOLEntry.top), Vec2u(rectCOLEntry.right - rectCOLEntry.left, rectCOLEntry.bottom - rectCOLEntry.top));
		m_pWindow->resetRenderingStyleGroups();
		m_pWindow->resetRenderingStyleStatus();

		// draw collision number
		HFONT hFont = CreateFont(22, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
		old = SelectObject(hdc, hFont);

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

		/*
		todo

		// draw texture size
		rect.left = uiEntryRectX + uiXOffset1;
		rect.top = uiEntryRectY + 5 - yCurrentScroll;
		strText = String::toString(pImageData->m_uiWidth) + " x " + String::toString(pImageData->m_uiHeight);
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture BPP
		rect.left = uiEntryRectX + uiXOffset1 + 85;
		rect.top = uiEntryRectY + 5 - yCurrentScroll;
		strText = String::toString(pImageData->m_ucBPP) + " BPP";
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture raster format
		rect.left = uiEntryRectX + uiXOffset1 + 85 + 55;
		rect.top = uiEntryRectY + 5 - yCurrentScroll;
		strText = pImageData->m_strTextureFormat;
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);
		*/
		uiEntryRectY += 15;

		/*
		todo

		// draw texture image preview
		if (bTexturePreviewIsEnabled)
		{
			//old = (HBITMAP)SelectObject(memDC, pImageData->m_hBitmap);

			uint32 uiImageWidthWhenHeightIs128 = (uint32)(((float32)128.0f / (float32)pImageData->m_uiHeight) * (float32)pImageData->m_uiWidth);
			uint32 uiImageHeightWhenWidthIs128 = (uint32)(((float32)128.0f / (float32)pImageData->m_uiWidth) * (float32)pImageData->m_uiHeight);

			uint32 uiDestWidth;
			uint32 uiDestHeight;
			if (uiImageWidthWhenHeightIs128 > uiImageHeightWhenWidthIs128)
			{
				uiDestWidth = 128;
				uiDestHeight = uiImageHeightWhenWidthIs128;
			}
			else
			{
				uiDestWidth = uiImageWidthWhenHeightIs128;
				uiDestHeight = 128;
			}
			
			pGFX->drawImage(Vec2i(uiEntryRectX + 20, uiEntryRectY - yCurrentScroll), pImageData->m_hBitmap, Vec2u(pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight));
			uiEntryRectY += 128;
		}
		*/

		uiEntryRectY += 10;

		// horizontal line below texture image
		pGFX->drawLine(Vec2i(vecMainPanelPosition.x, uiEntryRectY - 1 - yCurrentScroll), Vec2i(vecMainPanelPosition.x + 250, uiEntryRectY - 1 - yCurrentScroll));

		uiTextureIndex++;
		rectCOLEntry.top += 55;
		rectCOLEntry.bottom += 55;
	}

	// zoom text
	RECT rect;
	rect.left = vecMainPanelPosition.x + 250 + 100;
	rect.top = vecMainPanelPosition.y - 50;
	string strText = "Zoom:";
	pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

	m_pWindow->setRenderingStyleGroups("centerEntryPanel");
	Vec2u vecRectSize;
	vecRectSize.x = m_pWindow->getSize().x - (vecMainPanelPosition.x + 250);
	vecRectSize.y = m_pWindow->getSize().y - vecMainPanelPosition.y;
	pGFX->drawRectangle(Vec2i(vecMainPanelPosition.x + 250, vecMainPanelPosition.y), vecRectSize);
	m_pWindow->resetRenderingStyleGroups();

	if (pActiveCOLEntry)
	{
		// todo

		//uint32 uiDestinationWidth = (uint32)((float32)pActiveCOLEntry->m_uiWidth * getZoomLevel());
		//uint32 uiDestinationHeight = (uint32)((float32)pActiveCOLEntry->m_uiHeight * getZoomLevel());
		
		//pGFX->drawImage(Vec2i(vecMainPanelPosition.x + 250, vecMainPanelPosition.y), pActiveImageData->m_hBitmap, Vec2u(uiDestinationWidth, uiDestinationHeight));

		//render3D();
	}
	
	//getIMGF()->getEntryViewerManager()->getTextureViewer()->setWindowScrollbarMaxRange(uiImageY + 200);

	if (false)
	{
		// todo
		uint32 uiMaxXPosition = uiEntryRectX + uiCalculatedWidth + uiImagePaddingRight;
		if (clientRect.bottom > (int32)uiMaxXPosition)
		{
			uiMaxXPosition = clientRect.bottom;
		}
		uiMaxXPosition += 100;
		//getIMGF()->getEntryViewerManager()->getTextureViewer()->setSingleDisplayTypeTopScrollbarMaxXPosition(uiMaxXPosition);
	}

	SelectObject(memDC, old);
	DeleteDC(memDC);
}

// render editor 3d
void						CollisionEditorTab::render3D(void)
{
	static bool bInitd = false;
	static HBITMAP hbm;
	static HDC hdcWindow;

	Vec2u vecRenderSize = Vec2u(512, 512);

	if (!bInitd)
	{
		bInitd = true;





		//glfwInit();

		//glewExperimental = GL_TRUE;
		//GLenum err = glewInit();

		




		//hDC = GetDC(m_pWindow->getWindowHandle());
		hdcWindow = GetDC(m_pWindow->getWindowHandle());
		hDC = CreateCompatibleDC(hdcWindow);

		hbm = CreateCompatibleBitmap(hdcWindow, vecRenderSize.x, vecRenderSize.y);

		SelectObject(hDC, hbm);

		if (!hDC)
		{
			MessageBox(NULL, L"ERROR 1", L"A", MB_OK);
			return;
		}

		int bits = 32;
		static PIXELFORMATDESCRIPTOR pfd =	// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
			1,								// Version Number
			/*PFD_DRAW_TO_WINDOW |*/			// Format Must Support Window
			PFD_DRAW_TO_BITMAP |
			//PFD_SUPPORT_GDI
			PFD_SUPPORT_OPENGL// |			// Format Must Support OpenGL
			/*PFD_DOUBLEBUFFER*/,				// Must Support Double Buffering
			PFD_TYPE_RGBA,					// Request An RGBA Format
			bits,							// Select Our Color Depth
			0, 0, 0, 0, 0, 0,				// Color Bits Ignored
			0,								// No Alpha Buffer
			0,								// Shift Bit Ignored
			0,								// No Accumulation Buffer
			0, 0, 0, 0,						// Accumulation Bits Ignored
			16,								// 16Bit Z-Buffer (Depth Buffer)
			0,								// No Stencil Buffer
			0,								// No Auxiliary Buffer
			PFD_MAIN_PLANE,					// Main Drawing Layer
			0,								// Reserved
			0, 0, 0							// Layer Masks Ignored
		};

		GLuint PixelFormat = ChoosePixelFormat(hDC, &pfd);
		if (!PixelFormat)
		{
			MessageBox(NULL, L"ERROR 2", L"A", MB_OK);
			return;
		}

		BOOL bResult = SetPixelFormat(hDC, PixelFormat, &pfd);
		if (!bResult)
		{
			MessageBox(NULL, L"ERROR 3", L"A", MB_OK);
			return;
		}

		HGLRC hRC = wglCreateContext(hDC);
		if (!hRC)
		{
			MessageBox(NULL, L"ERROR 4", L"A", MB_OK);
			return;
		}

		bResult = wglMakeCurrent(hDC, hRC);
		if (!bResult)
		{
			MessageBox(NULL, L"ERROR 5", L"A", MB_OK);
			return;
		}




		
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);                         // Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
		
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_ALPHA_TEST);
		//glDisable(GL_STENCIL_TEST);
		//glDisable(GL_SCISSOR_TEST);
		
		glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

		float32 fHighestDistance = 1.5f;
		float32 fDistanceMultiplier = 2.0f;
		vecCameraPosition = { -2.0f, -2.0f, 2.0f };
		//vecCameraPosition = { 0.0f, 0.0f, 0.0f };
		//vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, Math::convertDegreesToRadians(45.0f), fHighestDistance * fDistanceMultiplier);
		//vecCameraRotation = { 0.0f, Math::convertDegreesToRadians(45.0f + 90), 0.0f };
	}

	mutexRendering.lock();
	


	//HANDLE hOld = SelectObject(hDC, hbm);
	
	
	const float64 ar = ((float64)vecRenderSize.x) / ((float64)vecRenderSize.y);

	glViewport(0, 0, vecRenderSize.x, vecRenderSize.y);
	//glScissor(x, y, w, h);
	//glEnable(GL_SCISSOR_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);
	GLenum a = glGetError();
	if (a != GL_NO_ERROR)
	{
		MessageBox(NULL, L"AAA", L"BBB", MB_OK);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	//gluPerspective(60.0, ar, 0.1, 100.0);
	//gluPerspective(50.0, 1.0, 1.0, 50.0);
	perspectiveGL(45.0, ar, 1.0, 1500.0);

	//glLoadMatrixf(fData);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//prepare2DRender();
	//if (glGetError()) Input::showMessage("test1.5 error", "Error"); 
	//renderBackground();

	//if (glGetError()) Input::showMessage("test2 error", "Error");

	//prepare3DRender();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	//glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	
	
	renderCamera();
	renderAxis();
	
	if (getActiveEntry())
	{
		//renderBoundingSphere();
		//renderBoundingCuboid();
		//renderCollisionObjects();
	}
	
	//glTranslatef(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y);

	//glTranslatef(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y);

	//if (glGetError()) Input::showMessage("test3 error", "Error");

	//prepare2DRender();
	//if (glGetError()) Input::showMessage("test3.5 error", "Error");
	//render2DObjects();

	//if (glGetError()) Input::showMessage("test4 error", "Error");

	//glDisable(GL_SCISSOR_TEST);

	//SwapBuffers(hDC);
	

	glFinish();


	

	BitBlt(hdcWindow, 139+139+250, 192, vecRenderSize.x, vecRenderSize.y, hDC, 0, 0, SRCCOPY);


	



	//SelectObject(hDC, hOld);
	//DeleteObject(hbm);
	//DeleteDC(hDC);




	mutexRendering.unlock();
}

void						CollisionEditorTab::prepare3DRender(void)
{
	//glUseProgram(ProgramObject_3DScene);
	//if (glGetError()) Input::showMessage("glUseProgram error", "Error");

	int w, h;
	//GLFWwindow window;
	//glfwGetWindowSize(&window, &w, &h);
	//const float64 ar = ((float64)w) / ((float64)h);
	//const float64 ar = ((float64)m_pWindow->getSize().x) / ((float64)m_pWindow->getSize().y);
	//const float64 ar = ((float64)300) / ((float64)300);

	
	
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	glClear(GL_DEPTH_BUFFER_BIT);
	*/
}

void						CollisionEditorTab::moveCamera(float32 fAngleDeg, float32 fRadius)
{
	vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, getCameraZRotation() + Math::convertDegreesToRadians(fAngleDeg), fRadius);
}

float32						CollisionEditorTab::getCameraZRotation(void)
{
	return Math::getAngleBetweenPoints(vecCameraLookAtPosition, vecCameraPosition);
}

float f = 0.0f;

void						CollisionEditorTab::renderCamera(void)
{
	Vec3f vecCameraRotation = {
		//Math::convertDegreesToRadians(0.0f),
		//0.0f,
		//Math::convertDegreesToRadians(-135.0f),
		Math::getAngleBetweenPoints(Vec3f(vecCameraPosition.x, vecCameraPosition.z, 0.0f), Vec3f(vecCameraLookAtPosition.x, vecCameraLookAtPosition.z, 0.0f)) - Math::convertDegreesToRadians(90.0f),
		0.0f,
		Math::getAngleBetweenPoints(vecCameraPosition, vecCameraLookAtPosition)// + Math::convertDegreesToRadians(90.0f)
	};
	//f += 0.03f;
	while (vecCameraRotation.x > 3.142) vecCameraRotation.x -= 3.142;
	while (vecCameraRotation.x < -3.142) vecCameraRotation.x += 3.142;
	while (vecCameraRotation.y > 3.142) vecCameraRotation.y -= 3.142;
	while (vecCameraRotation.y < -3.142) vecCameraRotation.y += 3.142;
	while (vecCameraRotation.z > 3.142) vecCameraRotation.z -= 3.142;
	while (vecCameraRotation.z < -3.142) vecCameraRotation.z += 3.142;
	//vecCameraRotation.z = -vecCameraRotation.z;

	// camera rotation
	glRotatef(-Math::convertRadiansToDegrees(vecCameraRotation.x), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(-Math::convertRadiansToDegrees(vecCameraRotation.z), 0.0f, 1.0f, 0.0f); // Rotate our camera on the y-axis (looking left and right)
	//glRotatef(-Math::convertRadiansToDegrees(vecCameraRotation.y), 0.0f, 0.0f, 1.0f);

	// camera position
	glTranslatef(-vecCameraPosition.x, -vecCameraPosition.z, -vecCameraPosition.y);

	//vecCameraRotation.x += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.03f);
}
void						CollisionEditorTab::renderCollisionObjects(void)
{
	glColor3ub(255, 255, 255);

	renderCollisionMeshes();
	renderCollisionCuboids();
	renderCollisionSpheres();
}

void						CollisionEditorTab::renderAxis(void)
{
	glBegin(GL_LINE_STRIP);
	glColor3ub(255, 0, 0);
	glVertex3f(-5000.0f, 0.0f, 0.0f);
	glVertex3f(5000.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 255, 0);
	glVertex3f(0.0f, 0.0f, -5000.0f);
	glVertex3f(0.0f, 0.0f, 5000.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 255);
	glVertex3f(0.0f, -5000.0f, 0.0f);
	glVertex3f(0.0f, 5000.0f, 0.0f);
	glEnd();
}

void						CollisionEditorTab::renderBoundingSphere(void)
{
	COLEntry *pCOLEntry = getActiveEntry();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians((float32)i), Math::convertDegreesToRadians(0.0f));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians(90.0f), Math::convertDegreesToRadians((float32)i));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians((float32)i), Math::convertDegreesToRadians(90.0f));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();
}

void						CollisionEditorTab::renderBoundingCuboid(void)
{
	COLEntry *pCOLEntry = getActiveEntry();

	glColor3ub(0, 255, 255);
	vector<Vec3f> vecVertices = Math::getCuboidFaceVerticesAsQuads(pCOLEntry->getBoundingObjects().m_vecMin, pCOLEntry->getBoundingObjects().m_vecMax);
	for (uint32 i = 0; i < vecVertices.size(); i += 4)
	{
		if ((i % 4) == 0)
		{
			glBegin(GL_LINE_LOOP);
		}
		for (uint32 i2 = 0; i2 < 4; i2++)
		{
			Vec3f& vecPosition = vecVertices[i + i2];
			glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		}
		if ((i % 4) == 0)
		{
			glEnd();
		}
	}
}

void						CollisionEditorTab::renderCollisionMeshes(void)
{
	COLEntry *pCOLEntry = getActiveEntry();

	// draw collision mesh faces & vertices
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);
	for (TFace& face : pCOLEntry->getCollisionMeshFaces())
	{
		TVertex& vecVector1 = pCOLEntry->getCollisionMeshVertices()[face.m_uiA];
		TVertex& vecVector2 = pCOLEntry->getCollisionMeshVertices()[face.m_uiB];
		TVertex& vecVector3 = pCOLEntry->getCollisionMeshVertices()[face.m_uiC];
		//Debugger::log("vecVector1: " + String::toString(vecVector1.x) + ", " + String::toString(vecVector1.y) + ", " + String::toString(vecVector1.z));
		//Debugger::log("vecVector2: " + String::toString(vecVector2.x) + ", " + String::toString(vecVector2.y) + ", " + String::toString(vecVector2.z));
		//Debugger::log("vecVector3: " + String::toString(vecVector3.x) + ", " + String::toString(vecVector3.y) + ", " + String::toString(vecVector3.z));
		glVertex3f(vecVector1.x, vecVector1.z, vecVector1.y);
		glVertex3f(vecVector2.x, vecVector2.z, vecVector2.y);
		glVertex3f(vecVector3.x, vecVector3.z, vecVector3.y);
	}
	glEnd();
}

void						CollisionEditorTab::renderCollisionCuboids(void)
{
	COLEntry *pCOLEntry = getActiveEntry();

	glBegin(GL_QUADS);
	//glColor3ub(255, 0, 0);

	//Debugger::log("collisionBox.m_min: " + String::toString(collisionBox.m_min.x) + ", " + String::toString(collisionBox.m_min.y) + ", " + String::toString(collisionBox.m_min.z));
	//Debugger::log("collisionBox.m_max: " + String::toString(collisionBox.m_max.x) + ", " + String::toString(collisionBox.m_max.y) + ", " + String::toString(collisionBox.m_max.z));
	uint32 i = 0;
	int i2 = 0;
	int colors[6][3] = {
		{ 255, 0, 0 },
		{ 0, 255, 0 },
		{ 0, 0, 255 },
		{ 255, 255, 0 },
		{ 255, 128, 0 },
		{ 50, 50, 50 }
	};
	for (TBox& collisionBox : pCOLEntry->getCollisionBoxes())
	{
		vector<Vec3f> vecVertices = Math::getCuboidFaceVerticesAsQuads(collisionBox.m_min, collisionBox.m_max);
		i = 0;
		i2 = 0;
		for (auto vecVertex : vecVertices)
		{
			//Debugger::log("vecVertex: " + String::toString(vecVertex.x) + ", " + String::toString(vecVertex.y) + ", " + String::toString(vecVertex.z));
			if ((i % 4) == 0)
			{
				glColor3ub(colors[i2][0], colors[i2][1], colors[i2][2]);
				i2++;
			}
			if ((i % 4) == 3)
			{
				//Debugger::log("--");
			}
			glVertex3f(vecVertex.x, vecVertex.z, vecVertex.y);
			i++;
		}
		//Debugger::log("------------------------------");
	}
	glEnd();
}

void						CollisionEditorTab::renderCollisionSpheres(void)
{
	COLEntry *pCOLEntry = getActiveEntry();

	// draw collision spheres
	uint32 i2 = 0;
	for (TSphere& collisionSphere : pCOLEntry->getCollisionSpheres())
	{
		//glColor3ub(colors[i2][0], colors[i2][1], colors[i2][2]);

		//glPushMatrix();
		//glTranslatef(collisionSphere.m_vecCenter.x, collisionSphere.m_vecCenter.z, collisionSphere.m_vecCenter.y); 
		//gluSphere(gluNewQuadric(), collisionSphere.m_fRadius, 100, 100);
		////////////////if (!isEntryChanging() && i2 < m_vecCollisionSpheresGL.size() && m_vecCollisionSpheresGL[i2] != nullptr)
		////////////////{
		////////////////	m_vecCollisionSpheresGL[i2]->draw(collisionSphere.m_vecCenter.x, collisionSphere.m_vecCenter.z, collisionSphere.m_vecCenter.y);
		////////////////}
		//glPopMatrix();

		i2++;
	}
}

// utility
void						perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}