#include "CEditor.h"
#include "Static/CPath.h"
#include "GUI/Editor/Tab/CEditorTab.h"
#include "Format/CFormat.h"
#include "CIMGF.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Controls/CTabBarControl.h"
#include "GUI/Windows/CMainWindow.h"
#include "Static/CString2.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;

CEditor::CEditor(void) :
	m_pActiveFile(nullptr),
	m_pTabBar(nullptr)
{
}

// initialization
void								CEditor::init(void)
{
	m_pTabBar = ((CMainWindow*)getWindow())->getTabBar();
}

// add/remove file
void								CEditor::addFile(CEditorTab *pEditorFile)
{
	// store file object
	m_vecTabs.addEntry(pEditorFile);
	setActiveFile(pEditorFile);

	string strFilePath = getResolvedFilePath(pEditorFile->getFile()->getFilePath());

	// choose tab text
	string strTabText = CPath::getFileName(strFilePath);
	if (CString2::toUpperCase(CPath::getFileExtension(strTabText)) == "DIR")
	{
		strTabText = CPath::replaceFileExtensionWithCase(strTabText, "IMG");
	}
	strTabText += " (" + CString2::toString(pEditorFile->getFile()->m_uiEntryCount) + ")";

	// add controls to tab layer
	pEditorFile->addControls();
	pEditorFile->initControls();

	// add tab to tab bar
	CTabBarControlEntry *pTab = m_pTabBar->addTab(strTabText, true);
	m_pTabBar->bindTabLayer(pTab, pEditorFile);
	pEditorFile->setTab(pTab);

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);
}

void								CEditor::removeFile(CEditorTab *pEditorFile)
{
	// remove tab from tab bar
	m_pTabBar->removeTab(pEditorFile->getTab());

	// remove tab object
	m_vecTabs.removeEntry(pEditorFile);

	// update active file
	uint32 uiNewActiveFileIndex = m_pTabBar->getActiveIndex();
	if (uiNewActiveFileIndex == -1)
	{
		setActiveFile(nullptr);
	}
	else
	{
		setActiveFile(m_vecTabs.getEntryByIndex(uiNewActiveFileIndex));
	}
}

void								CEditor::removeActiveFile(void)
{
	/*
	if (getTabs().getEntryCount() == 0)
	{
		return;
	}

	removeFile(getActiveFile());
	*/
}

// set active file
void								CEditor::setActiveFile(CEditorTab *pEditorFile)
{
	m_pActiveFile = pEditorFile;

	if (pEditorFile)
	{
		updateActiveFileDisplayedInfo();
	}
	else
	{
		clearActiveFileDisplayedInfo();
	}
}

void								CEditor::updateActiveFileDisplayedInfo(void)
{
	setFileInfoText(m_pActiveFile);
}

void								CEditor::clearActiveFileDisplayedInfo(void)
{
	clearFileInfoText();
}