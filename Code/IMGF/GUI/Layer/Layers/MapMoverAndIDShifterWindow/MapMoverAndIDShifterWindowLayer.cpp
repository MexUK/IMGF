#include "MapMoverAndIDShifterWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/TextBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

MapMoverAndIDShifterWindowLayer::MapMoverAndIDShifterWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &MapMoverAndIDShifterWindowLayer::onPressButton);
}

MapMoverAndIDShifterWindowLayer::~MapMoverAndIDShifterWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &MapMoverAndIDShifterWindowLayer::onPressButton);
}

// initialization
void					MapMoverAndIDShifterWindowLayer::init(void)
{
	addButton(200, 610, 160, 20, "Move Map & Shift IDs", "window2_button", 200);
	addButton(380, 610, 100, 20, "Cancel", "window2_button", 210);

	int32 x1, x2, x3, y, w, h;

	x1 = 35;
	x2 = 150;
	x3 = 560;

	w = 400;
	h = 40;
	y = 50;

	addText(x1, y, 90, 20, "DAT File:");
	addTextBox(x2, y, w, 25, "", 300);
	addButton(x3, y, 100, 25, "Choose..", "", 310);
	y += h;

	addText(x1, y, 90, 20, "Game Folder:");
	addTextBox(x2, y, w, 25, "", 400);
	addButton(x3, y, 100, 25, "Choose..", "", 410);
	y += h;

	addCheckBox(x1, y, 20, 20, "IDE Folder:", 501);
	addTextBox(x2, y, w, 25, "", 500);
	addButton(x3, y, 100, 25, "Choose..", "", 510);
	y += h;

	addCheckBox(x1, y, 20, 20, "IPL Folder:", 601);
	addTextBox(x2, y, w, 25, "", 600);
	addButton(x3, y, 100, 25, "Choose..", "", 610);
	y += h;

	addText(x1, y, 95, 20, "Output Folder:");
	addTextBox(x2, y, w, 25, "", 700);
	addButton(x3, y, 100, 25, "Choose..", "", 710);
	y += h;

	addCheckBox(x1, y, 20, 20, "ID Start:", 801);
	addTextBox(x2, y, 150, 25, "", 800);
	y += h;

	x1 += 150;
	x2 = x1 + 170;
	x3 = x2 + 170;

	addCheckBox(x1 - 150, y, 20, 20, "Position Offset:", 901);
	addText(x1, y, 20, 20, "X:");
	addTextBox(x1 + 20, y, 130, 25, "", 900);
	addText(x2, y, 20, 20, "Y:");
	addTextBox(x2 + 20, y, 130, 25, "", 910);
	addText(x3, y, 20, 20, "Z:");
	addTextBox(x3 + 20, y, 130, 25, "", 920);
	y += h;
	x1 -= 150;

	addCheckBox(x1, y, 20, 20, "Ignore Default Objects (GTA III, VC, SA)", 1000);
	y += h * 2;

	addText(x1, y, 250, 20, "Ignore Files for ID Shifter");
	addText(320, y, 250, 20, "Ignore Files for Map Mover");
	y += 20;

	addTextBox(x1, y, 250, 160, "", 1100);
	addTextBox(320, y, 250, 160, "", 1110);
}

