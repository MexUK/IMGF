#include "CarColsDATEditor.h"

#include "TextureEditor.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Editor/Tabs/TextureEditorTab.h"
#include "BXGX.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Style/Parts/EStyleStatus.h"
#include "Format/TXD/TXDManager.h"
#include "Format/WTD/WTDManager.h"
#include "Static/Path.h"
#include "IMGF.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "GUI/Editor/Base/EEditor.h"

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

CarColsDATEditor::CarColsDATEditor(void) :
	Editor(CAR_COLS_DAT_EDITOR)
{
}

// initialization
void						CarColsDATEditor::init(void)
{
	setEditorFileType(TEXTURE);
	setEditorFileFormats({ "TXD", "WTD" });
	setImportEditorFileFormats({ "BMP", "PNG", "GIF", "JPG", "JPEG", "ICO", "CUR", "DDS" });

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1010);

	Editor::init();

	int32 startx, starty, x, y, x2, y2;
	uint32 uiLogWidth = 335;

	startx = 139 + 139;
	starty = 162 + 30;

	// add top horizontal line
	x = startx;
	y = starty;

	x2 = x + (m_pMainWindow->getSize().x - uiLogWidth - startx);
	y2 = y;

	//m_pTopLine = addLine(x, y, x2, y2);

	/*
	// add vertical line for texture preview panel
	x = startx + 150;
	y = starty;

	x2 = x;
	y2 = m_pMainWindow->getSize().y;

	addLine(x, y, x2, y2);
	*/
}

// event binding
void						CarColsDATEditor::bindEvents(void)
{
	Editor::bindEvents();
}

void						CarColsDATEditor::unbindEvents(void)
{
	Editor::unbindEvents();
}

// add editor tab
CarColsDATEditorTab*		CarColsDATEditor::addEditorTab(string& strFilePath)
{
	if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "TXD")
	{
		TXDFormat txdFormat(strFilePath);
		if (!txdFormat.readMetaData())
		{
			return nullptr;
		}

		TextureEditorTab *pTextureEditorTab = Editor::_addEditorTab<TXDFormat, TextureEditorTab>(strFilePath, false);

		if (pTextureEditorTab)
		{
			//pTextureEditorTab->setTextureEditor(this);
			pTextureEditorTab->setIsTXDFile(true);
			pTextureEditorTab->setTXDFile((TXDFormat*)pTextureEditorTab->getFile());
			if (!pTextureEditorTab->init(false))
			{
				removeEditorTab(pTextureEditorTab);
				return nullptr;
			}
		}
		return pTextureEditorTab;
	}
	else if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "WTD")
	{
		WTDFormat wtdFormat(strFilePath);
		if (!wtdFormat.readMetaData())
		{
			return nullptr;
		}

		TextureEditorTab *pTextureEditorTab = Editor::_addEditorTab<WTDFormat, TextureEditorTab>(strFilePath, false);

		if (pTextureEditorTab)
		{
			//pTextureEditorTab->setTextureEditor(this);
			pTextureEditorTab->setIsTXDFile(false);
			pTextureEditorTab->setWTDFile((WTDFormat*)pTextureEditorTab->getFile());
			if (!pTextureEditorTab->init(false))
			{
				removeEditorTab(pTextureEditorTab);
				return nullptr;
			}
		}
		return pTextureEditorTab;
	}
}

CarColsDATEditorTab*		CarColsDATEditor::addBlankEditorTab(string& strFilePath)
{
	if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "TXD")
	{
		TextureEditorTab *pTextureEditorTab = Editor::_addEditorTab<TXDFormat, TextureEditorTab>(strFilePath, true);

		if (pTextureEditorTab)
		{
			//pTextureEditorTab->setTextureEditor(this);
			pTextureEditorTab->setIsTXDFile(true);
			pTextureEditorTab->setTXDFile((TXDFormat*)pTextureEditorTab->getFile());
			pTextureEditorTab->getTXDFile()->setRWVersion(RWManager::get()->getVersionManager()->getEntryByVersionId(RW_3_6_0_3));
			pTextureEditorTab->init(true);
		}
		return pTextureEditorTab;
	}
	else if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "WTD")
	{
		TextureEditorTab *pTextureEditorTab = Editor::_addEditorTab<WTDFormat, TextureEditorTab>(strFilePath, true);

		if (pTextureEditorTab)
		{
			//pTextureEditorTab->setTextureEditor(this);
			pTextureEditorTab->setIsTXDFile(false);
			pTextureEditorTab->setWTDFile((WTDFormat*)pTextureEditorTab->getFile());
			// todo pTextureEditorTab->getTXDFile()->setRWVersion(RWManager::get()->getVersionManager()->getEntryByVersionId(RW_3_6_0_3));
			pTextureEditorTab->init(true);
		}
		return pTextureEditorTab;
	}
}