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

using namespace std;
using namespace bxcf;
using namespace bxgx;
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
	m_pIMGFile(nullptr)
{
}

// controls
void						RadarEditorTab::addControls(void)
{
}

// events
void						RadarEditorTab::bindEvents(void)
{
	bindEvent(UNSERIALIZE_IMG_ENTRY, &RadarEditorTab::onUnserializeEntry);

	EditorTab::bindEvents();
}

void						RadarEditorTab::unbindEvents(void)
{
	unbindEvent(UNSERIALIZE_IMG_ENTRY, &RadarEditorTab::onUnserializeEntry);

	EditorTab::unbindEvents();
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
	m_pText_FileGame->setText(IMGManager::getVersionGames(getIMGFile()->getVersion()));

	updateEntryCountText();
}

void						RadarEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = 0;
	
	for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries())
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
	for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries())
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

			addEntry(pTabEntry);
			uiTextureIndex++;
		}

		if (getEntryCount() > 0)
		{
			// todo setActiveEntry(getEntryByIndex(0));
		}
	}
}

void						RadarEditorTab::prepareRenderData_WTD(void)
{
	bPremultipledAlphaApplied = FALSE;

	vector<IMGEntry*> vecRadarIMGEntries;
	for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries())
	{
		if (!(pIMGEntry->isTextureFile() && String::toUpperCase(pIMGEntry->getEntryName().substr(0, 5)) == "RADAR" && String::isPositiveInteger(Path::removeFileExtension(pIMGEntry->getEntryName()).substr(5))))
		{
			continue;
		}
		vecRadarIMGEntries.push_back(pIMGEntry);
	}

	///*
	std::sort(vecRadarIMGEntries.begin(), vecRadarIMGEntries.end(), [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2)
	{
		return String::toUint32(Path::removeFileExtension(pIMGEntry1->getEntryName()).substr(5)) < String::toUint32(Path::removeFileExtension(pIMGEntry2->getEntryName()).substr(5));
	});
	//*/

	for(IMGEntry *pIMGEntry : vecRadarIMGEntries)
	{
		WTDFormat wtdFile(pIMGEntry->getEntryData(), false);
		if (!wtdFile.unserialize())
		{
			continue;
		}
		vector<WTDEntry*> vecWTDEntries = wtdFile.getEntries();

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

			addEntry(pTabEntry);
			uiTextureIndex++;
		}

		if (getEntryCount() > 0)
		{
			// todo setActiveEntry(getEntryByIndex(0));
		}
	}
}

// render editor
void						RadarEditorTab::render_Type1(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();


	/*
	todo

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



	Vec2u vecAreaSize(512, 512);
	uint32 uiTileCount = getEntryCount();
	if (uiTileCount == 0)
	{
		return;
	}
	Vec2u vecDimensionTileCount;
	if (m_pIMGFile->getVersion() == IMG_3)
	{
		vecDimensionTileCount = Vec2u(8, 8);
	}
	else
	{
		uint32 uiDimensionTileCount = ceil(sqrt((float32)uiTileCount));
		vecDimensionTileCount = Vec2u(uiDimensionTileCount, uiDimensionTileCount);
	}
	Vec2u vecImageSize(vecAreaSize.x / vecDimensionTileCount.x, vecAreaSize.y / vecDimensionTileCount.y);
	uint32 uiTabEntry = 0;

	for (uint32 i = 0; i < vecDimensionTileCount.y; i++)
	{
		for (uint32 i2 = 0; i2 < vecDimensionTileCount.x; i2++)
		{
			Vec2i vecImagePosition;
			if (getIMGFile()->getVersion() == IMG_3)
			{
				vecImagePosition = Vec2i(139 + 139 + 150 + (i2 * vecImageSize.x), 192 + (i * vecImageSize.y));
			}
			else
			{
				vecImagePosition = Vec2i(139 + 139 + 150 + (i2 * vecImageSize.x), 192 + (i * vecImageSize.y));
			}

			uint32 uiTabEntry2 = uiTabEntry;
			//if (uiTabEntry2 < 4)
			//{
				
			//}
			if (uiTabEntry < 3)
			{
				uiTabEntry2 = 62 - uiTabEntry;
			}
			else
				uiTabEntry2 -= 3;
			RadarEditorTabEntry *pTabEntry = getEntryByIndex(uiTabEntry2);
			if (!pTabEntry)
			{
				continue;
			}

			pGFX->drawImage(vecImagePosition, pTabEntry->m_hBitmap, vecImageSize);

			uiTabEntry++;
		}
	}
}