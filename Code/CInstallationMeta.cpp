#include "CInstallationMeta.h"
#include "Type/String/CString2.h"
#include "Path/CPathManager.h"
#include "Registry/CRegistryManager.h"
#include <Shlobj.h>
#include <sstream>

using namespace std;
using namespace mcore;

string				CInstallationMeta::getProgramFilesPath(void)
{
	return CPathManager::addSlashToEnd(CRegistryManager::getSoftwareValueString("IMGF\\InternalSettings", "InstallationPath"));
}

string				CInstallationMeta::getLocalAppPath(void)
{
	wchar_t *pLocalAppDataFolderPath = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pLocalAppDataFolderPath);
	wstringstream ss;
	ss << pLocalAppDataFolderPath;
	string strLocalAppFolderPath = CPathManager::addSlashToEnd(CString2::convertStdWStringToStdString(ss.str()));
	CoTaskMemFree(static_cast<void*>(pLocalAppDataFolderPath));
	return CPathManager::addSlashToEnd(strLocalAppFolderPath) + "IMGF/";
}