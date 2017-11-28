#include "TextureEditorTab.h"
#include "nsbxgi.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/WTD/WTDFormat.h"
#include "Format/WTD/WTDManager.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/Text.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/DropDown.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "Format/TXD/TXDManager.h"
#include "Format/RW/Sections/RWSection_TextureDictionary.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "GUI/Editor/Editors/Entry/TextureEditorTabEntry.h"
#include "GraphicsLibrary/Base/ImageObject.h"
#include "Style/Parts/EStyleStatus.h"
#include "Stream/DataReader.h"
#include "../BXGI/Event/EEvent.h"
#include "Event/EInputEvent.h"
#include "Image/ImageManager.h"
#include "GUI/Editor/Base/Editor.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

TextureEditorTab::TextureEditorTab(void) :
	m_bIsTXDFile(false),
	m_pTXDFile(nullptr),
	m_pActiveTabEntry(nullptr),

	m_pZoomDropDown(nullptr),
	m_pVScrollBar(nullptr),

	m_fZoomLevel(1.0f),
	m_uiDisplayedEntryCount(0),
	m_pMouseDownOriginEntry(nullptr)
{
}

// events
void					TextureEditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &TextureEditorTab::repositionAndResizeControls);
	bindEvent(UNSERIALIZE_RW_SECTION, &TextureEditorTab::onUnserializeRWSection);
	bindEvent(SELECT_DROP_DOWN_ITEM, &TextureEditorTab::onSelectDropDownItem);
	bindEvent(LEFT_MOUSE_DOWN, &TextureEditorTab::onLeftMouseDown);
	bindEvent(LEFT_MOUSE_UP, &TextureEditorTab::onLeftMouseUp);
	bindEvent(MOVE_MOUSE, &TextureEditorTab::onMouseMove);
	bindEvent(KEY_DOWN, &TextureEditorTab::onKeyDown2);
	bindEvent(MOVE_MOUSE_WHEEL, &TextureEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void					TextureEditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &TextureEditorTab::repositionAndResizeControls);
	unbindEvent(UNSERIALIZE_RW_SECTION, &TextureEditorTab::onUnserializeRWSection);
	unbindEvent(SELECT_DROP_DOWN_ITEM, &TextureEditorTab::onSelectDropDownItem);
	unbindEvent(LEFT_MOUSE_DOWN, &TextureEditorTab::onLeftMouseDown);
	unbindEvent(LEFT_MOUSE_UP, &TextureEditorTab::onLeftMouseUp);
	unbindEvent(MOVE_MOUSE, &TextureEditorTab::onMouseMove);
	unbindEvent(KEY_DOWN, &TextureEditorTab::onKeyDown2);
	unbindEvent(MOVE_MOUSE_WHEEL, &TextureEditorTab::onMouseWheelMove2);

	EditorTab::unbindEvents();
}

// controls
void					TextureEditorTab::addControls(void)
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

void					TextureEditorTab::initControls(void)
{
	repositionAndResizeControls(Vec2i(0, 0));
}

void					TextureEditorTab::repositionAndResizeControls(Vec2i& vecSizeChange)
{
	EditorTab::repositionAndResizeControls(vecSizeChange);

	// entry list vertical scroll bar
	// todo m_pVScrollBar->setSize(m_pVScrollBar->getSize() + Vec2u(0, vecSizeChange.y));
	m_pVScrollBar->setSize(Vec2u(m_pVScrollBar->getSize().x, m_pWindow->getSize().y - m_pVScrollBar->getPosition().y));
}

// add entry
void					TextureEditorTab::addEntryAfter(FormatEntry *pEntry)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureNative *pTexture = (RWSection_TextureNative*) pEntry;
		prepareTexture_TXD(pTexture);
	}
	else
	{
		WTDEntry *pTexture = (WTDEntry*) pEntry;
		prepareTexture_WTD(pTexture);
	}

	// todo
	//updateIMGText();
}

