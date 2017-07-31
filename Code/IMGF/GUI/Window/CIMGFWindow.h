#ifndef CIMGFWindow_H
#define CIMGFWindow_H

#include "Window/CWindow.h"
#include <string>
#include <vector>

class CMainLayer;
class CEditor;
class CIMGEditor;

class CIMGFWindow : public CWindow
{
public:
	CIMGFWindow(void);

	void					init(void);

	void					bindEvents(void);

	void					addEditor(CEditor *pEditor);

	void					onRender(void);

	void					onDropFiles(std::vector<std::string>& vecPaths);

public:
	CMainLayer*				m_pMainLayer;
	CIMGEditor*				m_pIMGEditor;

private:
	void					initWindow(void);
	void					initMainLayer(void);
	void					initEditors(void);

	void					renderTitleBar(void);
	void					renderEtc(void);
};

#endif