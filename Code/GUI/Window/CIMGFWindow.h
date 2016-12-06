#ifndef CIMGFWindow_H
#define CIMGFWindow_H

#include "Window/CWindow.h"
#include <string>
#include <vector>

class CIMGFWindow : public CWindow
{
public:
	CIMGFWindow(void);

	void					initTabs(void);

	void					bindEvents(void);

	void					onRender(void);

	void					onDropFiles(std::vector<std::string>& vecPaths);

private:

	void					renderTitleBar(void);
	void					renderEtc(void);
};

#endif