// editor input
void					TextureEditorTab::onSelectDropDownItem(DropDownItem *pItem)
{
	string strActiveZoomText = m_pZoomDropDown->getActiveItem()->getText();
	float32 fZoomLevel = ((float32)String::toUint32(strActiveZoomText.substr(0, strActiveZoomText.length() - 1))) / 100.0f;
	setZoomLevel(fZoomLevel);
}

bool						TextureEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
	TextureEditorTabEntry
		*pActiveTabEntry = nullptr;
	uint32
		uiActiveImageIndex,
		uiRowHeight = 50;
	float32
		fVProgress = m_pVScrollBar ? m_pVScrollBar->getProgress() : 0.0f;

	for (uint32
		uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
		uiEntryIndex = Math::getEntryStartIndex(getEntryCount(), uiMaxEntryCount, fVProgress),
		uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(getEntryCount(), uiEntryIndex, uiMaxEntryCount);
		uiEntryIndex < uiEntryEndIndexExclusive;
		uiEntryIndex++
		)
	{
		TextureEditorTabEntry *pImageData = getEntryByIndex(uiEntryIndex);
		if (!pImageData)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

		if (vecCursorPosition.x >= pImageData->m_rect.left
			&& vecCursorPosition.y >= pImageData->m_rect.top
			&& vecCursorPosition.x <= (pImageData->m_rect.right - (m_pVScrollBar ? m_pVScrollBar->getSize().x : 0))
			&& vecCursorPosition.y <= pImageData->m_rect.bottom)
		{
			uiActiveImageIndex = uiEntryIndex;
			pActiveTabEntry = pImageData;
			break;
		}
	}
	if (pActiveTabEntry != nullptr)
	{
		if (m_pWindow->isMovingWindow())
		{
			m_pWindow->checkToStopMovingOrResizingWindow();
		}

		m_pMouseDownOriginEntry = pActiveTabEntry;
		if (!pActiveTabEntry->m_bIsActive)
		{
			clearActiveEntries();
		}
		setActiveEntry(pActiveTabEntry);
		m_pWindow->render();

		return false;
	}

	return true;
}

void						TextureEditorTab::onLeftMouseUp(Vec2i vecCursorPosition)
{
	m_pMouseDownOriginEntry = nullptr;
}

void						TextureEditorTab::onMouseMove(Vec2i vecCursorPosition)
{
	static bool bDoingDragDrop = false;
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && m_pMouseDownOriginEntry != nullptr && !bDoingDragDrop)
	{
		bDoingDragDrop = true;
		startDragDrop(this, "BMP");
		m_pMouseDownOriginEntry = nullptr;
		bDoingDragDrop = false;
	}
}

