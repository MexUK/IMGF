#include "TXDBuilderWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/RadioButton.h"
#include "Control/Controls/TextBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "Engine/RW/RWVersion.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

TXDBuilderWindowLayer::TXDBuilderWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &TXDBuilderWindowLayer::onPressButton);
}

TXDBuilderWindowLayer::~TXDBuilderWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &TXDBuilderWindowLayer::onPressButton);
}

// initialization
void					TXDBuilderWindowLayer::init(void)
{
	addButton(250, 650, 100, 20, "Build TXD(s)", "window2_button", 200);
	addButton(370, 650, 100, 20, "Cancel", "window2_button", 210);

	int32 x, y, x2;
	uint32 w, h, h2, h3;

	x = 30;
	x2 = x;
	y = m_pWindow->getTitleBarHeight() + 30;

	w = 200;
	h = 20;
	h2 = 25;
	h3 = 30;

	addText(x, y, w, h, "DFF Files");
	y += h3;

	w = 20;
	h = 20;
	addRadioButton(x, y, w, h, "All DFF entries in active tab", 0);
	y += h2;
	addRadioButton(x, y, w, h, "Selected DFF entries in active tab", 0);
	y += h2;
	addRadioButton(x, y, w, h, "All DFF entries in active all tabs", 0);
	y += h2;
	addRadioButton(x, y, w, h, "Folder containing DFF files", 0);
	y += h2;
	addRadioButton(x, y, w, h, "IDE file referencing DFF files", 0);
	y += h3 + 20;

	addText(x, y, 200, h, "DFFs Folder");
	y += 20;
	addTextBox(x, y, 400, h, "", false, "", 400);
	x += 405;
	addButton(x, y, 100, h, "Choose..", "", 410);
	x = x2;
	y += 30;

	addText(x, y, 200, h, "IDE File");
	y += 20;
	addTextBox(x, y, 400, h, "", false, "", 450);
	x += 405;
	addButton(x, y, 100, h, "Choose..", "", 460);
	x = x2;
	y += 50;

	addText(x, y, 200, h, "General Settings");
	y += 30;

	addText(x, y, 200, h, "Textures Folder (.BMPs)");
	y += 20;
	addTextBox(x, y, 400, h, "", false, "", 500);
	x2 = x;
	x += 405;
	addButton(x, y, 100, h, "Choose..", "", 510);
	y += 30;
	x = x2;

	addText(x, y, 200, h, "Output Folder");
	y += 20;
	addTextBox(x, y, 400, h, "", false, "", 600);
	x2 = x;
	x += 405;
	addButton(x, y, 100, h, "Choose..", "", 610);
	y += 50;
	x = x2;

	addText(x, y, 200, h, "Extra Settings");
	y += 30;

	addText(x, y, 200, h, "Texture count per TXD");
	y += 20;
	addTextBox(x, y, 100, h, "0", false, "", 700);
	y += 30;

	addText(x, y, 200, h, "RW Version");
	y += 20;
	DropDown *pDropDown = addDropDown(x, y, 400, h, "Choose..", "", 800);
	for (RWVersion *pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		DropDownItem *pItem = pDropDown->addItem(pRWVersion->getVersionTextWithGames());
		pItem->setUserdata((uint32)pRWVersion);
	}
}

// window events
void					TXDBuilderWindowLayer::onPressButton(Button *pButton)
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
		// Build TXD(s)
		pWindow1->m_bWindow2Cancelled = false;

		pWindowManager->m_txdBuilderWindowResult.m_uiDFFFilesType = getSelectedRadioButton(0)->getIndex();
		pWindowManager->m_txdBuilderWindowResult.m_strDFFsFolderPath = ((TextBox*)getItemById(400))->getText();
		pWindowManager->m_txdBuilderWindowResult.m_strIDEFilePath = ((TextBox*)getItemById(450))->getText();
		pWindowManager->m_txdBuilderWindowResult.m_strTexturesBMPsFolderPath = ((TextBox*)getItemById(500))->getText();
		pWindowManager->m_txdBuilderWindowResult.m_strOutputFolderPath = ((TextBox*)getItemById(600))->getText();

		string
			strTextureCountPerTXD = ((TextBox*)getItemById(700))->getText();
		DropDownItem
			*pActiveRWVersionItem = ((DropDown*)getItemById(800))->getActiveItem();

		if (strTextureCountPerTXD == "")
		{
			Input::showMessage("Texture count per TXD must be a positive integer.", "Input Error", MB_OK);
			return;
		}
		else if (!pActiveRWVersionItem)
		{
			Input::showMessage("RW Version must be chosen.", "Input Error", MB_OK);
			return;
		}

		pWindowManager->m_txdBuilderWindowResult.m_uiTextureCountPerTXD = String::toUint32(strTextureCountPerTXD);
		pWindowManager->m_txdBuilderWindowResult.m_uiRWVersion = ((RWVersion*)pActiveRWVersionItem->getUserdata())->getVersionId();

		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}

	case 210:
		// Cancel
		pWindow1->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;

	case 410:
	{
		// DFFs Folder
		string strDFFsFolder = Input::openFolder("Choose a folder containing DFF files:");
		if (strDFFsFolder == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(400))->setText(strDFFsFolder);
		break;
	}

	case 460:
	{
		// IDE File
		vector<string> strIDEilePath = Input::openFile("", "IDE", false);
		if (strIDEilePath.size() == 0)
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(450))->setText(strIDEilePath[0]);
		break;
	}

	case 510:
	{
		// Texture BMPs Folder
		string strTextureBMPsFolder = Input::openFolder("Choose a folder containing BMP files:");
		if (strTextureBMPsFolder == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(500))->setText(strTextureBMPsFolder);
		break;
	}

	case 610:
	{
		// Texture BMPs Folder
		string strOutputFolderPath = Input::openFolder("Choose an output folder for the TXD files:");
		if (strOutputFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(600))->setText(strOutputFolderPath);
		break;
	}
	}
}