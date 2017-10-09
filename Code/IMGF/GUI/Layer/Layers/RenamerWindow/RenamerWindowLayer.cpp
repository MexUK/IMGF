#include "RenamerWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/RadioButton.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

RenamerWindowLayer::RenamerWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &RenamerWindowLayer::onPressButton);
}

RenamerWindowLayer::~RenamerWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &RenamerWindowLayer::onPressButton);
}

// initialization
void					RenamerWindowLayer::init(void)
{
	addButton(450, 670, 100, 20, "Rename", "window2_button", 200);
	addButton(570, 670, 100, 20, "Cancel", "window2_button", 210);

	int32 x, y, x2, y2;
	uint32 w, h, w2, h2, h3, uiCheckableItemWidth, uiCheckableItemHeight, uiTextBoxWidth;

	x = 30;
	y = m_pWindow->getTitleBarHeight() + 30;
	w = 200;
	h = 25;
	h3 = h + 3;
	h2 = h3 + 10;
	uiCheckableItemWidth = 20;
	uiCheckableItemHeight = 20;
	uiTextBoxWidth = 400;

	addText(x, y, w, h, "Entries:");
	y += h2;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "All entries in active tab", 0);
	y += h;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Selected entries in active tab", 0);
	y += h2;



	addText(x, y, w, h, "Matching Entries: (Deep Folder Search)");
	y += h2;

	x2 = x;
	addCheckBox(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "IDE", -1, "", 310);
	x += 80;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 300);
	x += 410;
	addButton(x, y, 100, h, "Choose..");
	y += h3;
	x = x2;

	addCheckBox(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "IPL", -1, "", 410);
	x += 80;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 400);
	x += 410;
	addButton(x, y, 100, h, "Choose..");
	y += h3;
	x = x2;

	addCheckBox(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "COL", -1, "", 510);
	x += 80;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 500);
	x += 410;
	addButton(x, y, 100, h, "Choose..");
	y += h2;
	x = x2;



	y2 = y;
	uiTextBoxWidth = 120;
	addText(x, y, w, h, "Character Adding / Replacing:");
	y += h2;

	addText(x, y, 100, h, "Front");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 600);
	x = x2;
	y += h3;

	addText(x, y, w, h, "End");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 640);
	x = x2;
	y += h3;

	addText(x, y, w, h, "At Position");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", 680);
	x += uiTextBoxWidth + 10;
	addText(x, y, w, h, "Position");
	x += 60;
	addTextBox(x, y, 50, h, "", false, "", 690);
	x = x2;
	y += h2;



	addText(x, y, 400, h, "Character Removing: (Enter number of characters)");
	y += h2;

	addText(x, y, w, h, "Front");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 700);
	x = x2;
	y += h3;

	addText(x, y, w, h, "End");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 740);
	x = x2;
	y += h3;

	addText(x, y, w, h, "At Position");
	x += 110;
	addTextBox(x, y, uiTextBoxWidth, h, "", false, "", 780);
	x += uiTextBoxWidth + 10;
	addText(x, y, w, h, "Position");
	x += 60;
	addTextBox(x, y, 50, h, "", false, "", 790);
	x = x2;
	y += h3;



	addText(x, y, w, h, "Character Case");
	y += h2;

	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Leave untouched", 1);
	y += h3;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "UPPER CASE", 1);
	y += h3;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "lower case", 1);
	y += h3;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Title Case", 1);
	y += h2;



	x += 400;
	x2 = x;
	y = y2;

	addText(x, y, w, h, "Character Replacement Options:");
	y += h2;

	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Don't replace characters", 2);
	y += h3;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Always replace characters", 2);
	y += h3;
	addRadioButton(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Only replace if length exceeds", 2);
	x += 240;
	addTextBox(x, y, 70, h, "", false, "", 800);
	y += h2;
	x = x2;



	addText(x, y, w, h, "Extra Options");
	y += h2;

	addCheckBox(x, y, uiCheckableItemWidth, uiCheckableItemHeight, "Update LOD names to match new name", -1, "", 900);
	y += h3;
}

