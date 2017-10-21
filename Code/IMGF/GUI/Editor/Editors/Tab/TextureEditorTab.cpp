#include "TextureEditorTab.h"
#include "nsbxgi.h"
#include "Format/TXD/TXDFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/Text.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/Path.h"
#include "Format/TXD/TXDManager.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "GUI/Editor/Editors/Entry/TextureEditorTabEntry.h"
#include "GraphicsLibrary/Base/ImageObject.h"
#include "Style/Parts/EStyleStatus.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

TextureEditorTab::TextureEditorTab(void) :
	m_pTXDFile(nullptr),
	m_pActiveTabEntry(nullptr)
{
}

// controls
void					TextureEditorTab::addControls(void)
{
}

void					TextureEditorTab::initControls(void)
{
}

// file unserialization
bool					TextureEditorTab::unserializeFile(void)
{
	TXDFormat *txd = new TXDFormat;

	/*
	progress bar: 3 stages

	[IMG versions 1, 2, and fastman92]
	- parsing header
	- parsing RW versions
	- adding entries to grid

	[IMG versions 3 (encrypted and unencrypted)]
	- parsing header
	- parsing entry names
	- adding entries to grid
	*/

	if (!txd->openFile())
	{
		return false;
	}
	if (!txd->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(txd->getErrorCode()) + "\r\n\r\n" + txd->getFilePath(), "Can't Open TXD File");
		delete txd;
		return false;
	}

	uint32
		uiProgressBarMaxMultiplier = 3,
		uiProgressBarMax = txd->m_uiEntryCount * uiProgressBarMaxMultiplier;
	getProgressBar()->setMax(uiProgressBarMax);

	if (!txd->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(txd->getErrorCode()) + "\r\n\r\n" + txd->getFilePath(), "Can't Open TXD File");
		delete txd;
		return false;
	}

	setTXDFile(txd);
	return true;
}

void					TextureEditorTab::onFileLoaded(void)
{
	string strFilePath = getFile()->getFilePath();

	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);

	// prepare render data
	prepareRenderData_TXD();

	// display TXD info
	setFileInfoText();

	// render
	m_pWindow->render();

	/*
	// store render items
	getRenderItems().addEntry(m_pEntryGrid);
	getRenderItems().addEntry(m_pEntryTypeFilter);
	getRenderItems().addEntry(m_pEntryVersionFilter);

	addGridEntries();

	m_pEntryGrid->setActiveItem();

	loadFilter_Type();
	loadFilter_Version();

	setFileInfoText();
	*/
}

// update tab text
void						TextureEditorTab::updateTabText(void)
{
	string strTabText = Path::getFileName(m_pFile->getFilePath());
	m_pTab->setText(strTabText);
}

// prepare render data
bool						TextureEditorTab::prepareRenderData_TXD(void)
{
	vector<RWSection_TextureNative*> vecTextures = m_pTXDFile->getTextures();
	uint32 uiTextureIndex = 0;
	for (RWSection_TextureNative *pRWSection_TextureNative : vecTextures)
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

		addEntry(pTabEntry);
		uiTextureIndex++;
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getEntryByIndex(0));
	}

	//setRenderDataIsReady(true);
	return true;
}

