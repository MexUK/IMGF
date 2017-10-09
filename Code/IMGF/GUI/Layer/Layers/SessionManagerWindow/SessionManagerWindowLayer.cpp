#include "SessionManagerWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/Grid.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "Task/Tasks/Session/SessionManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

SessionManagerWindowLayer::SessionManagerWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

SessionManagerWindowLayer::~SessionManagerWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

// initialization
void					SessionManagerWindowLayer::init(void)
{
	Grid *pGrid = addGrid(50, 50, 600, 500, "window2_grid", 190);
	vector<string> vecGridHeaders = { "Session ID", "Session Name", "File Count", "File Names" };
	pGrid->addHeaders(vecGridHeaders);
	pGrid->getHeaders().getEntryByIndex(0)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(1)->setColumnWidth(170);
	pGrid->getHeaders().getEntryByIndex(2)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(3)->setColumnWidth(270);

	addButton(50, 580, 120, 20, "Add Session", "window2_button", 200);
	addButton(190, 580, 120, 20, "Update Session", "window2_button", 210);
	addButton(330, 580, 120, 20, "Remove Session", "window2_button", 220);
	addButton(510, 580, 120, 20, "Close", "window2_button", 230);

	reloadSessionsGrid();
}

// data lading
void					SessionManagerWindowLayer::reloadSessionsGrid(void)
{
	Grid *pSessionGrid = (Grid*)getItemById(190);
	for (Session *pSession : getIMGF()->getSessionManager()->getEntries())
	{
		GridRow *pRow = new GridRow;
		vector<vector<string>> vecRowText = { { "Session ID", "Session Name", "File Count", "File Names" } };
		pRow->getText() = vecRowText;
		pSessionGrid->addEntry(pRow);
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
		// Add Session
		string strIMGFilePaths = pWindow2->showMultiLineTextBoxWindow("Add Session", "Separate IMG/DIR file paths with a new line, put session name on the first line.");
		vector<string> vecInputLines = String::split(strIMGFilePaths, "\n");
		string& strSessionManager = vecInputLines[0];
		vector<string> vecIMGFilePaths;
		for (uint32 i = 1, j = vecInputLines.size(); i < j; i++)
		{
			string& strIMGFilePath = vecInputLines[i];
			strIMGFilePath = String::trim(strIMGFilePath);
			vecIMGFilePaths.push_back(strIMGFilePath);
		}
		getIMGF()->getSessionManager()->addSession(strSessionManager, vecIMGFilePaths);
		reloadSessionsGrid();
		break;
	}

	case 210:
	{
		// Update Session
		string strIMGFilePaths = pWindow2->showMultiLineTextBoxWindow("Update Session", "Separate IMG/DIR file paths with a new line, put session name on the first line.");
		vector<string> vecInputLines = String::split(strIMGFilePaths, "\n");
		string& strSessionName = vecInputLines[0];
		vector<string> vecIMGFilePaths;
		for (uint32 i = 1, j = vecInputLines.size(); i < j; i++)
		{
			string& strIMGFilePath = vecInputLines[i];
			strIMGFilePath = String::trim(strIMGFilePath);
			vecIMGFilePaths.push_back(strIMGFilePath);
		}
		reloadSessionsGrid();
		getIMGF()->getSessionManager()->getSessionByName(strSessionName)->setPaths(vecIMGFilePaths);
		break;
	}

	case 220:
	{
		// Remove Session
		Grid *pSessionGrid = (Grid*)getItemById(190);
		for (GridRow *pRow : pSessionGrid->getSelectedRows())
		{
			string strSessionName = pRow->getText()[1][0];
			Session *pSession = getIMGF()->getSessionManager()->getSessionByName(strSessionName);
			getIMGF()->getSessionManager()->removeSession(pSession);
		}
		reloadSessionsGrid();
		break;
	}

	case 230:
		// Close
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}
}