void						TextureEditorTab::onKeyDown2(uint16 uiKey)
{
	int32 iNextTextureIndex;
	int32 wScrollNotify;
	uint32 uiMinTextureIndex = 0;
	uint32 uiMaxTextureIndex = getEntryCount() - 1;
	uint32 yCurrentScroll = 0;
	TextureEditorTabEntry *pTexData;

	switch (uiKey)
	{
	case VK_PRIOR:
		iNextTextureIndex = getActiveEntry()->m_uiIndex - 5;
		if (iNextTextureIndex < 0)
		{
			iNextTextureIndex = 0;
		}
		pTexData = getEntryByIndex(iNextTextureIndex);
		setActiveEntry(pTexData);
		if (!pTexData->isCompletelyDisplayed())
		{
			yCurrentScroll -= ((pTexData->m_rect.bottom - pTexData->m_rect.top) + 1) * 5;
			if (yCurrentScroll < 0)
			{
				yCurrentScroll = 0;
			}
		}
		m_pWindow->render();
		break;

	case VK_NEXT:
		iNextTextureIndex = getActiveEntry()->m_uiIndex + 5;
		if (iNextTextureIndex > (int32)uiMaxTextureIndex)
		{
			iNextTextureIndex = uiMaxTextureIndex;
		}
		pTexData = getEntryByIndex(iNextTextureIndex);
		setActiveEntry(pTexData);
		if (!pTexData->isCompletelyDisplayed())
		{
			yCurrentScroll += ((pTexData->m_rect.bottom - pTexData->m_rect.top) + 1) * 5;
		}
		m_pWindow->render();
		break;

	case VK_UP:
		iNextTextureIndex = ((int32)getActiveEntry()->m_uiIndex) - 1;
		if (iNextTextureIndex >= 0)
		{
			pTexData = getEntryByIndex(iNextTextureIndex);
			setActiveEntry(pTexData);
			if (!pTexData->isCompletelyDisplayed())
			{
				yCurrentScroll -= (pTexData->m_rect.bottom - pTexData->m_rect.top) + 1;
				if (yCurrentScroll < 0)
				{
					yCurrentScroll = 0;
				}
			}
			m_pWindow->render();
		}
		break;

	case VK_DOWN:
		iNextTextureIndex = getActiveEntry()->m_uiIndex + 1;
		if (iNextTextureIndex <= (int32)uiMaxTextureIndex)
		{
			pTexData = getEntryByIndex(iNextTextureIndex);
			setActiveEntry(pTexData);
			if (!pTexData->isCompletelyDisplayed())
			{
				yCurrentScroll += (pTexData->m_rect.bottom - pTexData->m_rect.top) + 1;
			}
			m_pWindow->render();
		}
		break;

	case VK_HOME:
		if (getEntryCount() > 0)
		{
			setActiveEntry(getFirstEntry());
			m_pWindow->render();
		}
		wScrollNotify = SB_TOP;
		break;

	case VK_END:
		if (getEntryCount() > 0)
		{
			setActiveEntry(getLastEntry());
			m_pWindow->render();
		}
		wScrollNotify = SB_BOTTOM;
		break;
	}
}

void					TextureEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	int iDelta = -(iRotationDistance / WHEEL_DELTA);
	float32 fNewProgress = m_pVScrollBar->getProgress() + (iDelta * m_pVScrollBar->getProgressFor1Item());
	fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
	m_pVScrollBar->setProgress(fNewProgress);

	m_pWindow->render();
}

// file unserialization
bool					TextureEditorTab::unserializeFile(void)
{
	string strFileExtension = String::toUpperCase(Path::getFileExtension(m_pFile->getFilePath()));

	if (!m_pFile->openFile())
	{
		return false;
	}

	if (!m_pFile->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(m_pFile->getErrorCode()) + "\r\n\r\n" + m_pFile->getFilePath(), "Can't Open " + strFileExtension + " File");
		delete m_pFile;
		return false;
	}

	uint32 uiProgressBarMax = m_pFile->m_reader.getSize();
	getProgressBar()->setMax(uiProgressBarMax);

	if (!m_pFile->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(m_pFile->getErrorCode()) + "\r\n\r\n" + m_pFile->getFilePath(), "Can't Open " + strFileExtension + " File");
		delete m_pFile;
		return false;
	}

	if (m_bIsTXDFile)
	{
		setTXDFile((TXDFormat*)m_pFile);
	}
	else
	{
		setWTDFile((WTDFormat*)m_pFile);
	}

	return true;
}

void					TextureEditorTab::onUnserializeRWSection(RWSection *pRWSection)
{
	uint32 uiCurrentProgressBytes = pRWSection->getRWFormat()->m_reader.getSeek();
	getProgressBar()->setCurrent(uiCurrentProgressBytes);
}

void					TextureEditorTab::onFileLoaded(void)
{
	string strFilePath = getFile()->getFilePath();

	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), strFilePath);

	// prepare render data
	if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "TXD")
	{
		prepareRenderData_TXD();
	}
	else if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "WTD")
	{
		prepareRenderData_WTD();
	}

	calculateDisplayedEntryCount();

	// render
	m_pWindow->render();

	// display TXD info
	setFileInfoText();
}

void					TextureEditorTab::calculateDisplayedEntryCount(void)
{
	uint32 uiMatchCount = 0;
	for(TextureEditorTabEntry *pTabEntry : getEntries())
	{
		if (doesTabEntryMatchFilter(pTabEntry))
		{
			uiMatchCount++;
		}
	}
	m_uiDisplayedEntryCount = uiMatchCount;
}

