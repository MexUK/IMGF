#pragma once

#include "nsimgf.h"
#include "Layer/CLayer.h"
#include "Pool/CVectorPool.h"
#include "GUI/Editor/Tab/CEditorTab.h"
#include <string>

class bxgx::CTabBar;

class imgf::CEditor : public bxgx::CLayer
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

	void								setTabBar(bxgx::CTabBar *pTabBar) { m_pTabBar = pTabBar; }
	bxgx::CTabBar*				getTabBar(void) { return m_pTabBar; }

	void								updateActiveFileDisplayedInfo(void);
	void								clearActiveFileDisplayedInfo(void);

	virtual void						setFileInfoText(CEditorTab *pEditorFile) = 0;
	virtual void						clearFileInfoText(void) = 0;

	virtual std::string					getResolvedFilePath(std::string& strFilePath) { return strFilePath; } // file name or file path

protected:
	bxgx::CTabBar*				m_pTabBar;
	CEditorTab*							m_pActiveFile;
	bxcf::CVectorPool<CEditorTab*>		m_vecTabs;
};