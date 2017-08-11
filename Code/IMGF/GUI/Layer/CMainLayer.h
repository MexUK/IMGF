#pragma once

#include "Layer/CGUILayer.h"

class CIMGFWindow;
class CProgressControl;
class CTextBoxControl;
class CDropControl;

class CMainLayer : public CGUILayer
{
public:
	void						init(void);

	void						setIMGFWindow(CIMGFWindow* pIMGFWindow) { m_pIMGFWindow = pIMGFWindow; }
	CIMGFWindow*				getIMGFWindow(void) { return m_pIMGFWindow; }

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(void);

private:
	CIMGFWindow*				m_pIMGFWindow;
	CProgressControl*			m_pProgressBar;
	CTextBoxControl*			m_pSearchBox;
	CDropControl*				m_pEntryTypeFilter;
	CDropControl*				m_pEntryVersionFilter;
};