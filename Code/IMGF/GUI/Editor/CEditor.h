#ifndef CEditor_H
#define CEditor_H

#include "Layer/CGUILayer.h"
#include "Pool/CVectorPool.h"
#include "GUI/Editor/Tab/CEditorTab.h"

class CTabBarControl;

class CEditor : public CGUILayer
{
public:
	CEditor(void);

	virtual void						init(void) = 0;

	void								addFile(CEditorTab *pEditorTab);
	void								removeFile(CEditorTab *pEditorTab);
	void								removeActiveFile(void);

	bxcf::CVectorPool<CEditorTab*>&		getTabs(void) { return m_vecTabs; }

	void								setActiveFile(CEditorTab *pEditorFile);
	CEditorTab*							getActiveFile(void) { return m_pActiveFile; }

	void								setTabBar(CTabBarControl *pTabBar) { m_pTabBar = pTabBar; }
	CTabBarControl*						getTabBar(void) { return m_pTabBar; }

	void								updateActiveFileDisplayedInfo(void);
	void								clearActiveFileDisplayedInfo(void);

	virtual void						setFileInfoText(CEditorTab *pEditorFile) = 0;
	virtual void						clearFileInfoText(void) = 0;

protected:
	CTabBarControl*						m_pTabBar;
	CEditorTab*							m_pActiveFile;
	bxcf::CVectorPool<CEditorTab*>		m_vecTabs;
};

#endif