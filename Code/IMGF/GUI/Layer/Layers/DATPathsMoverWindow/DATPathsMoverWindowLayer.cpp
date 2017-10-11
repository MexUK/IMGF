#include "DATPathsMoverWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "Control/Controls/TextBox.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

DATPathsMoverWindowLayer::DATPathsMoverWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &DATPathsMoverWindowLayer::onPressButton);
}

DATPathsMoverWindowLayer::~DATPathsMoverWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &DATPathsMoverWindowLayer::onPressButton);
}

// initialization
void					DATPathsMoverWindowLayer::init(void)
{
	addButton(420, 520, 130, 25, "Move Path Nodes", "window2_button", 200);
	addButton(570, 520, 100, 25, "Cancel", "window2_button", 210);

	int32 x, y, x2, y2;
	uint32 w, h;

	// output map range
	x = 50;
	y = 50;
	w = 200;
	h = 20;
	addText(x, y, w, h, "Output Map Range");

	x2 = x;
	y2 = y;
	y += 25;
	w = 50;
	addText(x, y, w, h, "Min X:");
	x += 50;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 500);

	x = x2;
	y += 25;
	w = 50;
	addText(x, y, w, h, "Max X:");
	x += 50;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 510);

	x = x2;
	y = y2;
	x += 150;
	y += 25;
	w = 50;
	addText(x, y, w, h, "Min Y:");
	x += 50;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 501);

	x = x2;
	x += 150;
	y += 25;
	w = 50;
	addText(x, y, w, h, "Max Y:");
	x += 50;
	w = 90;
	addTextBox(x, y, w, h, "", false, "", 511);

	// output tile size
	x = x2;
	x += 300;
	y = 50;
	w = 200;
	h = 20;
	addText(x, y, w, h, "Output Tile Size");

	y += 25;
	w = 50;
	addText(x, y, w, h, "Width:");
	x += 50;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 600);

	x += 130;
	w = 50;
	addText(x, y, w, h, "Height:");
	x += 50;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 601);

	// position offset
	x = 50;
	y = 180;
	w = 550;
	h = 20;
	addText(x, y, w, h, "Position Offset - Each coordinate must be a multiple of the Output Tile Size");

	y += 25;
	w = 50;
	addText(x, y, w, h, "X:");
	x += 20;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 700);

	x += 130;
	w = 50;
	addText(x, y, w, h, "Y:");
	x += 20;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 701);

	x += 130;
	w = 50;
	addText(x, y, w, h, "Z:");
	x += 20;
	w = 90;
	addTextBox(x, y - 2, w, h, "", false, "", 702);

	// DAT Nodes Input Folder
	x = x2;
	y += 100;
	w = 195;
	h = 20;
	addText(x, y, w, h, "Input Folder: (nodes*.DAT)");
	x += 200;
	w = 330;
	addTextBox(x, y, w, h, "", false, "", 800);
	x += 350;
	w = 100;
	addButton(x, y, w, h, "Choose..", "", 801);

	// DAT Nodes Output Folder
	x = x2;
	y += 45;
	w = 195;
	addText(x, y, w, h, "Output Folder: (nodes*.DAT)");
	x += 200;
	w = 330;
	addTextBox(x, y, w, h, "", false, "", 900);
	x += 350;
	w = 100;
	addButton(x, y, w, h, "Choose..", "", 901);
}

// window events
void					DATPathsMoverWindowLayer::onPressButton(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
	WindowManager
		*pWindowManager = getIMGF()->getWindowManager();

	switch(pButton->getId())
	{
		case 200:
		{
			// Move Path Nodes
			pWindow1->m_bWindow2Cancelled = false;

			string
				strMinOutputMapRangeX = ((TextBox*)pWindow2->getItemById(500))->getText(),
				strMinOutputMapRangeY = ((TextBox*)pWindow2->getItemById(501))->getText(),
				strMaxOutputMapRangeX = ((TextBox*)pWindow2->getItemById(510))->getText(),
				strMaxOutputMapRangeY = ((TextBox*)pWindow2->getItemById(511))->getText(),
				strOutputTileSizeX = ((TextBox*)pWindow2->getItemById(600))->getText(),
				strOutputTileSizeY = ((TextBox*)pWindow2->getItemById(601))->getText(),
				strPositionOffsetX = ((TextBox*)pWindow2->getItemById(700))->getText(),
				strPositionOffsetY = ((TextBox*)pWindow2->getItemById(701))->getText(),
				strPositionOffsetZ = ((TextBox*)pWindow2->getItemById(702))->getText(),
				strDATInputFolderPath = ((TextBox*)pWindow2->getItemById(800))->getText(),
				strDATOutputFolderPath = ((TextBox*)pWindow2->getItemById(900))->getText();

			if (strMinOutputMapRangeX == "")
			{
				Input::showMessage("The minimum output map range X co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strMinOutputMapRangeY == "")
			{
				Input::showMessage("The minimum output map range Y co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strMaxOutputMapRangeX == "")
			{
				Input::showMessage("The maximum output map range X co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strMaxOutputMapRangeY == "")
			{
				Input::showMessage("The maximum output map range Y co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strPositionOffsetX == "")
			{
				Input::showMessage("The position offset X co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strPositionOffsetY == "")
			{
				Input::showMessage("The position offset Y co ordinate must be a number.", "Input Error");
				return;
			}
			else if (strPositionOffsetZ == "")
			{
				Input::showMessage("The position offset Z co ordinate must be a number.", "Input Error");
				return;
			}

			pWindowManager->m_datPathsMoverWindowResult.m_vecMinOutputMapRange = Vec2f(String::toFloat32(strMinOutputMapRangeX), String::toFloat32(strMinOutputMapRangeY));
			pWindowManager->m_datPathsMoverWindowResult.m_vecMaxOutputMapRange = Vec2f(String::toFloat32(strMaxOutputMapRangeX), String::toFloat32(strMaxOutputMapRangeY));
			pWindowManager->m_datPathsMoverWindowResult.m_vecOutputTileSize = Vec2f(String::toFloat32(strOutputTileSizeX), String::toFloat32(strOutputTileSizeY));
			pWindowManager->m_datPathsMoverWindowResult.m_vecPositionOffset = Vec3f(String::toFloat32(strPositionOffsetX), String::toFloat32(strPositionOffsetY), String::toFloat32(strPositionOffsetZ));
			pWindowManager->m_datPathsMoverWindowResult.m_strDATInputFolderPath = strDATInputFolderPath;
			pWindowManager->m_datPathsMoverWindowResult.m_strDATOutputFolderPath = strDATOutputFolderPath;
			BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
			break;
		}
		case 210:
			// cancel
			pWindow1->m_bWindow2Cancelled = true;
			BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
			break;
		case 801:
		{
			// input folder
			string strDATInputFolderPath = Input::openFolder("Choose the input folder containing nodes*.DAT files:");
			if (strDATInputFolderPath == "")
			{
				return;
			}
			((TextBox*)pWindow2->getItemById(800))->setText(strDATInputFolderPath);
			pWindowManager->m_datPathsMoverWindowResult.m_strDATInputFolderPath = strDATInputFolderPath;
			break;
		}
		case 901:
		{
			// output folder
			string strDATOutputFolderPath = Input::openFolder("Choose the output to put the nodes*.DAT files:");
			if (strDATOutputFolderPath == "")
			{
				return;
			}
			((TextBox*)pWindow2->getItemById(900))->setText(strDATOutputFolderPath);
			pWindowManager->m_datPathsMoverWindowResult.m_strDATOutputFolderPath = strDATOutputFolderPath;
			break;
		}
	}
}