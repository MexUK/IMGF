#include "CInstallationMeta.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CRegistry.h"
#include <Shlobj.h>
#include <sstream>

using namespace std;
using namespace bxcf;

string				CInstallationMeta::getProgramFilesPath(void)
{
	return CPath::addSlashToEnd(CRegistry::getSoftwareValueString("IMGF\\InternalSettings", "InstallationPath"));
}

string				CInstallationMeta::getLocalAppPath(void)
{
	wchar_t *pLocalAppDataFolderPath = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pLocalAppDataFolderPath);
	wstringstream ss;
	ss << pLocalAppDataFolderPath;
	string strLocalAppFolderPath = CPath::addSlashToEnd(CString2::convertStdWStringToStdString(ss.str()));
	CoTaskMemFree(static_cast<void*>(pLocalAppDataFolderPath));
	return CPath::addSlashToEnd(strLocalAppFolderPath) + "IMGF/";
}