// prepare render data
bool						TextureEditorTab::prepareRenderData_TXD(void)
{
	m_bIsTXDFile = true;

	vector<RWSection_TextureNative*> vecTextures = m_pTXDFile->getTextures();

	if (m_pVScrollBar)
	{
		m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
		m_pVScrollBar->setItemCount(VERTICAL, vecTextures.size() * 50);
	}

	for (RWSection_TextureNative *pRWSection_TextureNative : vecTextures)
	{
		prepareTexture_TXD(pRWSection_TextureNative);
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getFirstEntry());
	}

	return true;
}

void						TextureEditorTab::prepareTexture_TXD(RWSection_TextureNative *pRWSection_TextureNative)
{
	TextureEditorTabEntry *pTabEntry = new TextureEditorTabEntry;

	if (pRWSection_TextureNative->getMipMaps().getEntryCount() == 0)
	{
		// the texture does not have a mipmap
		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_bTextureContainsNoMipmaps = true;
	}
	else
	{
		RWEntry_TextureNative_MipMap *pMipmap = pRWSection_TextureNative->getMipMaps().getEntryByIndex(0);
		string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
		const char *pBmpImageData = strBMPImageDataStr.c_str();

		HBITMAP hBitmap = CreateBitmap(pMipmap->getImageSize().x, pMipmap->getImageSize().y, 1, 32, pBmpImageData);

		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_hBitmap = hBitmap;
		pTabEntry->m_uiWidth = pRWSection_TextureNative->getImageSize().x;
		pTabEntry->m_uiHeight = pRWSection_TextureNative->getImageSize().y;
		pTabEntry->m_strDiffuseName = pRWSection_TextureNative->getDiffuseName();
		pTabEntry->m_strAlphaName = pRWSection_TextureNative->getAlphaName();
		pTabEntry->m_ucBPP = pRWSection_TextureNative->getOriginalBPP() == 0 ? pRWSection_TextureNative->getBPP() : pRWSection_TextureNative->getOriginalBPP();
		pTabEntry->m_strTextureFormat = TXDManager::getTXDRasterFormatText(pRWSection_TextureNative->getTXDRasterDataFormat(), pRWSection_TextureNative->getDXTCompressionType());
		pTabEntry->m_bIsActive = false;
	}

	addEntry(pTabEntry);
}

bool						TextureEditorTab::prepareRenderData_WTD(void)
{
	m_bIsTXDFile = false;

	if (!m_pWTDFile)
	{
		return false;
	}

	vector<WTDEntry*> vecWTDEntries = m_pWTDFile->getEntries();
	for (WTDEntry *pWTDEntry : vecWTDEntries)
	{
		prepareTexture_WTD(pWTDEntry);
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getFirstEntry());
	}

	return true;
}

void						TextureEditorTab::prepareTexture_WTD(WTDEntry *pWTDEntry)
{
	TextureEditorTabEntry *pTabEntry = new TextureEditorTabEntry;

	if (pWTDEntry->getEntryCount() == 0)
	{
		// the texture does not have a mipmap
		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_bTextureContainsNoMipmaps = true;
	}
	else
	{
		WTDMipmap *pMipmap = pWTDEntry->getEntryByIndex(0);
		string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
		const char *pBmpImageData = strBMPImageDataStr.c_str();

		HBITMAP hBitmap = CreateBitmap(pWTDEntry->getImageSize(true), pWTDEntry->getImageSize(false), 1, 32, pBmpImageData);

		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_hBitmap = hBitmap;
		pTabEntry->m_uiWidth = pWTDEntry->getImageSize(true);
		pTabEntry->m_uiHeight = pWTDEntry->getImageSize(false);
		pTabEntry->m_strDiffuseName = pWTDEntry->getEntryName();
		pTabEntry->m_strAlphaName = "";
		pTabEntry->m_ucBPP = 32;
		pTabEntry->m_strTextureFormat = ImageManager::getD3DFormatText(pWTDEntry->getD3DFormat());
		pTabEntry->m_bIsActive = false;
	}

	addEntry(pTabEntry);
}

