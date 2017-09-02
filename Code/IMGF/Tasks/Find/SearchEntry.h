#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"

class bxgi::CIMGEntry;
class imgf::IMGEditorTab;

class imgf::SearchEntry
{
public:
	SearchEntry(void);

	void						setWindowTab(IMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	IMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxgi::CIMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxgi::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	IMGEditorTab*				m_pEditorTab;
	bxgi::CIMGEntry*					m_pIMGEntry;
};