// window events
void					RenamerWindowLayer::onPressButton(Button *pButton)
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
		// Rename
		pWindow1->m_bWindow2Cancelled = false;

		pWindowManager->m_renamerWindowResult.m_uiEntriesType = getSelectedRadioButton(0)->getIndex();
		pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInIDE = ((CheckBox*)getItemById(310))->isMarked();
		pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInIPL = ((CheckBox*)getItemById(410))->isMarked();
		pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInCOL = ((CheckBox*)getItemById(510))->isMarked();
		pWindowManager->m_renamerWindowResult.m_uiCharCase = getSelectedRadioButton(1)->getIndex();
		pWindowManager->m_renamerWindowResult.m_uiCharReplaceType = getSelectedRadioButton(2)->getIndex();
		pWindowManager->m_renamerWindowResult.m_bUpdateLODNames = ((CheckBox*)getItemById(900))->isMarked();

		string
			strMatchingEntriesInIDEFolder = ((TextBox*)getItemById(300))->getText(),
			strMatchingEntriesInIPLFolder = ((TextBox*)getItemById(400))->getText(),
			strMatchingEntriesInCOLFolder = ((TextBox*)getItemById(500))->getText(),

			strCharAddingFront = ((TextBox*)getItemById(600))->getText(),
			strCharAddingEnd = ((TextBox*)getItemById(640))->getText(),
			strCharAddingAtPosition = ((TextBox*)getItemById(680))->getText(),
			strCharAddingAtPosition2 = ((TextBox*)getItemById(690))->getText(),

			strCharRemovingFront = ((TextBox*)getItemById(700))->getText(),
			strCharRemovingEnd = ((TextBox*)getItemById(740))->getText(),
			strCharRemovingAtPosition = ((TextBox*)getItemById(780))->getText(),
			strCharRemovingAtPosition2 = ((TextBox*)getItemById(790))->getText(),

			strOnlyReplaceIfLengthExceeds = ((TextBox*)getItemById(800))->getText();

		pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInIDEFolderPath = strMatchingEntriesInIDEFolder;
		pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInIPLFolderPath = strMatchingEntriesInIPLFolder;
		pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInCOLFolderPath = strMatchingEntriesInCOLFolder;

		pWindowManager->m_renamerWindowResult.m_strCharAddingFront = strCharAddingFront;
		pWindowManager->m_renamerWindowResult.m_strCharAddingEnd = strCharAddingEnd;
		pWindowManager->m_renamerWindowResult.m_strCharAddingAtPosition = strCharAddingAtPosition;
		pWindowManager->m_renamerWindowResult.m_uiCharAddingAtPositionIndex = String::toUint32(strCharAddingAtPosition2);

		pWindowManager->m_renamerWindowResult.m_uiCharRemovingFront = String::toUint32(strCharRemovingFront);
		pWindowManager->m_renamerWindowResult.m_uiCharRemovingEnd = String::toUint32(strCharRemovingEnd);
		pWindowManager->m_renamerWindowResult.m_uiCharRemovingAtPosition = String::toUint32(strCharRemovingAtPosition);
		pWindowManager->m_renamerWindowResult.m_uiCharRemovingAtPosition2 = String::toUint32(strCharRemovingAtPosition2);

		pWindowManager->m_renamerWindowResult.m_uiOnlyReplaceIfLengthExceeds = String::toUint32(strOnlyReplaceIfLengthExceeds);


		if (pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInIDE && pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInIDEFolderPath == "")
		{
			Input::showMessage("The path to a folder containing IDE files must be set, as the check box is checked.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInIPL && pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInIPLFolderPath == "")
		{
			Input::showMessage("The path to a folder containing IPL files must be set, as the check box is checked.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_renamerWindowResult.m_bMatchingEntriesInCOL && pWindowManager->m_renamerWindowResult.m_strMatchingEntriesInCOLFolderPath == "")
		{
			Input::showMessage("The path to a folder containing COL files must be set, as the check box is checked.", "Input Error", MB_OK);
			return;
		}

		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}

	case 210:
		// Cancel
		pWindow1->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}
}