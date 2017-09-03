#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"

class bxgi::IMGEntry;
class imgf::IMGEditorTab;

class imgf::SearchEntry
{
public:
	SearchEntry(void);

	void						setWindowTab(IMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	IMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxgi::IMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxgi::IMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	IMGEditorTab*				m_pEditorTab;
	bxgi::IMGEntry*					m_pIMGEntry;
};