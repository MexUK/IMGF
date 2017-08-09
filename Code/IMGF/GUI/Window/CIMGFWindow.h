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

	void					addEditor(CEditor *pEditor);

public:
	CMainLayer*				m_pMainLayer;
	CIMGEditor*				m_pIMGEditor;

private:
	void					initWindow(void);
	void					initMainLayer(void);
	void					initEditors(void);
};

#endif