#ifndef CEditor_H
#define CEditor_H

#include "Layer/CGUILayer.h"
#include "Pool/CVectorPool.h"
#include "GUI/Editor/Tab/CEditorTab.h"

class CIMGFWindow;

class CEditor : public CGUILayer
{
public:
	CEditor(void);

	CIMGFWindow*					getWindow(void) { return (CIMGFWindow*) CGUILayer::getWindow(); }

	void						setActiveTab(CEditorTab *pActiveTab) { m_pActiveTab = pActiveTab; }
	CEditorTab*					getActiveTab(void) { return m_pActiveTab; }

	bxa::CVectorPool<CEditorTab*>&	getTabs(void) { return m_vecTabs; }

private:
	CEditorTab*					m_pActiveTab;
	bxa::CVectorPool<CEditorTab*>	m_vecTabs;
};

#endif