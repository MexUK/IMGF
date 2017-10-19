#include "SettingsWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Task/TaskManager.h"

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
	unbindEvent(CHECK_CHECK_BOX, &SettingsWindowLayer::onMarkCheckBox);
	unbindEvent(UNCHECK_CHECK_BOX, &SettingsWindowLayer::onUnmarkCheckBox);
	unbindEvent(SELECT_DROP_DOWN_ITEM, &SettingsWindowLayer::onSelectDropDownItem);
}

// initialization
void					SettingsWindowLayer::init(void)
{
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();

	addButton(50, 450, 100, 20, "Close", "window2_button", 200);

	int32
		yGap1 = 30,
		yGap2 = 70;
	uint32
		y = 50;

	// text
	addText(50, y, 500, 20, "Text");
	y += yGap1;

	addText(50, y, 83, 50, "Language:");
	DropDown *pLanguageDropDown = addDropDown(135, y - 2, 150, 20, "Choose..", "window2_dropDown", 300);
	vector<string> vecLanguages = { "English" };
	string strActiveLanguageName = "English";
	for (string& strLanguage : vecLanguages)
	{
		bool bActiveItem = false;
		if (strLanguage == strActiveLanguageName)
		{
			bActiveItem = true;
		}
		pLanguageDropDown->addItem(strLanguage, bActiveItem);
	}
	y += yGap2;

	// graphics
	addText(50, y, 500, 20, "Graphics");
	y += yGap1;

	CheckBox *pAlwaysOnTopCheckBox = addCheckBox(50, y, 20, 20, "Window Always on Top", -1, "window2_checkBox", 400);
	if (BXGX::get()->getFirstEntry()->isTopZIndex())
	{
		pAlwaysOnTopCheckBox->setMarked(true);
	}
	y += yGap1;

	// theme
	addText(50, y, 83, 50, "Theme:");

	DropDown *pThemesDropDown = addDropDown(135, y, 150, 20, "Choose..", "window2_checkBox", 410);
	string& strActiveThemeName = StyleManager::get()->getThemeName();
	for (string& strThemeName : StyleManager::get()->getThemeNames())
	{
		bool bActiveItem = false;
		if (strThemeName == strActiveThemeName)
		{
			bActiveItem = true;
		}
		pThemesDropDown->addItem(strThemeName, bActiveItem);
	}
	y += yGap2;

	/*
	todo
	addText(50, y, 85, 20, "Tab Colours:");
	addButton(135, y - 2, 100, 20, "Choose..", "window2_button", 420);
	y += yGap2;
	*/

	// tasks
	addText(50, y, 500, 20, "Tasks");
	y += yGap1;

	addText(50, y, 144, 20, "Quick Export Folder:");
	addButton(200, y - 2, 100, 20, "Choose..", "window2_button", 500);
	y += yGap1;

	addText(50, y, 150, 20, "Save After Tasks:");
	addButton(210, y - 2, 100, 20, "Choose..", "window2_button", 510);
	y += yGap1;

	CheckBox *pSaveLogsToFolderCheckBox = addCheckBox(50, y, 20, 20, "Save Logs to Folder:", -1, "window2_checkBox", 520);
	addButton(225, y - 2, 100, 20, "Choose..", "window2_button", 530);
	string strSaveLogsToFolder = pSettingsManager->getSetting("SaveLogsToFolder");
	if (strSaveLogsToFolder == "1")
	{
		pSaveLogsToFolderCheckBox->setMarked(true);
	}
	y += yGap2;

	bindEvent(PRESS_BUTTON, &SettingsWindowLayer::onPressButton);
	bindEvent(CHECK_CHECK_BOX, &SettingsWindowLayer::onMarkCheckBox);
	bindEvent(UNCHECK_CHECK_BOX, &SettingsWindowLayer::onUnmarkCheckBox);
	bindEvent(SELECT_DROP_DOWN_ITEM, &SettingsWindowLayer::onSelectDropDownItem);
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
	{
		// Rebuild After Task
		vector<string> vecListItems = String::split(pSettingsManager->getSetting("SaveAfterTasks"), ",");
		vector<string> vecSaveAfterTasks = BXGX::get()->getEntryByIndex(0)->showDynamicItemListWindow("Save After Task", "Feature", getIMGF()->getTaskManager()->getTaskNames(), "Add", "Remove Selected", vecListItems);
		if (m_pWindow->m_bWindow2Cancelled)
		{
			return;
		}
		pSettingsManager->setSetting("SaveAfterTasks", String::join(vecSaveAfterTasks, ","));
		break;
	}

	case 530:
	{
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
	
	/* Graphics */
	case 410:
		// Theme
		pSettingsManager->setSetting("ThemeName", pDropDownEntry->getText());
		StyleManager::get()->reloadTheme(pDropDownEntry->getText());
		break;
	}
}