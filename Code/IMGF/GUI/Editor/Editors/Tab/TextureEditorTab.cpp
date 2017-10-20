#include "TextureEditorTab.h"
#include "nsbxgi.h"
#include "Format/TXD/TXDFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TabBar.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/Path.h"
#include "Format/TXD/TXDManager.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "GUI/Editor/Editors/Entry/TextureEditorTabEntry.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
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

	uint32 x = 139 + 139;

	uint32 uiLeftPanelWidth = x + 250;

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
		uiImageX = 0,// uiSingleDisplayTypeTopScrollbarXCurrentScroll,
		uiImageY = 0,
		uiHighestImageInRow = 0,
		uiCalculatedWidth,
		uiTextureIndex = 0;
	TextureEditorTabEntry
		*pActiveImageData = getActiveEntry();
	bool
		bTexturePreviewIsEnabled = true;
	for (TextureEditorTabEntry *pImageData : getEntries())
	{
		uint32 uiTop = uiImageY == 0 ? 0 : (uiImageY - 5);
		if (bTexturePreviewIsEnabled)
		{
			pImageData->m_rect.left = 0;
			pImageData->m_rect.top = (uiImageY - 5) + 1;
			pImageData->m_rect.right = uiLeftPanelWidth;
			pImageData->m_rect.bottom = uiImageY + 45 + 128 + 5;
		}
		else
		{
			pImageData->m_rect.left = 0;
			pImageData->m_rect.top = (uiImageY - 5) + 1;
			pImageData->m_rect.right = uiLeftPanelWidth;
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
		if (pImageData == getActiveEntry())
		{
			RECT rect2 = pImageData->m_rect;
			rect2.top -= yCurrentScroll;
			rect2.bottom -= yCurrentScroll;
			HBRUSH bkgBrush = CreateSolidBrush(RGB(255, 255, 0));
			FillRect(hdc, &rect2, bkgBrush);
			DeleteObject(bkgBrush);

			/*
			HDC tempHdc = CreateCompatibleDC(hdc);
			int width = pImageData->m_rect.right - pImageData->m_rect.left;
			int height = pImageData->m_rect.bottom - pImageData->m_rect.top;
			HBITMAP canvas = CreateCompatibleBitmap(hdc, width, height);
			// select new bitmap into context, don't forget to save old bitmap handle
			HBITMAP oldBmp = (HBITMAP) SelectObject(tempHdc, canvas);

			SetDCPenColor(tempHdc, RGB(255, 255, 0));
			SetDCBrushColor(tempHdc, RGB(255, 255, 0));
			Rectangle(tempHdc, pImageData->m_rect.left, pImageData->m_rect.top, pImageData->m_rect.right, pImageData->m_rect.bottom);
			BLENDFUNCTION blend = { AC_SRC_OVER, 0, 127, AC_SRC_ALPHA };
			AlphaBlend(hdc, pImageData->m_rect.left, pImageData->m_rect.top, pImageData->m_rect.right - pImageData->m_rect.left, pImageData->m_rect.bottom - pImageData->m_rect.top, tempHdc, 0, 0, pImageData->m_rect.right - pImageData->m_rect.left, pImageData->m_rect.bottom - pImageData->m_rect.top, blend);
			*/
		}

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
		DrawText(hdc, String::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX);

		// draw texture diffuse name
		HFONT hFont2 = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
		old = SelectObject(hdc, hFont2);

		uint32 uiXOffset1 = 50;

		rect.left = uiImageX + uiXOffset1;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		DrawText(hdc, String::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &rect, DT_NOPREFIX);
		uiImageY += 15;

		// draw texture alpha name
		if (pImageData->m_strAlphaName != "")
		{
			rect.left = uiImageX + uiXOffset1;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			DrawText(hdc, String::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &rect, DT_NOPREFIX);
			uiImageY += 15;
		}

		// draw texture size
		rect.left = uiImageX + uiXOffset1;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = String::toString(pImageData->m_uiWidth) + " x " + String::toString(pImageData->m_uiHeight);
		DrawText(hdc, String::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // size

		// draw texture BPP
		rect.left = uiImageX + uiXOffset1 + 85;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = String::toString(pImageData->m_ucBPP) + " BPP";
		DrawText(hdc, String::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // BPP

		// draw texture raster format
		rect.left = uiImageX + uiXOffset1 + 85 + 55;
		rect.top = uiImageY - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		strText = pImageData->m_strTextureFormat;
		DrawText(hdc, String::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // raster format

		uiImageY += 15;
		if (pImageData->m_strAlphaName == "")
		{
			uiImageY += 15;
		}
		SelectObject(hdc, old);
		DeleteObject(hFont);
		DeleteObject(hFont2);

		// draw texture image preview
		if (bTexturePreviewIsEnabled)
		{
			old = (HBITMAP)SelectObject(memDC, pImageData->m_hBitmap);

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

			//StretchBlt(hdc, uiImageX + 20, uiImageY - yCurrentScroll, uiDestWidth, uiDestHeight, memDC, 0, 0, pImageData->m_uiWidth, pImageData->m_uiHeight, SRCCOPY);
			uint32 uiAlpha = 255;
			BLENDFUNCTION bf = { AC_SRC_OVER, (uint8)0,  (uint8)uiAlpha, AC_SRC_ALPHA };
			AlphaBlend(hdc, uiImageX + 20, uiImageY - yCurrentScroll, uiDestWidth, uiDestHeight, memDC, 0, 0, pImageData->m_uiWidth, pImageData->m_uiHeight, bf);
			uiImageY += 128;
		}

		/*
		pImageData->m_rect.left = uiImageX + 20;
		pImageData->m_rect.top = uiImageY;
		pImageData->m_rect.right = uiImageX + 20 + 128;
		pImageData->m_rect.bottom = uiImageY + 128 + 20 + 20;
		*/

		uiImageY += 10;

		//uint32 uiItemHeight = 128 + 20 + 20 + uiImagePaddingBottom;


		// texture calculations 2
		//uint32 uiImageDisplayedHeight = 128;
		//uiImageY += pImageData->m_uiHeight + 20 + 20 + uiImagePaddingBottom;
		//uiImageY += uiItemHeight;

		/*
		if (pImageData->m_uiWidth > uiLongestImageInRow)
		{
		uiLongestImageInRow = pImageData->m_uiWidth;
		}
		*/

		// horizontal line below texture image
		//Pen      pen(Color(255, 0, 0, 0));
		pGFX->drawLine(Vec2i(0, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll), Vec2i(uiLeftPanelWidth, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll));

		uiTextureIndex++;
	}

	// zoom text
	HFONT hFont = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
	old = SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	RECT rect;
	rect.left = uiLeftPanelWidth + 5;
	rect.top = 10;
	rect.right = 8000;
	rect.bottom = 8000;
	string strText = "Zoom:";
	DrawText(hdc, String::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX);

	// vertical line next to textures list
	//Pen      pen(Color(255, 0, 0, 0));
	//graphics.DrawLine(&pen, 180, 0, 180, clientRect.bottom);

	// horizontal line above active image
	pGFX->drawLine(Vec2i(uiLeftPanelWidth, 50), Vec2i(clientRect.right, 50));

	if (pActiveImageData)
	{
		// active texture image
		old = (HBITMAP)SelectObject(memDC, pActiveImageData->m_hBitmap);
		//float32 fZoom = 4.0;
		//uint32 uiDestinationWidth = ((float32)pActiveImageData->m_uiWidth) * fZoom;
		//uint32 uiDestinationHeight = ((float32)pActiveImageData->m_uiHeight) * fZoom;
		uint32 uiDestinationWidth = (uint32)((float32)pActiveImageData->m_uiWidth * getZoomLevel());
		uint32 uiDestinationHeight = (uint32)((float32)pActiveImageData->m_uiHeight * getZoomLevel());

		//BitBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, SRCCOPY);
		//StretchBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, SRCCOPY);

		uint32 uiAlpha = 255;
		BLENDFUNCTION bf = { AC_SRC_OVER, (uint8)0, (uint8)uiAlpha, AC_SRC_ALPHA };
		AlphaBlend(hdc, uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, bf);
	}

	SelectObject(hdc, old);
	DeleteObject(hFont);
	
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