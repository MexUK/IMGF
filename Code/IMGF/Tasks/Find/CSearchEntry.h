#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"

class bxgi::CIMGEntry;
class imgf::CIMGEditorTab;

class imgf::CSearchEntry
{
public:
	CSearchEntry(void);

	void						setWindowTab(CIMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	CIMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxgi::CIMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxgi::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	CIMGEditorTab*				m_pEditorTab;
	bxgi::CIMGEntry*					m_pIMGEntry;
};