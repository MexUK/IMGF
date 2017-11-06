#include "RadarEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Control/Controls/TextBox.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/WTD/WTDFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/Text.h"
#include "../bxgi/Event/EEvent.h"
#include "Task/TaskManager.h"
#include "Format/TXD/TXDManager.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "GUI/Editor/Editors/Entry/RadarEditorTabEntry.h"
#include "GraphicsLibrary/Libraries/GraphicsLibrary_GDIPlus.h"
#include "Image/ImageManager.h"
#include "GUI/Editor/Base/Editor.h"
#include "Style/Parts/EStyleStatus.h"
#include "Event/EInternalEvent.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::styles::statuses;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

BOOL bPremultipledAlphaApplied = FALSE; // todo - namespace

inline void PremultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp)
{
	BITMAP bm = { 0 };
	GetObject(hBmp, sizeof(bm), &bm);
	BITMAPINFO* bmi = (BITMAPINFO*)_alloca(sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
	::ZeroMemory(bmi, sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BOOL bRes = ::GetDIBits(hDC, hBmp, 0, bm.bmHeight, NULL, bmi, DIB_RGB_COLORS);
	if (!bRes || bmi->bmiHeader.biBitCount != 32) return;
	LPBYTE pBitData = (LPBYTE) ::LocalAlloc(LPTR, bm.bmWidth * bm.bmHeight * sizeof(DWORD));
	if (pBitData == NULL) return;
	LPBYTE pData = pBitData;
	::GetDIBits(hDC, hBmp, 0, bm.bmHeight, pData, bmi, DIB_RGB_COLORS);
	for (int y = 0; y < bm.bmHeight; y++) {
		for (int x = 0; x < bm.bmWidth; x++) {
			pData[0] = (BYTE)((DWORD)pData[0] * pData[3] / 255);
			pData[1] = (BYTE)((DWORD)pData[1] * pData[3] / 255);
			pData[2] = (BYTE)((DWORD)pData[2] * pData[3] / 255);
			pData += 4;
		}
	}
	::SetDIBits(hDC, hBmp, 0, bm.bmHeight, pBitData, bmi, DIB_RGB_COLORS);
	::LocalFree(pBitData);
}

RadarEditorTab::RadarEditorTab(void) :
	m_pIMGFile(nullptr),
	m_pActiveTabEntry(nullptr)
{
}

// controls
void						RadarEditorTab::addControls(void)
{
	int32 x, y;
	uint32 w, h, uiLogWidth;

	uiLogWidth = 335;

	x = 139 + 139 + 250 + 100 + 51;
	y = ((162 + 30) - 50) - 1;
	w = 80;
	h = 20;

	// vertical scroll bar
	x = 139 + 139 + 250;
	y = 192;
	w = 15;
	h = m_pWindow->getSize().y - y;
	x -= w;

	m_pVScrollBar = addScrollBar(x, y, w, h, "", -1, 50);
	m_pVScrollBar->setScrollOrientation(VERTICAL);
}

void						RadarEditorTab::initControls(void)
{
	repositionAndResizeControls(Vec2i(0, 0));
}

void						RadarEditorTab::repositionAndResizeControls(Vec2i& vecSizeChange)
{
	// entry list vertical scroll bar
	// todo m_pVScrollBar->setSize(m_pVScrollBar->getSize() + Vec2u(0, vecSizeChange.y));
	m_pVScrollBar->setSize(Vec2u(m_pVScrollBar->getSize().x, m_pWindow->getSize().y - m_pVScrollBar->getPosition().y));
}

// events
void						RadarEditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &RadarEditorTab::repositionAndResizeControls);
	bindEvent(UNSERIALIZE_IMG_ENTRY, &RadarEditorTab::onUnserializeEntry);
	bindEvent(LEFT_MOUSE_DOWN, &RadarEditorTab::onLeftMouseDown);
	bindEvent(KEY_DOWN, &RadarEditorTab::onKeyDown2);
	bindEvent(MOVE_MOUSE_WHEEL, &RadarEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void						RadarEditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &RadarEditorTab::repositionAndResizeControls);
	unbindEvent(UNSERIALIZE_IMG_ENTRY, &RadarEditorTab::onUnserializeEntry);
	unbindEvent(LEFT_MOUSE_DOWN, &RadarEditorTab::onLeftMouseDown);
	unbindEvent(KEY_DOWN, &RadarEditorTab::onKeyDown2);
	unbindEvent(MOVE_MOUSE_WHEEL, &RadarEditorTab::onMouseWheelMove2);

	EditorTab::unbindEvents();
}

