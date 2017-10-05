#include "DumpWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/RadioButton.h"
#include "Control/Controls/TextBox.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

DumpWindowLayer::DumpWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &DumpWindowLayer::onPressButton);
}

DumpWindowLayer::~DumpWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &DumpWindowLayer::onPressButton);
}

// initialization
void					DumpWindowLayer::init(void)
{
	MainWindow
		*pWindow1 = (MainWindow*)BXGX::get()->getEntryByIndex(0);

	pWindow1->m_dumpWindowResult = DumpWindowResult();

	addButton(450, 520, 100, 20, "Dump", "window2_button", 200);
	addButton(570, 520, 100, 20, "Cancel", "window2_button", 210);

	uint32 x, y, y3, y2, yGap, yGap2, yGap3;

	y = 50;
	yGap = 28;
	yGap2 = 35;
	yGap3 = 22;

	// dump type
	addText(50, y, 100, 20, "Dump Type");
	y += yGap3;
	uint32 uiTabGroupId = 0;

	RadioButton *pRadio1 = addRadioButton(50, y, 20, 20, "Dump all entries in active tab", uiTabGroupId, "window2_radioButton");
	pRadio1->setMarked(true);
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump selected entries in active tab", uiTabGroupId, "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump all entries in all tabs", uiTabGroupId, "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump entries by DAT file", uiTabGroupId, "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump entries by all IMGs for a game", uiTabGroupId, "window2_radioButton");
	y += yGap2;

	// DAT file path - for "by DAT file"
	addText(50, y, 100, 20, "DAT File(s)");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox", 300);
	addButton(360, y, 100, 20, "Choose..", "window2_button", 510);
	y += yGap;

	// game folder path - for "by DAT file" and "all IMGs for a game"
	addText(50, y, 100, 20, "Game Folder");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox", 301);
	addButton(360, y, 100, 20, "Choose..", "window2_button", 410);
	y += yGap;

	// output folder path
	addText(50, y, 100, 20, "Output Folder");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox", 302);
	addButton(360, y, 100, 20, "Choose..", "window2_button", 610);
	y += yGap2;

	// entry types
	x = 50;
	y2 = y;
	addText(50, y, 100, 20, "Entry Types");
	y += yGap3;
	uint32 uiCheckBoxGroupId = 0;
	
	addCheckBox(x, y, 20, 20, "Model", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Collision", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Texture Set", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Animation", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Item Placement", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Texture Images", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Other", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;

	// texture image output formats
	x = 250;
	y = y2;
	addText(x, y, 100, 20, "Texture Image Output Formats");
	y += yGap3;
	uiCheckBoxGroupId = 1;
	
	y3 = y;
	addCheckBox(x, y, 20, 20, "BMP", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "GIF", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "JPG", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "PNG", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "TGA", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "TIFF", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;

	x = 320;
	y = y3;
	addCheckBox(x, y, 20, 20, "CUR", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "ICO", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "DDS", uiCheckBoxGroupId, "window2_checkBox");
	y += yGap;

	// other options
	x = 450;
	y = y2;
	addText(x, y, 100, 20, "Other Options");
	y += yGap3;
	uiCheckBoxGroupId = 2;

	y2 = y;
	addCheckBox(x, y, 20, 20, "Dump texture images as folders", uiCheckBoxGroupId, "window2_checkBox", 400);
	y += yGap;
	addCheckBox(x, y, 20, 20, "Dump all texture mipmaps", uiCheckBoxGroupId, "window2_checkBox", 401);
}

// window events
void					DumpWindowLayer::onPressButton(Button *pButton)
{
	MainWindow
		*pWindow1 = (MainWindow*)BXGX::get()->getEntryByIndex(0);
	Window
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
	string
		strFolderPath;
	vector<string>
		vecDATFilePaths;

	switch (pButton->getId())
	{
	case 200:
		// Dump
		pWindow2->m_bWindow2Cancelled = false;

		if (pWindow1->m_dumpWindowResult.m_strOutputFolderPath == "")
		{
			Input::showMessage("Output folder mst be chosen.", "Input Error", MB_OK);
			return;
		}

		pWindow1->m_dumpWindowResult.m_bCancelled = false;
		pWindow1->m_dumpWindowResult.m_uiDumpType = pWindow2->getFirstEntry()->getSelectedRadioButton(0)->getIndex();
		pWindow1->m_dumpWindowResult.m_vecEntryTypes = pWindow2->getFirstEntry()->getSelectedCheckBoxesText(0);
		pWindow1->m_dumpWindowResult.m_vecTextureImageOutputFormats = pWindow2->getFirstEntry()->getSelectedCheckBoxesText(1);
		pWindow1->m_dumpWindowResult.m_bDumpAllTextureMipmaps = ((CheckBox*)pWindow2->getItemById(400))->isMarked();
		pWindow1->m_dumpWindowResult.m_bDumpTextureImagesAsFolders = ((CheckBox*)pWindow2->getItemById(401))->isMarked();
		break;

	case 210:
		// cancel
		pWindow1->m_dumpWindowResult.m_bCancelled = true;
		pWindow2->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;

	case 510:
		// choose DAT files
		vecDATFilePaths = Input::openFile("dat");
		if (vecDATFilePaths.size() == 0)
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(300))->setText(strFolderPath);
		pWindow1->m_dumpWindowResult.m_vecDATFilePaths = vecDATFilePaths;
		break;

	case 410:
		// choose game folder
		strFolderPath = Input::openFolder("Choose a game folder:");
		if (strFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(301))->setText(strFolderPath);
		pWindow1->m_dumpWindowResult.m_strGameFolderPath = strFolderPath;
		break;

	case 610:
		// choose output folder
		strFolderPath = Input::openFolder("Choose the output folder:");
		if (strFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(302))->setText(strFolderPath);
		pWindow1->m_dumpWindowResult.m_strOutputFolderPath = strFolderPath;
		break;
	}
}