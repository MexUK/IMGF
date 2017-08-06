#include "CIMGFWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Controls/CButtonControl.h"
#include "Controls/CListControl.h"
#include "Styles/CGUIStyles.h"
#include "GUI/CWindowManager.h"
#include "GUI/CGUIManager.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "File/CFileManager.h"
#include "Path/CPathManager.h"
#include "Type/String/CString2.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "Type/Vector/CColour.h"
#include "GUI/Window/CMainLayer.h"

using namespace std;
using namespace bxcf;

CIMGFWindow::CIMGFWindow(void)
{
	m_pMainLayer = new CMainLayer;
}

// main interface
void					CIMGFWindow::init(void)
{
	CWindow::init();

	initWindow();
	initMainLayer();

	initEditors();

	bindEvents();
}

// event binding
void					CIMGFWindow::bindEvents(void)
{
	CWindow::bindEvents();
}

// window initialization
void					CIMGFWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - Development Version");
	getStyles()->setStyle("fill-colour", CColour(0, 140, 200, 255)); // medium blue
}

void					CIMGFWindow::initMainLayer(void)
{
	m_pMainLayer->setWindow(this);
	m_pMainLayer->setIMGFWindow(this);
	m_pMainLayer->setEnabled(true);
	addEntry(m_pMainLayer);
	m_pMainLayer->init();
}

void					CIMGFWindow::initEditors(void)
{
	//addEditor(new CDATEditor);
	addEditor(new CIMGEditor); // CIMGEditor eventually extends CGUILayer - todo use pWindow->addTemplatedGroup<CIMGEditor>() instead?
}

// editors (layers)
void					CIMGFWindow::addEditor(CEditor *pEditor)
{
	pEditor->setWindow(this);
	pEditor->setEnabled(true);
	addEntry(pEditor);
	pEditor->init();
}

// render
bool					CIMGFWindow::onRender(void)
{
	renderTitleBar();
	renderEtc();

	return true;
}

void					CIMGFWindow::renderTitleBar(void)
{
	/*
	CGraphicsLibrary *pGFX = bxgx::CGUIManager::getInstance()->getGraphicsLibrary();

	string strStyleGroup = "titleBar";
	string strTitleBarText = "IMG Factory ALPHA";
	uint32 uiTitleBarTextFontSize = 14;
	CGUIStyles styles9;
	styles9.setEntry("text-size", uiTitleBarTextFontSize);
	uint32 uiTitleBarTextWidth = pGFX->getTextSize(strTitleBarText, &styles9).m_x;
	uint32 uiTitleBarTextX = 6;// todo (getSize().m_x / 2) - (uiTitleBarTextWidth / 2);

	CGUIStyles styles1;
	styles1.setEntry("fill-colour", CColour(50, 50, 50));
	pGFX->drawRectangle(CPoint2D((int32) 0, 0), CSize2D(getSize().m_x, getTitleBarHeight()), 0, strStyleGroup);

	CGUIStyles styles2;
	styles2.setStyle("text-align-x", string("left"));
	styles2.setStyle("text-align-y", string("center"));
	styles2.setEntry("text-colour", CColour(0xE1, 0xE6, 0xEF));
	styles2.setEntry("text-size", uiTitleBarTextFontSize);
	pGFX->drawText(CPoint2D(uiTitleBarTextX, 1), CSize2D(uiTitleBarTextWidth, getTitleBarHeight()), strTitleBarText, 0, strStyleGroup);

	if (getIMGF()->getThemeDesigner()->isThemeDesignerModeEnabled())
	{
		CGUIStyles stylesThemeDesigner;
		stylesThemeDesigner.setStyle("text-colour", CColour(241, 155, 30));
		//stylesThemeDesigner.setStyle<string>("text-style", "bold");
		stylesThemeDesigner.setStyle<uint32>("text-size", 15);
		string strText = "[Theme Designer Mode]";
		pGFX->drawText(CPoint2D((int32) 10, 8), CSize2D(200, 20), strText, 0, strStyleGroup);
	}
	*/
}

