#pragma once

#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::MainWindow;
class bxgx::ProgressBar;
class bxgx::TextBox;

class imgf::MainLayerNoTabsOpen : public bxgx::Layer, public bxcf::EventBindable
{
public:
	MainLayerNoTabsOpen(void);

	void								init(void);

	void								addControls(void);
	void								initControls(void);
	void								repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void								setIMGFWindow(MainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	MainWindow*							getIMGFWindow(void) { return m_pMainWindow; }

	bxgx::ProgressBar*					getProgressBar(void) { return m_pProgressBar; }
	bxgx::TextBox*						getSearchBox(void) { return m_pSearchBox; }
	bxgx::TextBox*						getLog(void) { return m_pLog; }

private:
	imgf::MainWindow*					m_pMainWindow;

	bxgx::ProgressBar*					m_pProgressBar;
	bxgx::TextBox*						m_pSearchBox;
	bxgx::TextBox*						m_pLog;
};