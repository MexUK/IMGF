#ifndef CEditorTab_H
#define CEditorTab_H

#include "Type/Types.h"
#include "bxcf.h"
#include "Layer/CGUILayer.h"
#include <string>

class CEditor;
class bxcf::CFormat;
class CTabBarControlEntry;

class CEditorTab : public CGUILayer
{
public:
	CEditorTab(void);

	void						unload(void) {}

	void						setEditor(CEditor* pEditor) { m_pEditor = pEditor; }
	CEditor*					getEditor(void) { return m_pEditor; }

	void						setTab(CTabBarControlEntry *pTab) { m_pTab = pTab; }
	CTabBarControlEntry*		getTab(void) { return m_pTab; }

	uint32						getTabIndex(void);

	void						setFile(bxcf::CFormat *pFile) { m_pFile = pFile; }
	bxcf::CFormat*				getFile(void) { return m_pFile; }

	virtual void				addControls(void) = 0;
	virtual void				initControls(void) = 0;

	void						log(std::string strText);
	void						logf(std::string strFormatText, ...);

private:
	CEditor*					m_pEditor;
	CTabBarControlEntry*		m_pTab;
	bxcf::CFormat*				m_pFile;
};

#endif