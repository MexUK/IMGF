#ifndef CSearchEntry_H
#define CSearchEntry_H

class CIMGEditorTab;
class bxcf::CIMGEntry;

class CSearchEntry
{
public:
	CSearchEntry(void) :
		m_pEditorTab(nullptr),
		m_pIMGEntry(nullptr)
	{};

	void						setWindowTab(CIMGEditorTab* pEditorTab) { m_pEditorTab = pEditorTab; }
	CIMGEditorTab*				getWindowTab(void) { return m_pEditorTab; }

	void						setIMGEntry(bxcf::CIMGEntry* pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxcf::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

private:
	CIMGEditorTab*				m_pEditorTab;
	bxcf::CIMGEntry*					m_pIMGEntry;
};

#endif