void						RadarEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
	RadarEditorTabEntry
		*pActiveTabEntry = nullptr;
	uint32
		uiActiveImageIndex,
		uiRowHeight = 50;
	float32
		fVProgress = m_pVScrollBar->getProgress();

	for (uint32
		uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
		uiEntryIndex = Math::getEntryStartIndex(getEntryCount(), uiMaxEntryCount, fVProgress),
		uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(getEntryCount(), uiEntryIndex, uiMaxEntryCount);
		uiEntryIndex < uiEntryEndIndexExclusive;
		uiEntryIndex++
		)
	{
		RadarEditorTabEntry *pImageData = getEntryByIndex(uiEntryIndex);
		if (!pImageData)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

		if (vecCursorPosition.x >= pImageData->m_rect.left
			&& vecCursorPosition.y >= pImageData->m_rect.top
			&& vecCursorPosition.x <= (pImageData->m_rect.right - m_pVScrollBar->getSize().x)
			&& vecCursorPosition.y <= pImageData->m_rect.bottom)
		{
			uiActiveImageIndex = uiEntryIndex;
			pActiveTabEntry = pImageData;
			break;
		}
	}
	if (pActiveTabEntry != nullptr)
	{
		setActiveEntry(pActiveTabEntry);
		m_pWindow->render();
	}
}

void						RadarEditorTab::onKeyDown2(uint16 uiKey)
{
	int32 iNextTextureIndex;
	int32 wScrollNotify;
	uint32 uiMinTextureIndex = 0;
	uint32 uiMaxTextureIndex = getEntryCount() - 1;
	uint32 yCurrentScroll = 0;
	RadarEditorTabEntry *pTexData;

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
		if (iNextTextureIndex >(int32)uiMaxTextureIndex)
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

void						RadarEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	int iDelta = -(iRotationDistance / WHEEL_DELTA);
	float32 fNewProgress = m_pVScrollBar->getProgress() + (iDelta * m_pVScrollBar->getProgressFor1Item());
	fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
	m_pVScrollBar->setProgress(fNewProgress);

	m_pWindow->render();
}

// unserialize entry
void						RadarEditorTab::onUnserializeEntry(IMGFormat *img)
{
	if (img != m_pIMGFile)
	{
		return;
	}

	getIMGF()->getTaskManager()->onTaskProgressTick();
}

// file loading
bool						RadarEditorTab::unserializeFile(void)
{
	IMGFormat *img = getIMGFile();

	/*
	progress bar: 2 stages

	[IMG versions 1, 2, and fastman92]
	- parsing header
	- parsing RW versions
	//- adding entries to grid

	[IMG versions 3 (encrypted and unencrypted)]
	- parsing header
	- parsing entry names
	//- adding entries to grid
	*/

	if (!img->openFile())
	{
		return false;
	}
	if (!img->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	uint32
		uiProgressBarMaxMultiplier = 2,
		uiProgressBarMax = img->m_uiEntryCount * uiProgressBarMaxMultiplier;
	getProgressBar()->setMax(uiProgressBarMax);

	if (!img->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	return true;
}

void						RadarEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// prepare render data
	if (getIMGFile()->getVersion() == IMG_3)
	{
		prepareRenderData_WTD();
	}
	else
	{
		prepareRenderData_TXD();
	}

	// display file info
	setFileInfoText();

	// render
	m_pWindow->render();
}

// file info text
void						RadarEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getIMGFile()->getIMGFilePath());
	m_pText_FileVersion->setText(IMGManager::getVersionText(getIMGFile()->getVersion(), getIMGFile()->isEncrypted()));

	if (getEntryCount() == 64 && getFirstEntry()->m_ucBPP == 32)
	{
		// GTA III
		m_pText_FileGame->setText(string("GTA III"));
	}
	else if (getEntryCount() == 64 && getFirstEntry()->m_strAlphaName == "" && getFirstEntry()->m_ucBPP == 16)
	{
		// GTA VC
		m_pText_FileGame->setText(string("GTA VC"));
	}
	else if (getEntryCount() == 128 && getFirstEntry()->m_strAlphaName == "" && getFirstEntry()->m_ucBPP == 16)
	{
		// GTA SA
		m_pText_FileGame->setText(string("GTA SA"));
	}
	else if (getEntryCount() == 63)
	{
		// GTA IV
		m_pText_FileGame->setText(string("GTA IV"));
	}
	else if (getEntryCount() == 1296)
	{
		// SOL
		m_pText_FileGame->setText(string("SOL"));
	}
	else
	{
		// Unknown
		m_pText_FileGame->setText(IMGManager::getVersionGames(getIMGFile()->getVersion()));
	}

	updateEntryCountText();
}

