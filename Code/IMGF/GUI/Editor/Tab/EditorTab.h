#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include <string>

class imgf::Editor;
class bxcf::CFormat;
class bxgx::Tab;

class imgf::EditorTab : public bxgx::Layer
{
public:
	EditorTab(void);

	void						unload(void) {}

	void						setEditor(Editor* pEditor) { m_pEditor = pEditor; }
	Editor*					getEditor(void) { return m_pEditor; }

	void						setTab(bxgx::Tab *pTab) { m_pTab = pTab; }
	bxgx::Tab*	getTab(void) { return m_pTab; }

	uint32						getTabIndex(void);

	void						setFile(bxcf::CFormat *pFile) { m_pFile = pFile; }
	bxcf::CFormat*				getFile(void) { return m_pFile; }

	virtual void				addControls(void) = 0;
	virtual void				initControls(void) = 0;

	void						log(std::string strText);
	void						logf(std::string strFormatText, ...);

private:
	Editor*					m_pEditor;
	bxgx::Tab*	m_pTab;
	bxcf::CFormat*				m_pFile;
};