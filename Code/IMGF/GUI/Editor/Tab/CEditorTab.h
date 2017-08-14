#ifndef CEditorTab_H
#define CEditorTab_H

#include "Type/Types.h"
#include "bxcf.h"
#include <string>

class CEditor;
class bxcf::CFormat;

class CEditorTab
{
public:
	CEditorTab(void);

	void						unload(void) {}

	void						setEditor(CEditor* pEditor) { m_pEditor = pEditor; }
	CEditor*					getEditor(void) { return m_pEditor; }

	void						setIndex(uint32 uiIndex) { m_uiIndex = uiIndex; }
	uint32						getIndex(void) { return m_uiIndex; }

	void						setFile(bxcf::CFormat *pFormat) { m_pFormat = pFormat; }
	bxcf::CFormat*				getFile(void) { return m_pFormat; }

	void						log(std::string strText);
	void						logf(std::string strFormatText, ...);

private:
	CEditor*					m_pEditor;
	uint32						m_uiIndex;
	bxcf::CFormat*				m_pFormat;
};

#endif