// filter
bool						TextureEditorTab::doesTabEntryMatchFilter(TextureEditorTabEntry *pTabEntry)
{
	string strSearchTextUpper = String::toUpperCase(m_pSearchBox->getText());
	return strSearchTextUpper == "" || String::isIn(String::toUpperCase(pTabEntry->m_strDiffuseName), strSearchTextUpper, false);
}

// render editor
void						TextureEditorTab::renderDisplayType_Single(void)
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
	//todo
	BOOL bPremultipledAlphaApplied = FALSE; /////

	if (!bPremultipledAlphaApplied)
	{
		for (TextureEditorTabEntry *pTabEntry : getEntries())
		{
			PremultiplyBitmapAlpha(hdc, pTabEntry->m_hBitmap);
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
	TextureEditorTabEntry
		*pActiveImageData = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = false;
	float32
		fVProgress = m_pVScrollBar ? m_pVScrollBar->getProgress() : 0.0f;

	for(uint32
			uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
			uiEntryIndex = Math::getEntryStartIndex(getEntryCount(), uiMaxEntryCount, fVProgress),
			uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(getEntryCount(), uiEntryIndex, uiMaxEntryCount),
			uiDisplayedEntryCount = 0,
			uiEntryCount = getEntryCount();
		uiEntryIndex < uiEntryCount;
		uiEntryIndex++
	)
	{
		if (uiDisplayedEntryCount > uiMaxEntryCount)
		{
			break;
		}

		TextureEditorTabEntry *pImageData = getEntryByIndex(uiEntryIndex);
		if (!pImageData)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

		if (!doesTabEntryMatchFilter(pImageData))
		{
			continue;
		}

		uiDisplayedEntryCount++;

		if (bTexturePreviewIsEnabled)
		{
			pImageData->m_rect.left = vecMainPanelPosition.x;
			pImageData->m_rect.top = uiEntryRectY;
			pImageData->m_rect.right = vecMainPanelPosition.x + 250;
			pImageData->m_rect.bottom = uiEntryRectY + 45 + 128 + 10;
		}
		else
		{
			pImageData->m_rect.left = vecMainPanelPosition.x;
			pImageData->m_rect.top = uiEntryRectY;
			pImageData->m_rect.right = vecMainPanelPosition.x + 250;
			pImageData->m_rect.bottom = uiEntryRectY + 45 + 10;
		}

		uiCalculatedWidth = 0;

		// calculate max width out of: image, diffuse text and alpha text
		SIZE textSize;
		GetTextExtentPoint32(hdc, String::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &textSize);
		uiCalculatedWidth = textSize.cx;

		SIZE textSize2;
		GetTextExtentPoint32(hdc, String::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &textSize2);
		if (textSize2.cx > (int32)uiCalculatedWidth)
		{
			uiCalculatedWidth = textSize2.cx;
		}

		if (pImageData->m_uiWidth > uiCalculatedWidth)
		{
			uiCalculatedWidth = pImageData->m_uiWidth;
		}

		// draw active texture background colour
		RECT rect2 = pImageData->m_rect;

		m_pWindow->setRenderingStyleGroups("leftEntryPanel");
		if (pImageData->m_bIsActive)
		{
			m_pWindow->setRenderingStyleStatus(EStyleStatus::ACTIVE);
		}
		pGFX->drawRectangle(Vec2i(rect2.left, rect2.top), Vec2u(rect2.right - rect2.left, rect2.bottom - rect2.top));
		m_pWindow->resetRenderingStyleGroups();
		m_pWindow->resetRenderingStyleStatus();

		// draw texture number
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

		// draw texture diffuse name
		uint32 uiXOffset1 = 50;

		rect.left = uiEntryRectX + uiXOffset1;
		rect.top = uiEntryRectY + 5 - yCurrentScroll;
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), pImageData->m_strDiffuseName);
		uiEntryRectY += 15;

		// draw texture alpha name
		if (pImageData->m_strAlphaName != "")
		{
			rect.left = uiEntryRectX + uiXOffset1;
			rect.top = uiEntryRectY + 5 - yCurrentScroll;
			pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), pImageData->m_strAlphaName);
		}
		uiEntryRectY += 15;

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

		uiEntryRectY += 15;

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

		uiEntryRectY += 10;

		// horizontal line below texture image
		pGFX->drawLine(Vec2i(vecMainPanelPosition.x, uiEntryRectY - 1 - yCurrentScroll), Vec2i(vecMainPanelPosition.x + 250, uiEntryRectY - 1 - yCurrentScroll));

		uiTextureIndex++;
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

	if (pActiveImageData)
	{
		uint32 uiDestinationWidth = (uint32)((float32)pActiveImageData->m_uiWidth * getZoomLevel());
		uint32 uiDestinationHeight = (uint32)((float32)pActiveImageData->m_uiHeight * getZoomLevel());
		
		pGFX->drawImage(Vec2i(vecMainPanelPosition.x + 250, vecMainPanelPosition.y), pActiveImageData->m_hBitmap, Vec2u(uiDestinationWidth, uiDestinationHeight));
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

// file info text
void					TextureEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	if (m_bIsTXDFile)
	{
		string strVersionText = RWManager::get()->getVersionManager()->getVersionText(getTXDFile()->getRawVersion());
		string strVersionGames = getTXDFile()->getRWVersion() ? getTXDFile()->getRWVersion()->getGamesAsString() : "Unknown";

		m_pText_FileVersion->setText(strVersionText);
		m_pText_FileGame->setText(strVersionGames);
	}
	else
	{
		m_pText_FileVersion->setText(string("Unknown"), false);
		m_pText_FileGame->setText(string("GTA IV"));
	}

	updateEntryCountText();
}

