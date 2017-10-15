#include "InstallerFiles.h"
#include "InstallerFile.h"

using namespace std;

// add file
void					InstallerFiles::addFile(string strRelativeFilePath)
{
	InstallerFile *pInstallerFile = new InstallerFile;
	pInstallerFile->m_strRelativeFilePath = strRelativeFilePath;
	m_vecFiles.addEntry(pInstallerFile);
}

// load files
void					InstallerFiles::load(void)
{
	/*
	addFile("Images/Logo.png");
	
	addFile("Settings/RegularSettings.ini");
	
	addFile("Styles/Main (dark) - Copy.bxs");
	addFile("Styles/Main (dark).bxs");
	addFile("Styles/Main (orange and yellow).bxs");
	*/
	//addFile("Styles/Main.bxs");
	/*
	addFile("Styles/Main_black.bxs");
	addFile("Styles/Main_blue.bxs");
	addFile("Styles/Main_blueish.bxs");
	addFile("Styles/Main_Green.bxs");
	addFile("Styles/Main_LightGreen.bxs");
	addFile("Styles/Main_orange.bxs");
	addFile("Styles/Main_Purple.bxs");
	addFile("Styles/Main_red.bxs");
	addFile("Styles/Main-1 (grey).bxs");
	addFile("Styles/Main-2 (blue and yellow).bxs");
	*/
}