#include "SettingsWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

SettingsWindowLayer::SettingsWindowLayer(void)
{
}

SettingsWindowLayer::~SettingsWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &SettingsWindowLayer::onPressButton);
	unbindEvent(MARK_CHECKBOX, &SettingsWindowLayer::onMarkCheckBox);
	unbindEvent(UNMARK_CHECKBOX, &SettingsWindowLayer::onUnmarkCheckBox);
	unbindEvent(SELECT_DROP_ENTRY, &SettingsWindowLayer::onSelectDropDownItem);
}

// initialization
void					SettingsWindowLayer::init(void)
{
	addButton(50, 450, 100, 20, "Close", "window2_button", 200);

	int32
		yGap1 = 30,
		yGap2 = 70;
	uint32
		y = 50;

	addText(50, y, 500, 20, "Text");
	y += yGap1;
	addText(50, y, 50, 50, "Language:");
	DropDown *pLanguageDropDown = addDropDown(135, y - 2, 150, 20, "Choose..", "window2_dropDown", 300);
	pLanguageDropDown->addItems(vector<string>({ "English" }));
	y += yGap2;

	addText(50, y, 500, 20, "Graphics");
	y += yGap1;
	addCheckBox(50, y, 20, 20, "Window Always on Top", "window2_checkBox", 400);
	y += yGap1;
	addText(50, y, 500, 20, "Tab Colours:");
	addButton(135, y - 2, 100, 20, "Choose..", "window2_button", 410);
	y += yGap2;

	addText(50, y, 500, 20, "Tasks");
	y += yGap1;
	addText(50, y, 500, 20, "Quick Export Folder:");
	addButton(180, y - 2, 100, 20, "Choose..", "window2_button", 500);
	y += yGap1;
	addText(50, y, 500, 20, "Rebuild After Feature:");
	addButton(190, y - 2, 100, 20, "Choose..", "window2_button", 510);
	y += yGap1;
	addCheckBox(50, y, 20, 20, "Save Logs to Folder:", "window2_checkBox", 520);
	addButton(210, y - 2, 100, 20, "Choose..", "window2_button", 530);
	y += yGap2;

	bindEvent(PRESS_BUTTON, &SettingsWindowLayer::onPressButton);
	bindEvent(MARK_CHECKBOX, &SettingsWindowLayer::onMarkCheckBox);
	bindEvent(UNMARK_CHECKBOX, &SettingsWindowLayer::onUnmarkCheckBox);
	bindEvent(SELECT_DROP_ENTRY, &SettingsWindowLayer::onSelectDropDownItem);
}

// events
void					SettingsWindowLayer::onPressButton(Button *pButton)
{
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();
	string strFolderPath;

	switch (pButton->getId())
	{
	/* Graphics */
	case 410:
		// Tab Colours

		break;

	/* Tasks */
	case 500:
		// Quick Export Folder
		strFolderPath = pSettingsManager->getSetting("QuickExportFolderPath");
		strFolderPath = Input::openFolder("Choose a folder to export file(s) to for the Quick Export feature.", strFolderPath);
		if (strFolderPath == "")
		{
			return;
		}
		pSettingsManager->setSetting("QuickExportFolderPath", strFolderPath);
		break;
	case 510:
		// Rebuild After Feature

		break;
	case 530:
		// Save Logs to Folder
		strFolderPath = pSettingsManager->getSetting("LogsFolderPath");
		strFolderPath = Input::openFolder("Choose a folder to save logs to.", strFolderPath);
		if (strFolderPath == "")
		{
			return;
		}
		pSettingsManager->setSetting("LogsFolderPath", strFolderPath);
		break;
	}
}

void					SettingsWindowLayer::onMarkCheckBox(bxgx::CheckBox *pCheckBox)
{
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();

	switch (pCheckBox->getId())
	{
	/* Graphics */
	case 400:
		// Window Always on Top
		pSettingsManager->setSetting("WindowAlwaysOnTop", "1");
		getIMGF()->getWindowManager()->getMainWindow()->setTopZIndex(true);
		break;

	/* Tasks */
	case 520:
		// Save Logs to Folder
		pSettingsManager->setSetting("SaveLogsToFolder", "1");
		break;
	}
}

void					SettingsWindowLayer::onUnmarkCheckBox(bxgx::CheckBox *pCheckBox)
{
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();

	switch (pCheckBox->getId())
	{
	/* Graphics */
	case 400:
		// Window Always on Top
		pSettingsManager->setSetting("WindowAlwaysOnTop", "0");
		getIMGF()->getWindowManager()->getMainWindow()->setTopZIndex(false);
		break;

	/* Tasks */
	case 520:
		// Save Logs to Folder
		pSettingsManager->setSetting("SaveLogsToFolder", "0");
		break;
	}
}

void					SettingsWindowLayer::onSelectDropDownItem(DropDownItem *pDropDownEntry)
{
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();
	DropDown *pDropDown = pDropDownEntry->getDropControl();

	switch (pDropDown->getId())
	{
	/* Text */
	case 300:
		// Language
		pSettingsManager->setSetting("Language", pDropDownEntry->getText());
		break;
	}
}