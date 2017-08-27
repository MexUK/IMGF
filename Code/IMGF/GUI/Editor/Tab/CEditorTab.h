#pragma once

#include "Type/Types.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Layer/CLayer.h"
#include <string>

class CEditor;
class bxcf::CFormat;
class bxgx::CTabBarControlEntry;

class CEditorTab : public bxgx::CLayer
{
public:
	CEditorTab(void);

	void						unload(void) {}

	void						setEditor(CEditor* pEditor) { m_pEditor = pEditor; }
	CEditor*					getEditor(void) { return m_pEditor; }

	void						setTab(bxgx::CTabBarControlEntry *pTab) { m_pTab = pTab; }
	bxgx::CTabBarControlEntry*	getTab(void) { return m_pTab; }

	uint32						getTabIndex(void);

	void						setFile(bxcf::CFormat *pFile) { m_pFile = pFile; }
	bxcf::CFormat*				getFile(void) { return m_pFile; }

	virtual void				addControls(void) = 0;
	virtual void				initControls(void) = 0;

	void						log(std::string strText);
	void						logf(std::string strFormatText, ...);

private:
	CEditor*					m_pEditor;
	bxgx::CTabBarControlEntry*	m_pTab;
	bxcf::CFormat*				m_pFile;
};