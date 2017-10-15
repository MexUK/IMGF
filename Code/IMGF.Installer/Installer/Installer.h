#pragma once

#include <string>
#include "Window/Window.h"
#include "Event/EventBindable.h"
#include "InstallerFiles.h"
#include "../../../Compiler/Projects/IMGF.Installer/resource.h"
#include <Windows.h>

class Installer : public bxcf::EventBindable
{
public:
	Installer(void);

	InstallerFiles*			getInstallerFiles(void) { return m_pInstallerFiles; }

	void					init(void);

	void					openWindow(void);
	
	void					process(void);

	void					log(std::string strText);

private:
	void					initTheme(void);

	void					onPressButton(bxgx::Button *pButton);

	void					install(void);

	void					createFiles(void);
	void					addDesktopIcon(void);
	void					addToStartMenu(void);
	void					associateFileExtensions(void);

	void					createFile(HMODULE hModule, int iResourceId, std::string strFilePath);

private:
	InstallerFiles*			m_pInstallerFiles;

	bxgx::Window*			m_pWindow;

	bxgx::TextBox*			m_pLog;

	bxgx::Button*			m_pButton1;
	bxgx::Button*			m_pButton2;
	bxgx::Button*			m_pButton3_1;
	bxgx::Button*			m_pButton3_2;

	std::string				m_strIMGFFileName;
};