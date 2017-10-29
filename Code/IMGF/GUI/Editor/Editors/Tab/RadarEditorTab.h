#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::RadarEditorTab : public imgf::EditorTab
{
public:
	RadarEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						render_Type1(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);

	void						setIMGFile(bxgi::IMGFormat *pIMGFile) { m_pIMGFile = pIMGFile; }
	bxgi::IMGFormat*			getIMGFile(void) { return m_pIMGFile; }

private:
	bxgi::IMGFormat*			m_pIMGFile;
};