void						RadarEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = 0;
	
	for (IMGEntry *pIMGEntry : m_pIMGFile->VectorPool::getEntries())
	{
		if (!(pIMGEntry->isTextureFile() && String::toUpperCase(pIMGEntry->getEntryName().substr(0, 5)) == "RADAR" && String::isPositiveInteger(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5))))
		{
			continue;
		}
		uiDisplayedEntryCount++;
	}

	uint32
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

// prepare render data
void						RadarEditorTab::prepareRenderData_TXD(void)
{
	bPremultipledAlphaApplied = FALSE;

	vector<IMGEntry*> vecRadarIMGEntries;
	for (IMGEntry *pIMGEntry : m_pIMGFile->VectorPool::getEntries())
	{
		if (!(pIMGEntry->isTextureFile() && String::toUpperCase(pIMGEntry->getEntryName().substr(0, 5)) == "RADAR" && String::isPositiveInteger(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5))))
		{
			continue;
		}
		vecRadarIMGEntries.push_back(pIMGEntry);
	}

	std::sort(vecRadarIMGEntries.begin(), vecRadarIMGEntries.end(), [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2)
	{
		return String::toUint32(Path::removeFileExtension(pIMGEntry1->getEntryName()).substr(5)) < String::toUint32(Path::removeFileExtension(pIMGEntry2->getEntryName()).substr(5));
	});

	m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
	m_pVScrollBar->setItemCount(VERTICAL, vecRadarIMGEntries.size() * 50);

	for(IMGEntry *pIMGEntry : vecRadarIMGEntries)
	{
		TXDFormat txdFile(pIMGEntry->getEntryData(), false);
		if (!txdFile.unserialize())
		{
			continue;
		}
		vector<RWSection_TextureNative*> vecTextures = txdFile.getTextures();

		// todo
		//m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
		//m_pVScrollBar->setItemCount(VERTICAL, vecTextures.size() * 50);

		uint32 uiTextureIndex = 0;
		for (RWSection_TextureNative *pRWSection_TextureNative : vecTextures)
		{
			RadarEditorTabEntry *pTabEntry = new RadarEditorTabEntry;

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
			pTabEntry->m_uiMatrixIndex = String::toUint32(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5));

			addEntry(pTabEntry);
			uiTextureIndex++;
		}

		if (getEntryCount() > 0)
		{
			setActiveEntry(getEntryByIndex(0));
		}
	}
}

void						RadarEditorTab::prepareRenderData_WTD(void)
{
	bPremultipledAlphaApplied = FALSE;

	vector<IMGEntry*> vecRadarIMGEntries;
	vecRadarIMGEntries.resize(144);
	for (int i = 0; i < 144; i++) vecRadarIMGEntries[i] = nullptr;
	for (IMGEntry *pIMGEntry : m_pIMGFile->VectorPool::getEntries())
	{
		if (!(pIMGEntry->isTextureFile() && String::toUpperCase(pIMGEntry->getEntryName().substr(0, 5)) == "RADAR" && String::isPositiveInteger(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5))))
		{
			continue;
		}

		uint32 uiTokenIndex = String::toUint32(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5));
		vecRadarIMGEntries[uiTokenIndex] = pIMGEntry;
	}

	/*
	std::sort(vecRadarIMGEntries.begin(), vecRadarIMGEntries.end(), [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2)
	{
		return String::toUint32(Path::removeFileExtension(pIMGEntry1->getEntryName()).substr(5)) < String::toUint32(Path::removeFileExtension(pIMGEntry2->getEntryName()).substr(5));
	});
	*/

	m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
	m_pVScrollBar->setItemCount(VERTICAL, vecRadarIMGEntries.size() * 50);

	uint32 uiTabEntry = 0;
	//getEntries().resize(144);
	for(IMGEntry *pIMGEntry : vecRadarIMGEntries)
	{
		if (!pIMGEntry)
		{
			uiTabEntry++;
			continue;
		}

		WTDFormat wtdFile(pIMGEntry->getEntryData(), false);
		if (!wtdFile.unserialize())
		{
			uiTabEntry++;
			continue;
		}
		vector<WTDEntry*> vecWTDEntries = wtdFile.VectorPool::getEntries();

		// todo
		//m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, m_pWindow->getSize().y - 193);
		//m_pVScrollBar->setItemCount(VERTICAL, vecTextures.size() * 50);

		uint32 uiTextureIndex = 0;
		for (WTDEntry *pWTDEntry : vecWTDEntries)
		{
			RadarEditorTabEntry *pTabEntry = new RadarEditorTabEntry;

			if (pWTDEntry->getEntryCount() == 0)
			{
				// the texture does not have a mipmap
				pTabEntry->m_uiIndex = uiTextureIndex;
				pTabEntry->m_bTextureContainsNoMipmaps = true;
			}
			else
			{
				WTDMipmap *pMipmap = pWTDEntry->getEntryByIndex(0);
				string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
				const char *pBmpImageData = strBMPImageDataStr.c_str();

				HBITMAP hBitmap = CreateBitmap(pWTDEntry->getImageSize(true), pWTDEntry->getImageSize(false), 1, 32, pBmpImageData);

				pTabEntry->m_uiIndex = uiTextureIndex;
				pTabEntry->m_hBitmap = hBitmap;
				pTabEntry->m_uiWidth = pWTDEntry->getImageSize(true);
				pTabEntry->m_uiHeight = pWTDEntry->getImageSize(false);
				pTabEntry->m_strDiffuseName = pWTDEntry->getEntryName();
				pTabEntry->m_strAlphaName = "";
				pTabEntry->m_ucBPP = 32;
				pTabEntry->m_strTextureFormat = ImageManager::getD3DFormatText(pWTDEntry->getD3DFormat());
			}
			pTabEntry->m_uiMatrixIndex = String::toUint32(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5));

			addEntry(pTabEntry);
			uiTextureIndex++;
		}
		
		uiTabEntry++;
		if (getEntryCount() > 0)
		{
			setActiveEntry(getEntryByIndex(0));
		}
	}
}

