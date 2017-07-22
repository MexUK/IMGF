#ifndef CSearchEntry_H
#define CSearchEntry_H

class CIMGEditorTab;
class bxa::CIMGEntry;

class CSearchEntry
{
public:
	CSearchEntry(void) :
		m_pEditorTab(nullptr),
		m_pIMGEntry(nullptr)
	{};

	void						setWindowTab(CIMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	CIMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxa::CIMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxa::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	CIMGEditorTab*				m_pEditorTab;
	bxa::CIMGEntry*					m_pIMGEntry;
};

#endif