// window events
void					MapMoverAndIDShifterWindowLayer::onPressButton(Button *pButton)
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
		// Move Map & Shift IDs
		pWindow1->m_bWindow2Cancelled = false;

		string
			strDATFilePath = ((TextBox*)pWindow2->getItemById(300))->getText(),
			strGameFolderPath = ((TextBox*)pWindow2->getItemById(400))->getText(),
			strIDEFolderPath = ((TextBox*)pWindow2->getItemById(500))->getText(),
			strIPLFolderPath = ((TextBox*)pWindow2->getItemById(600))->getText(),
			strOutputFolderPath = ((TextBox*)pWindow2->getItemById(700))->getText(),
			strIDStart = ((TextBox*)pWindow2->getItemById(800))->getText(),
			strPositionOffsetX = ((TextBox*)pWindow2->getItemById(900))->getText(),
			strPositionOffsetY = ((TextBox*)pWindow2->getItemById(910))->getText(),
			strPositionOffsetZ = ((TextBox*)pWindow2->getItemById(920))->getText();
		vector<string>
			vecIgnoreFilesForIDShifter = String::split(((TextBox*)pWindow2->getItemById(1100))->getText(), "\n"),
			vecIgnoreFilesForMapMover = String::split(((TextBox*)pWindow2->getItemById(1110))->getText(), "\n");

		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIDEFolder = ((CheckBox*)pWindow2->getItemById(501))->isMarked();
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIPLFolder = ((CheckBox*)pWindow2->getItemById(601))->isMarked();
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIDStart = ((CheckBox*)pWindow2->getItemById(801))->isMarked();
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUsePositionOffset = ((CheckBox*)pWindow2->getItemById(901))->isMarked();
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bIgnoreDefaultObjects = ((CheckBox*)pWindow2->getItemById(1000))->isMarked();

		if (strDATFilePath == "")
		{
			Input::showMessage("DAT file path must be specified.", "Input Error", MB_OK);
			return;
		}
		else if (strGameFolderPath == "")
		{
			Input::showMessage("Game folder path must be specified.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIDEFolder && strIDEFolderPath == "")
		{
			Input::showMessage("IDE folder path must be specified, as the check box is checked for it.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIPLFolder && strIPLFolderPath == "")
		{
			Input::showMessage("IPL folder path must be specified, as the check box is checked for it.", "Input Error", MB_OK);
			return;
		}
		else if (strOutputFolderPath == "")
		{
			Input::showMessage("Output folder path must be specified.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUseIDStart && !String::isPositiveInteger(strIDStart))
		{
			Input::showMessage("The ID to start the objects at must be a positive integer.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUsePositionOffset && strPositionOffsetX == "")
		{
			Input::showMessage("The X co ordinate for the position offset must be specified, as the check box is checked for it.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUsePositionOffset && strPositionOffsetY == "")
		{
			Input::showMessage("The Y co ordinate for the position offset must be specified, as the check box is checked for it.", "Input Error", MB_OK);
			return;
		}
		else if (pWindowManager->m_mapMoverAndIDShifterWindowResult.m_bUsePositionOffset && strPositionOffsetZ == "")
		{
			Input::showMessage("The Z co ordinate for the position offset must be specified, as the check box is checked for it.", "Input Error", MB_OK);
			return;
		}

		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strDATFile = strDATFilePath;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strGameFolder = strGameFolderPath;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strIDEFolder = strIDEFolderPath;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strIPLFolder = strIPLFolderPath;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strOutputFolder = strOutputFolderPath;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_uiIDStart = String::toUint32(strIDStart);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_vecPositionOffset = Vec3f(String::toFloat32(strPositionOffsetX), String::toFloat32(strPositionOffsetY), String::toFloat32(strPositionOffsetZ));
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter = vecIgnoreFilesForIDShifter;
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover = vecIgnoreFilesForMapMover;

		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;
	}

	case 201:
		// cancel
		pWindow1->m_bWindow2Cancelled = true;
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
		break;

	case 310:
	{
		// DAT File
		vector<string> vecDATFiles = Input::openFile("", "DAT", false);
		if (vecDATFiles.size() == 0)
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(300))->setText(vecDATFiles[0]);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strDATFile = vecDATFiles[0];
		break;
	}

	case 410:
	{
		// Game Folder
		string strGameFolderPath = Input::openFolder("Choose a game folder:");
		if (strGameFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(400))->setText(strGameFolderPath);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strOutputFolder = strGameFolderPath;
		break;
	}

	case 510:
	{
		// IDE Folder
		string strIDEFolderPath = Input::openFolder("Choose a folder containing IDE files:");
		if (strIDEFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(500))->setText(strIDEFolderPath);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strIDEFolder = strIDEFolderPath;
		break;
	}

	case 610:
	{
		// IPL Folder
		string strIPLFolderPath = Input::openFolder("Choose a folder containing IPL files:");
		if (strIPLFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(600))->setText(strIPLFolderPath);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strIPLFolder = strIPLFolderPath;
		break;
	}

	case 710:
	{
		// Output Folder
		string strOutputFolderPath = Input::openFolder("Choose an output folder:");
		if (strOutputFolderPath == "")
		{
			return;
		}
		((TextBox*)pWindow2->getItemById(700))->setText(strOutputFolderPath);
		pWindowManager->m_mapMoverAndIDShifterWindowResult.m_strOutputFolder = strOutputFolderPath;
		break;
	}
	}
}