// render editor
void						RadarEditorTab::render_Type1(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();


	/*
	//todo

	if (!bPremultipledAlphaApplied)
	{
		for (RadarEditorTabEntry *pTabEntry : getEntries())
		{
			HDC hdc = ((GDIPlus*)pGFX)->getGraphics()->GetHDC();
			PremultiplyBitmapAlpha(hdc, pTabEntry->m_hBitmap);
		}
		bPremultipledAlphaApplied = true;
	}
	*/



	Vec2u vecAreaSize(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);
	uint32 uiTileCount = getEntryCount();
	if (uiTileCount == 0)
	{
		return;
	}
	Vec2u vecDimensionTileCount;
	if (m_pIMGFile->getVersion() == IMG_3)
	{
		vecDimensionTileCount = Vec2u(12, 12);
	}
	else
	{
		uint32 uiDimensionTileCount = ceil(sqrt((float32)uiTileCount));
		vecDimensionTileCount = Vec2u(uiDimensionTileCount, uiDimensionTileCount);
	}
	Vec2u vecImageSize(vecAreaSize.x / vecDimensionTileCount.x, vecAreaSize.y / vecDimensionTileCount.y);

	for(RadarEditorTabEntry *pTabEntry : getEntries())
	{
		uint32
			y = pTabEntry->m_uiMatrixIndex / vecDimensionTileCount.y,
			x = pTabEntry->m_uiMatrixIndex % vecDimensionTileCount.x;

		Vec2i vecImagePosition;
		if (getIMGFile()->getVersion() == IMG_3)
		{
			vecImagePosition = Vec2i(139 + 139 + 250 + (x * vecImageSize.x), 192 + (y * vecImageSize.y));
		}
		else
		{
			vecImagePosition = Vec2i(139 + 139 + 250 + (x * vecImageSize.x), 192 + (y * vecImageSize.y));
		}

		pGFX->drawImage(vecImagePosition, pTabEntry->m_hBitmap, vecImageSize);
	}
}

// render editor
void						RadarEditorTab::renderEntryList(void)
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
	RadarEditorTabEntry
		*pActiveImageData = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = false;
	float32
		fVProgress = m_pVScrollBar->getProgress();

	for(uint32
			uiMaxEntryCount = Math::getMaxEntryCount(m_pWindow->getSize().y - 193, uiRowHeight),
			uiEntryIndex = Math::getEntryStartIndex(getEntryCount(), uiMaxEntryCount, fVProgress),
			uiEntryEndIndexExclusive = Math::getEntryEndIndexExclusive(getEntryCount(), uiEntryIndex, uiMaxEntryCount);
		uiEntryIndex < uiEntryEndIndexExclusive;
		uiEntryIndex++
	)
	{
		RadarEditorTabEntry *pImageData = getEntryByIndex(uiEntryIndex);
		if (!pImageData)
		{
			continue; // in case of render() between vector.resize() and vector.setEntryAtIndex()
		}

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
		if (pImageData == getActiveEntry())
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

	SelectObject(memDC, old);
	DeleteDC(memDC);
}