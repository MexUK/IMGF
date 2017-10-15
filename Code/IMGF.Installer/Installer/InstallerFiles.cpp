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
}