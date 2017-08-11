#ifndef CEditor_H
#define CEditor_H

#include "Layer/CGUILayer.h"
#include "Pool/CVectorPool.h"
#include "GUI/Editor/Tab/CEditorTab.h"

class CMainWindow;

class CEditor : public CGUILayer
{
public:
	CEditor(void);

	virtual void						init(void) = 0;

	CMainWindow*						getWindow(void) { return (CMainWindow*) CGUILayer::getWindow(); }

	void								setActiveTab(CEditorTab *pActiveTab) { m_pActiveTab = pActiveTab; }
	CEditorTab*							getActiveTab(void) { return m_pActiveTab; }

	bxcf::CVectorPool<CEditorTab*>&		getTabs(void) { return m_vecTabs; }

private:
	CEditorTab*							m_pActiveTab;
	bxcf::CVectorPool<CEditorTab*>		m_vecTabs;
};

#endif