#include "DumpWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
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

	addRadioButton(50, y, 20, 20, "Dump all entries in active tab", "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump selected entries in active tab", "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump all entries in all tabs", "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump entries by DAT file", "window2_radioButton");
	y += yGap;
	addRadioButton(50, y, 20, 20, "Dump entries by all IMGs for a game", "window2_radioButton");
	y += yGap2;

	// game folder path - for "by DAT file" and "all IMGs for a game"
	addText(50, y, 100, 20, "Game Folder");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox");
	addButton(360, y, 100, 20, "Choose..", "window2_button", 410);
	y += yGap;

	// DAT file path - for "by DAT file"
	addText(50, y, 100, 20, "DAT File");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox");
	addButton(360, y, 100, 20, "Choose..", "window2_button", 510);
	y += yGap;

	// output folder path
	addText(50, y, 100, 20, "Output Folder");
	y += yGap3;

	addTextBox(50, y, 300, 20, "", false, "window2_textBox");
	addButton(360, y, 100, 20, "Choose..", "window2_button", 610);
	y += yGap2;

	// entry types
	x = 50;
	y2 = y;
	addText(50, y, 100, 20, "Entry Types");
	y += yGap3;

	addCheckBox(x, y, 20, 20, "Model", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Collision", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Texture Set", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Animation", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Item Placement", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Texture Images", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Other", "window2_checkBox");
	y += yGap;

	// texture image output formats
	x = 250;
	y = y2;
	addText(x, y, 100, 20, "Texture Image Output Formats");
	y += yGap3;

	y3 = y;
	addCheckBox(x, y, 20, 20, "BMP", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "GIF", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "JPG", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "PNG", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "TGA", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "TIFF", "window2_checkBox");
	y += yGap;

	x = 320;
	y = y3;
	addCheckBox(x, y, 20, 20, "CUR", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "ICO", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "DDS", "window2_checkBox");
	y += yGap;

	// other options
	x = 450;
	y = y2;
	addText(x, y, 100, 20, "Other Options");
	y += yGap3;

	y2 = y;
	addCheckBox(x, y, 20, 20, "Dump texture images as folders", "window2_checkBox");
	y += yGap;
	addCheckBox(x, y, 20, 20, "Dump all texture mipmaps", "window2_checkBox");
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
		break;

	case 210:
		// cancel
		pWindow2->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;

	case 410:
		// choose game folder
		strFolderPath = Input::openFolder("Choose a game folder:");
		if (strFolderPath == "")
		{
			return;
		}
		pWindow1->m_dumpWindowResult.m_strGameFolderPath = strFolderPath;
		break;

	case 510:
		// choose DAT file
		vecDATFilePaths = Input::openFile("dat");
		if (vecDATFilePaths.size() == 0)
		{
			return;
		}
		//pWindow1->m_dumpWindowData.m_vecDATFilePaths = vecDATFilePaths;
		break;

	case 610:
		// choose output file
		strFolderPath = Input::openFolder("Choose the output folder:");
		if (strFolderPath == "")
		{
			return;
		}
		//pWindow1->m_dumpWindowData.m_strOutputFolderPath = strFolderPath;
		break;
	}
}