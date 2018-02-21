#include "CarColsDATEditorTab.h"
#include "nsbxgi.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/WTD/WTDFormat.h"
#include "Format/WTD/WTDManager.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/CheckBox.h"
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
#include "GraphicsLibrary/Base/ImageObject.h"
#include "Style/Parts/EStyleStatus.h"
#include "Stream/DataReader.h"
#include "../BXGI/Event/EEvent.h"
#include "Event/EInputEvent.h"
#include "Image/ImageManager.h"
#include "GUI/Editor/Base/Editor.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "GUI/Window/windows/MainWindow/MainWindow.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

/*

CarColsDATEditorTab::CarColsDATEditorTab(void)
{
}

CarColsDATEditorTab::~CarColsDATEditorTab(void)
{
}

// events
void					CarColsDATEditorTab::bindEvents(void)
{
	bindEvent(RENDER, &CarColsDATEditorTab::render);
	bindEvent(UNSERIALIZE_RW_SECTION, &CarColsDATEditorTab::onUnserializeRWSection);
	bindEvent(SELECT_DROP_DOWN_ITEM, &CarColsDATEditorTab::onSelectDropDownItem);
	bindEvent(LEFT_MOUSE_DOWN, &CarColsDATEditorTab::onLeftMouseDown);
	bindEvent(LEFT_MOUSE_UP, &CarColsDATEditorTab::onLeftMouseUp);
	bindEvent(MOVE_MOUSE, &CarColsDATEditorTab::onMouseMove);
	bindEvent(KEY_DOWN, &CarColsDATEditorTab::onKeyDown2);
	bindEvent(MOVE_MOUSE_WHEEL, &CarColsDATEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void					CarColsDATEditorTab::unbindEvents(void)
{
	unbindEvent(RENDER, &CarColsDATEditorTab::render);
	unbindEvent(UNSERIALIZE_RW_SECTION, &CarColsDATEditorTab::onUnserializeRWSection);
	unbindEvent(SELECT_DROP_DOWN_ITEM, &CarColsDATEditorTab::onSelectDropDownItem);
	unbindEvent(LEFT_MOUSE_DOWN, &CarColsDATEditorTab::onLeftMouseDown);
	unbindEvent(LEFT_MOUSE_UP, &CarColsDATEditorTab::onLeftMouseUp);
	unbindEvent(MOVE_MOUSE, &CarColsDATEditorTab::onMouseMove);
	unbindEvent(KEY_DOWN, &CarColsDATEditorTab::onKeyDown2);
	unbindEvent(MOVE_MOUSE_WHEEL, &CarColsDATEditorTab::onMouseWheelMove2);

	EditorTab::unbindEvents();
}

// controls
void					CarColsDATEditorTab::storeControls(void)
{
}

// layer
void					CarColsDATEditorTab::initLayer(void)
{
	setLayer(m_pEditor->getMainWindow()->getLayerById(103));
}

// add entry
void					CarColsDATEditorTab::addEntryAfter(FormatEntry *pEntry)
{
	RWSection_TextureNative *pTexture = (RWSection_TextureNative*)pEntry;
	prepareTexture(pTexture);

	calculateDisplayedEntryCount();
	updateEntryCountText();
}

// editor input
bool						CarColsDATEditorTab::onLeftMouseDown(Vec2i vecCursorPosition)
{
}

void						CarColsDATEditorTab::onLeftMouseUp(Vec2i vecCursorPosition)
{
}

void						CarColsDATEditorTab::onMouseMove(Vec2i vecCursorPosition)
{
}

void						CarColsDATEditorTab::onKeyDown2(uint16 uiKey)
{
}

void					CarColsDATEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
}

// file unserialization
bool					CarColsDATEditorTab::unserializeFile(void)
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

	setDATCarColsFile((DATCarColsFormat*)m_pFile);

	return true;
}

void					CarColsDATEditorTab::onFileLoaded(void)
{
	string strFilePath = getFile()->getFilePath();

	// update tab text
	updateTabText();

	// prepare render data
	prepareRenderData();
	calculateDisplayedEntryCount();

	// render
	getLayer()->getWindow()->render();

	// display TXD info
	setFileInfoText();
}

void					CarColsDATEditorTab::calculateDisplayedEntryCount(void)
{
	uint32 uiMatchCount = 0;
	for (CarColsDATEditorTabEntry *pTabEntry : getEntries())
	{
		if (doesTabEntryMatchFilter(pTabEntry))
		{
			uiMatchCount++;
		}
	}
	m_uiDisplayedEntryCount = uiMatchCount;
}

// prepare render data
bool						CarColsDATEditorTab::prepareRenderData(void)
{
	m_bIsTXDFile = true;

	vector<RWSection_TextureNative*> vecTextures = m_pTXDFile->getTextures();

	if (m_pVScrollBar)
	{
		m_pVScrollBar->setMaxDisplayedItemCount(VERTICAL, getLayer()->getWindow()->getSize().y - 160);
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

void						CarColsDATEditorTab::prepareTexture(RWSection_TextureNative *pRWSection_TextureNative)
{
	CarColsDATEditorTabEntry *pTabEntry = new CarColsDATEditorTabEntry;

	if (pRWSection_TextureNative->getMipMaps().getEntryCount() == 0)
	{
		// the texture does not have a mipmap
		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_bTextureContainsNoMipmaps = true;
	}
	else
	{
		RWEntry_TextureNative_MipMap *pMipmap = pRWSection_TextureNative->getMipMaps().getEntryByIndex(0);

		string strRasterDataBGRA32 = pMipmap->getRasterDataBGRA32();
		const char *pRasterDataBGRA32 = strRasterDataBGRA32.c_str();
		HBITMAP hDiffuseBitmap = CreateBitmap(pMipmap->getImageSize().x, pMipmap->getImageSize().y, 1, 32, pRasterDataBGRA32);

		string strRasterDataBGR24 = ImageManager::convertBGRA32ToAlphaBGRA32(strRasterDataBGRA32);
		const char *pRasterDataBGR24 = strRasterDataBGR24.c_str();
		HBITMAP hAlphaBitmap = CreateBitmap(pMipmap->getImageSize().x, pMipmap->getImageSize().y, 1, 32, pRasterDataBGR24);

		pTabEntry->m_uiIndex = getEntryCount();
		pTabEntry->m_hDiffuseBitmap = hDiffuseBitmap;
		pTabEntry->m_hAlphaBitmap = hAlphaBitmap;
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

// filter
bool						CarColsDATEditorTab::doesTabEntryMatchFilter(CarColsDATEditorTabEntry *pTabEntry)
{
	string strSearchTextUpper = String::toUpperCase(m_pSearchBox->getText());
	return strSearchTextUpper == "" || String::isIn(String::toUpperCase(pTabEntry->m_strDiffuseName), strSearchTextUpper, false);
}

// render editor
void						CarColsDATEditorTab::render(void)
{
	renderDisplayType_Single();
}

void						CarColsDATEditorTab::renderDisplayType_Single(void)
{
}

// file info text
void					CarColsDATEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));

	string strVersionText = RWManager::get()->getVersionManager()->getVersionText(getTXDFile()->getRawVersion());
	string strVersionGames = getTXDFile()->getRWVersion() ? getTXDFile()->getRWVersion()->getGamesAsString() : "Unknown";

	m_pText_FileVersion->setText(strVersionText);
	m_pText_FileGame->setText(strVersionGames);

	updateEntryCountText();
}

void					CarColsDATEditorTab::updateEntryCountText(void)
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

vector<FormatEntry*>	CarColsDATEditorTab::getSelectedEntries(void)
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

uint32					CarColsDATEditorTab::getSelectedEntryCount(void)
{
	uint32 uiIndex = 0;
	uint32 uiSelectedItemCount = 0;
	for (RWSection_TextureNative *pTextureNative : getTXDFile()->getTextures())
	{
		if (m_vecEntries[uiIndex]->m_bIsActive)
		{
			uiSelectedItemCount++;
		}
		uiIndex++;
	}
	return uiSelectedItemCount;
}

uint32					CarColsDATEditorTab::getTotalEntryCount(void)
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

void					CarColsDATEditorTab::onEntryChange(FormatEntry *pEntry)
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
	CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiIndex);

	pTabEntry->m_strDiffuseName = pEntry->getEntryName();
	if (pTabEntry->m_strAlphaName != "")
	{
		pTabEntry->m_strAlphaName = pEntry->getEntryName() + "a";
	}
}

void					CarColsDATEditorTab::onSortEntries(vector<FormatEntry*>& vecEntries)
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

void					CarColsDATEditorTab::merge(string& strFilePath)
{
	getContainerFile()->merge(strFilePath);
}




void					CarColsDATEditorTab::recreateEntryList(void)
{
	VectorPool::removeAllEntries();
	if (m_bIsTXDFile)
	{
		prepareRenderData_TXD();
	}
	else
	{
		prepareRenderData_WTD();
	}
	calculateDisplayedEntryCount();
	updateEntryCountText();
	getLayer()->getWindow()->render();
}

void					CarColsDATEditorTab::removeAllEntries(void)
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

void					CarColsDATEditorTab::removeEntries(vector<FormatEntry*>& vecEntries)
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

void					CarColsDATEditorTab::clearActiveEntries(void)
{
	for (CarColsDATEditorTabEntry *pTabEntry : getEntries())
	{
		pTabEntry->m_bIsActive = false;
	}
	setActiveEntry(nullptr);
}

void					CarColsDATEditorTab::setEntriesSelected(vector<FormatEntry*>& vecEntries, bool bIsSelected)
{
	clearActiveEntries();
	for (FormatEntry *pFormatEntry : vecEntries)
	{
		if (m_bIsTXDFile)
		{
			RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pFormatEntry;
			uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
			CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
			pTabEntry->m_bIsActive = bIsSelected;
		}
		else
		{
			uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pFormatEntry);
			CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
			pTabEntry->m_bIsActive = bIsSelected;
		}
	}
	getLayer()->getWindow()->render();
}

void					CarColsDATEditorTab::setEntrySelected(FormatEntry *pEntry, bool bIsSelected)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pEntry;
		uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
		CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		pTabEntry->m_bIsActive = bIsSelected;
	}
	else
	{
		uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pEntry);
		CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		pTabEntry->m_bIsActive = bIsSelected;
	}
}

bool					CarColsDATEditorTab::isEntrySelected(FormatEntry *pEntry)
{
	if (m_bIsTXDFile)
	{
		RWSection_TextureNative *pTextureNative = (RWSection_TextureNative *)pEntry;
		uint32 uiTextureIndex = StdVector::findKey(getTXDFile()->getSectionsByType(RW_SECTION_TEXTURE_NATIVE), (RWSection*)pTextureNative);
		CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		return pTabEntry->m_bIsActive;
	}
	else
	{
		uint32 uiTextureIndex = getWTDFile()->getIndexByEntry((WTDEntry*)pEntry);
		CarColsDATEditorTabEntry *pTabEntry = getEntryByIndex(uiTextureIndex);
		return pTabEntry->m_bIsActive;
	}
}

*/