void					TextureEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = m_uiDisplayedEntryCount,
		uiTotalEntryCount = getEntryCount();
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

vector<FormatEntry*>	TextureEditorTab::getSelectedEntries(void)
{
	uint32 uiIndex = 0;
	vector<FormatEntry*> vecEntries;
	if (m_bIsTXDFile)
	{
		for (RWSection_TextureNative *pTextureNative : getTXDFile()->getTextures())
		{
			if (m_vecEntries[uiIndex]->m_bIsActive)
			{
				vecEntries.push_back(pTextureNative);
			}
			uiIndex++;
		}
	}
	else
	{
		for (WTDEntry *pWTDEntry : getWTDFile()->getEntries())
		{
			if (m_vecEntries[uiIndex]->m_bIsActive)
			{
				vecEntries.push_back(pWTDEntry);
			}
			uiIndex++;
		}
	}
	return vecEntries;
}

uint32					TextureEditorTab::getSelectedEntryCount(void)
{
	uint32 uiIndex = 0;
	uint32 uiSelectedItemCount = 0;
	if (m_bIsTXDFile)
	{
		for (RWSection_TextureNative *pTextureNative : getTXDFile()->getTextures())
		{
			if (m_vecEntries[uiIndex]->m_bIsActive)
			{
				uiSelectedItemCount++;
			}
			uiIndex++;
		}
	}
	else
	{
		for (WTDEntry *pWTDEntry : getWTDFile()->getEntries())
		{
			if (m_vecEntries[uiIndex]->m_bIsActive)
			{
				uiSelectedItemCount++;
			}
			uiIndex++;
		}
	}
	return uiSelectedItemCount;
}

uint32					TextureEditorTab::getTotalEntryCount(void)
{
	if (m_bIsTXDFile)
	{
		return getTXDFile()->getTextures().size();
	}
	else
	{
		return getWTDFile()->getEntries().size();
	}
}

