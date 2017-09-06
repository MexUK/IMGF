#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include <string>

class imgf::Editor;
class bxcf::Format;
class bxgx::Tab;
class bxgx::TextBox;

class imgf::EditorTab : public bxgx::Layer
{
public:
	EditorTab(void);

	void								unload(void) {}

	void								setEditor(Editor* pEditor) { m_pEditor = pEditor; }
	Editor*								getEditor(void) { return m_pEditor; }

	void								setTab(bxgx::Tab *pTab) { m_pTab = pTab; }
	bxgx::Tab*							getTab(void) { return m_pTab; }

	uint32								getTabIndex(void);

	void								setFile(bxcf::Format *pFile) { m_pFile = pFile; }
	bxcf::Format*						getFile(void) { return m_pFile; }

	virtual void						addControls(void);
	virtual void						initControls(void);

	void								log(std::string strText);
	void								logf(std::string strFormatText, ...);

	bxcf::VectorPool<RenderItem*>		getRenderItems(void) { return m_vecRenderItems; }
	bxcf::VectorPool<std::string>		getLogLines(void) { return m_vecLogLines; }

private:
	Editor*								m_pEditor;
	bxgx::Tab*							m_pTab;
	bxcf::Format*						m_pFile;
	bxgx::TextBox*						m_pLog;
	bxcf::VectorPool<RenderItem*>		m_vecRenderItems;
	bxcf::VectorPool<std::string>		m_vecLogLines;
};