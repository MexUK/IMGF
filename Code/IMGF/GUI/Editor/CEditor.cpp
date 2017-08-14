#include "CEditor.h"
#include "Path/CPathManager.h"
#include "GUI/Editor/Tab/CEditorTab.h"
#include "Format/CFormat.h"
#include "CIMGF.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Controls/CTabBarControl.h"
#include "GUI/Windows/CMainWindow.h"
#include "Type/String/CString2.h"

using namespace std;
using namespace bxcf;

CEditor::CEditor(void) :
	m_pActiveTab(nullptr),
	m_pTabBar(nullptr)
{
}

// initialization
void								CEditor::init(void)
{
	m_pTabBar = ((CMainWindow*)getWindow())->getTabBar();
}

// add tab object
void								CEditor::addTab(CEditorTab *pEditorTab)
{
	pEditorTab->setIndex(m_vecTabs.getNextEntryIndex());
	m_vecTabs.addEntry(pEditorTab);
	setActiveTab(pEditorTab);

	string& strFilePath = pEditorTab->getFile()->getFilePath();

	string strTabText = CPathManager::getFileName(strFilePath);
	if (CString2::toUpperCase(CPathManager::getFileExtension(strTabText)) == "DIR")
	{
		strTabText = CPathManager::replaceFileExtensionWithCase(strTabText, "IMG");
	}
	strTabText += " (" + CString2::toString(pEditorTab->getFile()->m_uiEntryCount) + ")";
	m_pTabBar->addTab(strTabText, true);

	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);
}