bool						TextureEditorTab::prepareRenderData_WTD(void)
{
	/*
	WTDFormat *pWTDFile = WTDManager::get()->unserializeMemory(getIMGEntry()->getEntryData());
	if (pWTDFile->doesHaveError())
	{
		setEntityDataIsCorrupt(true);
		return false;
	}

	uint32 uiTextureIndex = 0;
	vector<WTDEntry*> vecWTDEntries = pWTDFile->getEntries();

	for (auto pWTDEntry : vecWTDEntries)
	{
		TextureViewerTextureData *pTextureData = new TextureViewerTextureData;

		if (pWTDEntry->getEntryCount() == 0)
		{
			// the texture does not have a mipmap
			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_bTextureContainsNoMipmaps = true;
		}
		else
		{
			WTDMipmap *pMipmap = pWTDEntry->getEntryByIndex(0);
			string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
			const char *pBmpImageData = strBMPImageDataStr.c_str();

			HBITMAP hBitmap = CreateBitmap(pWTDEntry->getImageSize(true), pWTDEntry->getImageSize(false), 1, 32, pBmpImageData);

			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_hBitmap = hBitmap;
			pTextureData->m_uiWidth = pWTDEntry->getImageSize(true);
			pTextureData->m_uiHeight = pWTDEntry->getImageSize(false);
			pTextureData->m_strDiffuseName = pWTDEntry->getEntryName();
			pTextureData->m_strAlphaName = "";
			pTextureData->m_ucBPP = 32;
			pTextureData->m_strTextureFormat = ImageManager::getD3DFormatText(pWTDEntry->getD3DFormat());
		}

		addEntry(pTextureData);
		uiTextureIndex++;
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getEntryByIndex(0));
	}

	pWTDFile->unload();
	delete pWTDFile;

	setRenderDataIsReady(true);
	*/
	return true;
}

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

	//hdc = BeginPaint(hwnd, &ps);
	
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
		uiImageX = x,// uiSingleDisplayTypeTopScrollbarXCurrentScroll,
		uiImageY = y,
		uiHighestImageInRow = 0,
		uiCalculatedWidth,
		uiTextureIndex = 0;
	TextureEditorTabEntry
		*pActiveImageData = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = false;
	for (TextureEditorTabEntry *pImageData : getEntries())
	{
		uint32 uiTop = uiImageY == 0 ? 0 : (uiImageY - 5);
		if (bTexturePreviewIsEnabled)
		{
			pImageData->m_rect.left = vecMainPanelPosition.x;
			pImageData->m_rect.top = uiImageY;
			pImageData->m_rect.right = vecMainPanelPosition.x + 250;
			pImageData->m_rect.bottom = uiImageY + 45 + 128 + 5;
		}
		else
		{
			pImageData->m_rect.left = vecMainPanelPosition.x;
			pImageData->m_rect.top = uiImageY;
			pImageData->m_rect.right = vecMainPanelPosition.x + 250;
			pImageData->m_rect.bottom = uiImageY + 45 + 5;
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

		rect.left = uiImageX + 5;
		rect.top = uiImageY + 10 - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		string strText = String::toString(uiTextureIndex + 1);
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture diffuse name
		uint32 uiXOffset1 = 50;

		rect.left = uiImageX + uiXOffset1;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), pImageData->m_strDiffuseName);
		uiImageY += 15;

		// draw texture alpha name
		if (pImageData->m_strAlphaName != "")
		{
			rect.left = uiImageX + uiXOffset1;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), pImageData->m_strAlphaName);
			uiImageY += 15;
		}

		// draw texture size
		rect.left = uiImageX + uiXOffset1;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = String::toString(pImageData->m_uiWidth) + " x " + String::toString(pImageData->m_uiHeight);
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture BPP
		rect.left = uiImageX + uiXOffset1 + 85;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = String::toString(pImageData->m_ucBPP) + " BPP";
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		// draw texture raster format
		rect.left = uiImageX + uiXOffset1 + 85 + 55;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = pImageData->m_strTextureFormat;
		pGFX->drawText(Vec2i(rect.left, rect.top), Vec2u(250, 20), strText);

		uiImageY += 15;
		if (pImageData->m_strAlphaName == "")
		{
			uiImageY += 15;
		}

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
			
			pGFX->drawImage(Vec2i(uiImageX + 20, uiImageY - yCurrentScroll), pImageData->m_hBitmap, Vec2u(pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight));
			uiImageY += 128;
		}

		uiImageY += 10;

		// horizontal line below texture image
		pGFX->drawLine(Vec2i(vecMainPanelPosition.x, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll), Vec2i(vecMainPanelPosition.x + 250, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll));

		uiTextureIndex++;
	}

	// zoom text
	RECT rect;
	rect.left = vecMainPanelPosition.x + 250 + 100;
	rect.top = vecMainPanelPosition.y - 50;
	rect.right = 8000;
	rect.bottom = 8000;
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
		uint32 uiMaxXPosition = uiImageX + uiCalculatedWidth + uiImagePaddingRight;
		if (clientRect.bottom > (int32)uiMaxXPosition)
		{
			uiMaxXPosition = clientRect.bottom;
		}
		uiMaxXPosition += 100;
		//getIMGF()->getEntryViewerManager()->getTextureViewer()->setSingleDisplayTypeTopScrollbarMaxXPosition(uiMaxXPosition);
	}

	SelectObject(memDC, old);
	DeleteDC(memDC);
	
	//EndPaint(hwnd, &ps);
}

// file info text
void					TextureEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getFile()->getFilePath());
	m_pText_FileVersion->setText(getTXDFile()->getRWVersion()->getVersionText(), false);
	m_pText_FileGame->setText(getTXDFile()->getRWVersion()->getGamesAsString());

	updateEntryCountText();
}

void					TextureEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getTXDFile()->getTextures().size(),
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