void					TextureEditorTab::onEntryChange(FormatEntry *pEntry)
{
	uint32 uiIndex;
	if (m_bIsTXDFile)
	{
		uiIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)(RWSection_TextureNative*)pEntry);
	}
	else
	{
		uiIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pEntry);
	}
	TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiIndex);

	pTabEntry->m_strDiffuseName = pEntry->getEntryName();
	if (pTabEntry->m_strAlphaName != "")
	{
		pTabEntry->m_strAlphaName = pEntry->getEntryName() + "a";
	}
}

void					TextureEditorTab::onSortEntries(vector<FormatEntry*>& vecEntries)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureDictionary *pTextureDictionary = (RWSection_TextureDictionary*)getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_DICTIONARY)[0];

		pTextureDictionary->removeAllEntries();

		for (FormatEntry *pEntry : vecEntries)
		{
			pTextureDictionary->addEntry((RWSection_TextureNative*)pEntry);
		}
	}
}

void					TextureEditorTab::merge(string& strFilePath)
{
	getContainerFile()->merge(strFilePath);
}




void					TextureEditorTab::recreateEntryList(void)
{
	VectorPool::removeAllEntries();
	if(m_bIsTXDFile)
	{
		prepareRenderData_TXD();
	}
	else
	{
		prepareRenderData_WTD();
	}
	calculateDisplayedEntryCount();
	updateEntryCountText();
	m_pWindow->render();
}

void					TextureEditorTab::removeAllEntries(void)
{
	if (m_bIsTXDFile)
	{
		for (RWSection *pRWSection : getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE))
		{
			RWSection_TextureNative *pTXDEntry = (RWSection_TextureNative*)pRWSection;
			pTXDEntry->removeSection();
			Events::trigger(TASK_PROGRESS);
		}
	}
	else
	{
		getWTDFile()->removeAllEntries();
	}

	m_pActiveTabEntry = nullptr;

	recreateEntryList();
	updateEntryCountText();
}

void					TextureEditorTab::removeEntries(vector<FormatEntry*>& vecEntries)
{
	if (m_bIsTXDFile)
	{
		for (FormatEntry *pEntry : vecEntries)
		{
			RWSection_TextureNative *pTXDEntry = (RWSection_TextureNative*)pEntry;
			pTXDEntry->removeSection();
			Events::trigger(TASK_PROGRESS);
		}
	}
	else
	{
		for (FormatEntry *pEntry : vecEntries)
		{
			WTDEntry *pWTDEntry = (WTDEntry*)pEntry;
			getWTDFile()->removeEntry(pWTDEntry);
			Events::trigger(TASK_PROGRESS);
		}
	}

	m_pActiveTabEntry = nullptr;

	recreateEntryList();
	updateEntryCountText();
}

void					TextureEditorTab::clearActiveEntries(void)
{
	for (TextureEditorTabEntry *pTabEntry : getEntries())
	{
		pTabEntry->m_bIsActive = false;
	}
	setActiveEntry(nullptr);
}

void					TextureEditorTab::setEntriesSelected(vector<FormatEntry*>& vecEntries, bool bIsSelected)
{
	clearActiveEntries();
	for (FormatEntry *pFormatEntry : vecEntries)
	{
		if (m_bIsTXDFile)
		{
			RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pFormatEntry;
			uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
			TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
			pTabEntry->m_bIsActive = bIsSelected;
		}
		else
		{
			uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pFormatEntry);
			TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
			pTabEntry->m_bIsActive = bIsSelected;
		}
	}
	m_pWindow->render();
}

void					TextureEditorTab::setEntrySelected(FormatEntry *pEntry, bool bIsSelected)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pEntry;
		uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
		TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		pTabEntry->m_bIsActive = bIsSelected;
	}
	else
	{
		uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pEntry);
		TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		pTabEntry->m_bIsActive = bIsSelected;
	}
}

bool					TextureEditorTab::isEntrySelected(FormatEntry *pEntry)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pEntry;
		uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
		TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		return pTabEntry->m_bIsActive;
	}
	else
	{
		uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pEntry);
		TextureEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		return pTabEntry->m_bIsActive;
	}
}