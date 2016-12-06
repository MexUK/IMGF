#ifndef CEditorTab_H
#define CEditorTab_H

#include "Type/Types.h"

class CEditor;

class CEditorTab
{
public:
	CEditorTab(void);

	void						unload(void) {}

	void						setEditor(CEditor* pEditor) { m_pEditor = pEditor; }
	CEditor*					getEditor(void) { return m_pEditor; }

	void						setIndex(uint32 uiIndex) { m_uiIndex = uiIndex; }
	uint32						getIndex(void) { return m_uiIndex; }

private:
	CEditor*					m_pEditor;
	uint32						m_uiIndex;
};

#endif