#include "SessionManagerWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/Grid.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Task/Tasks/FileGroups/FileGroupManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

SessionManagerWindowLayer::SessionManagerWindowLayer(void) // todo - rename class to File Group
{
	bindDefaultEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

SessionManagerWindowLayer::~SessionManagerWindowLayer(void)
{
	unbindDefaultEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

// initialization
void					SessionManagerWindowLayer::init(void)
{
	Grid *pGrid = addGrid(50, 50, 600, 500, "window2_grid", 190);
	vector<string> vecGridHeaders = { "File Group ID", "File Group Name", "File Count", "File Names" };
	pGrid->addHeaders(vecGridHeaders);
	pGrid->getHeaders().getEntryByIndex(0)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(1)->setColumnWidth(170);
	pGrid->getHeaders().getEntryByIndex(2)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(3)->setColumnWidth(270);

	addButton(50, 580, 120, 20, "Add File Group", "window2_button", 200);
	addButton(190, 580, 120, 20, "Update File Group", "window2_button", 210);
	addButton(330, 580, 120, 20, "Remove File Group", "window2_button", 220);
	addButton(510, 580, 120, 20, "Close", "window2_button", 230);

	reloadFileGroupsGrid();
}

// data lading
void					SessionManagerWindowLayer::reloadFileGroupsGrid(void)
{
	Grid *pFileGroupGrid = (Grid*)getItemById(190);
	for (FileGroup *pFileGroup : getIMGF()->getFileGroupManager()->getEntries())
	{
		GridRow *pRow = new GridRow;
		vector<vector<SizedString>> vecRowText = { { SizedString(string("File Group ID")), SizedString(string("File Group Name")), SizedString(string("File Count")), SizedString(string("File Names")) } };
		pRow->getText() = vecRowText;
		pFileGroupGrid->addEntry(pRow);
	}
}

// window events
void					SessionManagerWindowLayer::onPressButton(Button *pButton)
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
		// Add File Group
		string strIMGFilePaths = pWindow2->showMultiLineTextBoxWindow("Add File Group", "Separate IMG/DIR file paths with a new line, put file group name on the first line.");
		vector<string> vecInputLines = String::split(strIMGFilePaths, "\n");
		string& strFileGroupName = vecInputLines[0];
		vector<string> vecIMGFilePaths;
		for (uint32 i = 1, j = vecInputLines.size(); i < j; i++)
		{
			string& strIMGFilePath = vecInputLines[i];
			strIMGFilePath = String::trim(strIMGFilePath);
			vecIMGFilePaths.push_back(strIMGFilePath);
		}
		getIMGF()->getFileGroupManager()->addFileGroup(pWindowManager->getMainWindow()->getActiveEditor()->getEditorType(), strFileGroupName, vecIMGFilePaths);
		reloadFileGroupsGrid();
		break;
	}

	case 210:
	{
		// Update File Group
		string strIMGFilePaths = pWindow2->showMultiLineTextBoxWindow("Update File Group", "Separate IMG/DIR file paths with a new line, put file group name on the first line.");
		vector<string> vecInputLines = String::split(strIMGFilePaths, "\n");
		string& strFileGroupName = vecInputLines[0];
		vector<string> vecIMGFilePaths;
		for (uint32 i = 1, j = vecInputLines.size(); i < j; i++)
		{
			string& strIMGFilePath = vecInputLines[i];
			strIMGFilePath = String::trim(strIMGFilePath);
			vecIMGFilePaths.push_back(strIMGFilePath);
		}
		reloadFileGroupsGrid();
		getIMGF()->getFileGroupManager()->getFileGroupByName(pWindowManager->getMainWindow()->getActiveEditor()->getEditorType(), strFileGroupName)->setPaths(vecIMGFilePaths);
		break;
	}

	case 220:
	{
		// Remove File Group
		Grid *pFileGroupGrid = (Grid*)getItemById(190);
		for (GridRow *pRow : pFileGroupGrid->getSelectedRows())
		{
			string strFileGroupName = pRow->getText()[1][0].getString();
			FileGroup *pFileGroup = getIMGF()->getFileGroupManager()->getFileGroupByName(pWindowManager->getMainWindow()->getActiveEditor()->getEditorType(), strFileGroupName);
			getIMGF()->getFileGroupManager()->removeFileGroup(pWindowManager->getMainWindow()->getActiveEditor()->getEditorType(), pFileGroup);
		}
		reloadFileGroupsGrid();
		break;
	}

	case 230:
		// Close
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}
}