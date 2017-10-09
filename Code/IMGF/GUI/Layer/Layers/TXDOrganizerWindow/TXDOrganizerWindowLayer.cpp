#include "TXDOrganizerWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/TextBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "Image/ImageManager.h"
#include "Image/RasterDataFormatManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

TXDOrganizerWindowLayer::TXDOrganizerWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &TXDOrganizerWindowLayer::onPressButton);
}

TXDOrganizerWindowLayer::~TXDOrganizerWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &TXDOrganizerWindowLayer::onPressButton);
}

// initialization
void					TXDOrganizerWindowLayer::init(void)
{
	addButton(450, 360, 100, 20, "Organize", "window2_button", 200);
	addButton(570, 360, 100, 20, "Cancel", "window2_button", 210);

	int32 y, h;

	y = 50;
	h = 35;

	addText(30, 50, 150, 20, "Every N DFF Files:");
	addTextBox(190, 50, 100, 25, "", false, "", 300);
	y += h;

	addText(30, y, 150, 20, "TXD Name Prefix:");
	addTextBox(190, y, 500, 25, "", false, "", 400);
	y += h;

	addText(30, y, 250, 20, "Texture Import Folder: (Deep Search)");
	addTextBox(290, y, 400, 25, "", false, "", 500);
	addButton(700, y, 100, 25, "Choose..", "", 502);
	y += h;

	addCheckBox(30, y, 20, 20, "IDE Update Folder: (Deep Search)", -1, "", 601);
	addTextBox(290, y, 400, 25, "", false, "", 600);
	addButton(700, y, 100, 25, "Choose..", "", 602);
	y += h;

	addText(30, y, 150, 20, "Output Folder:");
	addTextBox(190, y, 500, 25, "", false, "", 700);
	addButton(700, y, 100, 25, "Choose..", "", 702);
	y += h;

	addText(30, y, 150, 20, "TXD Texture Format:");
	DropDown *pDropDown = addDropDown(190, y, 500, 25, "Choose..", "", 800);
	for (RasterDataFormat *pRasterDataFormat : ImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		DropDownItem *pItem = pDropDown->addItem(pRasterDataFormat->getText());
		pItem->setUserdata((uint32)pRasterDataFormat);
	}
	y += h;
}

// window events
void					TXDOrganizerWindowLayer::onPressButton(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
	WindowManager
		*pWindowManager = getIMGF()->getWindowManager();

	switch (pButton->getId())
	{
	case 200:
	{
		// organize
		pWindow1->m_bWindow2Cancelled = false;

		string
			strEveryNFiles = ((TextBox*)pWindow2->getItemById(300))->getText(),
			strTXDNamePrefix = ((TextBox*)pWindow2->getItemById(400))->getText(),
			strTextureImportFolder = ((TextBox*)pWindow2->getItemById(500))->getText(),
			strIDEUpdateFolder = ((TextBox*)pWindow2->getItemById(600))->getText(),
			strOutputFolder = ((TextBox*)pWindow2->getItemById(700))->getText();
		bool
			bUseIDEUpdateFolder = ((CheckBox*)pWindow2->getItemById(601))->isMarked();
		RasterDataFormat
			*pRasterDataFormat = (RasterDataFormat*)((DropDown*)pWindow2->getItemById(800))->getActiveItem()->getUserdata();

		if (!String::isPositiveInteger(strEveryNFiles))
		{
			Input::showMessage("Every N DFF Files must be a positive integer.", "Input Error", MB_OK);
			return;
		}
		else if (strTextureImportFolder == "")
		{
			Input::showMessage("Texture import folder cannot be blank.", "Input Error", MB_OK);
			return;
		}
		else if (bUseIDEUpdateFolder && strIDEUpdateFolder == "")
		{
			Input::showMessage("IDE update folder cannot be blank, as the update IDE check box has been checked.", "Input Error", MB_OK);
			return;
		}
		else if (strOutputFolder == "")
		{
			Input::showMessage("Output folder cannot be blank.", "Input Error", MB_OK);
			return;
		}

		pWindowManager->m_txdOrganizerWindowResult.m_uiEveryNDFFFiles = String::toUint32(strEveryNFiles);
		pWindowManager->m_txdOrganizerWindowResult.m_strTXDNamePrefix = strTXDNamePrefix;
		pWindowManager->m_txdOrganizerWindowResult.m_strTextureImportFolder = strTextureImportFolder;
		pWindowManager->m_txdOrganizerWindowResult.m_bUpdateIDE = bUseIDEUpdateFolder;
		pWindowManager->m_txdOrganizerWindowResult.m_strIDEUpdateFolder = strIDEUpdateFolder;
		pWindowManager->m_txdOrganizerWindowResult.m_strOutputFolder = strOutputFolder;
		pWindowManager->m_txdOrganizerWindowResult.m_pRasterDataFormat = pRasterDataFormat;

		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}

	case 201:
		// cancel
		pWindow1->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;

	case 502:
	{
		// Texture Import Folder
		string strTextureImportFolderPath = Input::openFolder("Choose a folder to import textures recursively from:");
		if (strTextureImportFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(500))->setText(strTextureImportFolderPath);
		pWindowManager->m_txdOrganizerWindowResult.m_strTextureImportFolder = strTextureImportFolderPath;
		break;
	}

	case 602:
	{
		// IDE Update Folder
		string strIDEUpdateFolderPath = Input::openFolder("Choose a folder to update IDE files recursively in:");
		if (strIDEUpdateFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(600))->setText(strIDEUpdateFolderPath);
		pWindowManager->m_txdOrganizerWindowResult.m_strIDEUpdateFolder = strIDEUpdateFolderPath;
		break;
	}

	case 702:
	{
		// Output Folder
		string strOutputFolderPath = Input::openFolder("Choose an output folder:");
		if (strOutputFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(700))->setText(strOutputFolderPath);
		pWindowManager->m_txdOrganizerWindowResult.m_strOutputFolder = strOutputFolderPath;
		break;
	}
	}
}