void					CIMGFWindow::renderEtc(void)
{
	/*
	CGraphicsLibrary *pGFX = bxgx::CGUIManager::getInstance()->getGraphicsLibrary();
	CPoint2D vecDrawStartPosition = CPoint2D(0, getTitleBarHeight());

	return; // todo







	// render background
	pGFX->drawRectangleFill(vecDrawStartPosition, getSize(), getStyles());

	// render window backgrounds
	string strTabText = "Opened.IMG";
	string strTotalEntriesText = "Total Entries: 0";

	uint32 uiTabTextFontSize = 14;
	uint32 uiTabTextY = vecDrawStartPosition.m_y + 66;
	CGUIStyles styles10;
	styles10.setEntry("text-size", uiTabTextFontSize);
	uint32 uiTabTextWidth = pGFX->getTextSize(strTabText, &styles10).m_x;
	uint32 uiTabPaddingX = 17;
	uint32 uiTabWidth = uiTabTextWidth + (2 * uiTabPaddingX);
	uint32 uiTabTextX = vecDrawStartPosition.m_x + 252 + uiTabPaddingX;

	CGUIStyles styles2;
	styles2.setEntry("fill-colour", CColour(0x73, 0x9B, 0xB2, 0xFF));
	pGFX->drawRectangleFill(CPoint2D(vecDrawStartPosition.m_x + 213, vecDrawStartPosition.m_y), CSize2D(805, 38), &styles2);

	styles2.setEntry("fill-colour", CColour(0x2B, 0x63, 0x81, 0xFF));
	pGFX->drawRectangleFill(CPoint2D(vecDrawStartPosition.m_x + 213, vecDrawStartPosition.m_y + 38), CSize2D(805, 586), &styles2);

	CGUIStyles styles3;
	styles3.setEntry("fill-colour", CColour(0x2B, 0x63, 0x81, 0xFF));
	styles3.setEntry("border-intersection-radius", 20);
	styles3.setEntry("border-colour", CColour(0xFD, 0xFE, 0xFE, 0xFF));
	pGFX->drawRectangle(CPoint2D(vecDrawStartPosition.m_x + 226, vecDrawStartPosition.m_y + 57), CSize2D(777, 528), &styles3);
	
	///////////
	todo
	CGUIStyles styles8;
	styles8.setEntry("fill-colour", CColour(0xEC, 0xF3, 0xFD, 0xFF));
	pGFX->drawRectangleFill(CSize2D(vecDrawStartPosition.m_x + 252, vecDrawStartPosition.m_y + 87), CSize2D(732, 480), &styles8);
	///////////
	
	CGUIStyles styles4;
	styles4.setEntry("fill-colour-start", CColour(0x54, 0x89, 0xA7, 0xFF));
	styles4.setEntry("fill-colour-stop", CColour(0x31, 0x69, 0x88, 0xFF));
	pGFX->drawRectangleFill(CPoint2D(vecDrawStartPosition.m_x + 252, vecDrawStartPosition.m_y + 61), CSize2D(uiTabWidth, 26), &styles4);
	
	CGUIStyles styles5;
	styles4.setEntry("text-colour", CColour(0xE1, 0xE6, 0xEF, 0xFFF));
	styles4.setEntry("text-size", uiTabTextFontSize);
	pGFX->drawText(CPoint2D(vecDrawStartPosition.m_x + uiTabTextX, uiTabTextY), CSize2D(uiTabWidth, 26), strTabText, &styles5);
	
	CGUIStyles styles6;
	styles4.setEntry("text-colour", CColour(0xE1, 0xE6, 0xEF, 0xFF));
	styles4.setEntry("text-size", 13);
	pGFX->drawText(CPoint2D(vecDrawStartPosition.m_x + 252, vecDrawStartPosition.m_y + 597), CSize2D(200, 20), strTotalEntriesText, &styles6);

	uint32 uiButtonY = vecDrawStartPosition.m_y + 38 + 40;
	CGUIStyles styles7;
	for (uint32 i = 1; i < 14; i++)
	{
		CColour fillColour = (i % 2) == 0 ? CColour(0x1A, 0x3C, 0x4E, 0xFF) : CColour(0x21, 0x4E, 0x67, 0xFF);
		styles7.setEntry("fill-colour", fillColour);
		pGFX->drawRectangleFill(CPoint2D(38, uiButtonY), CSize2D(172, 40), &styles7);
		uiButtonY += 40;
	}
	*/
}

// input processing
void					CIMGFWindow::onDropFiles(vector<string>& vecPaths)
{
	vector<string>
		vecOpenPaths,
		vecEntryPaths;
	for (uint32 i = 0; i < vecPaths.size(); i++)
	{
		string strPath = vecPaths[i];

		// folder
		if (CFileManager::doesFolderExist(strPath))
		{
			strPath = CPathManager::addSlashToEnd(strPath);
			vector<string> vecFileNames = CFileManager::getFileNames(strPath);
			for (auto strFileName : vecFileNames)
			{
				vecPaths.push_back(strPath + strFileName);
			}
			continue;
		}

		string strExtension = CString2::toUpperCase(CPathManager::getFileExtension(strPath));
		if (strExtension == "IMG" || strExtension == "DIR")
		{
			// open IMG
			vecOpenPaths.push_back(strPath);
		}
		else
		{
			if (getIMGF()->getActiveTab() == nullptr)
			{
				return;
			}

			vecEntryPaths.push_back(strPath);
		}
	}

	if (vecEntryPaths.size() > 0)
	{
		for (auto strPath : vecEntryPaths)
		{
			getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strPath);
		}
		//getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_23", vecImportPaths.size()));

		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	for (auto strPath : vecOpenPaths)
	{
		getIMGF()->getTaskManager()->getDispatch()->onRequestOpen2(strPath);
	}
}