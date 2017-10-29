#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::ModelEditorTab : public imgf::EditorTab
{
public:
	ModelEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						render_Type1(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);

	void						setDFFFile(bxgi::DFFFormat *pDFFFile) { m_pDFFFile = pDFFFile; }
	bxgi::DFFFormat*			getDFFFile(void) { return m_pDFFFile; }

private:
	bxgi::DFFFormat*			m_pDFFFile;
};