#include "CIMGFWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Controls/CButtonControl.h"
#include "Controls/CGridControl.h"
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
	initWindow();
	initMainLayer();
	initEditors();
	bindEvents();
}

// window initialization
void					CIMGFWindow::initWindow(void)
{
	CWindow::init();

	addTitleBar("IMG Factory 2.0 - Development Version");
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
	addEditor(new CIMGEditor);
}

// editors (layers)
void					CIMGFWindow::addEditor(CEditor *pEditor)
{
	pEditor->setWindow(this);
	pEditor->setEnabled(true);
	addEntry(pEditor);
	pEditor->init();
}

// input processing
/*
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
		//getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_23", vecImportPaths.size()));

		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	for (auto strPath : vecOpenPaths)
	{
		getIMGF()->getTaskManager()->getDispatch()->onRequestOpen2(strPath);
	}
}
*/