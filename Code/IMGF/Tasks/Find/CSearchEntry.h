#pragma once

class CIMGEditorTab;
class bxgi::CIMGEntry;

class CSearchEntry
{
public:
	CSearchEntry(void) :
		m_pEditorTab(nullptr),
		m_pIMGEntry(nullptr)
	{};

	void						setWindowTab(CIMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	CIMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxgi::CIMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxgi::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	CIMGEditorTab*				m_pEditorTab;
	bxgi::CIMGEntry*					m_pIMGEntry;
};