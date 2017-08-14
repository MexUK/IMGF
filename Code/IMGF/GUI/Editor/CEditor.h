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

	void								addTab(CEditorTab *pEditorTab);

	bxcf::CVectorPool<CEditorTab*>&		getTabs(void) { return m_vecTabs; }

	void								setActiveTab(CEditorTab *pActiveTab) { m_pActiveTab = pActiveTab; }
	CEditorTab*							getActiveTab(void) { return m_pActiveTab; }

	void								setTabBar(CTabBarControl *pTabBar) { m_pTabBar = pTabBar; }
	CTabBarControl*						getTabBar(void) { return m_pTabBar; }

protected:
	CTabBarControl*						m_pTabBar;
	CEditorTab*							m_pActiveTab;
	bxcf::CVectorPool<CEditorTab*>		m_vecTabs;
};

#endif