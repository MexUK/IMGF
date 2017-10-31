#include "FileGroup.h"
#include "Static/String.h"
#include "Globals.h"
#include "IMGF.h"
#include "FileGroupManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

// serialize
string			FileGroup::serialize(void)
{
	return m_strName + "; " + String::join(m_vecPaths, "; ");
}

// serialize to file
void			FileGroup::serializeToFile(void)
{
	uint32 uiSessionIndex = getIMGF()->getFileGroupManager()->getIndexByEntry(this);
	INIManager::setItem(AppDataPath::getFileGroupsPath(), "FileGroups", uiSessionIndex, serialize());
}

// name
void			FileGroup::setName(string strSessionName)
{
	m_strName = strSessionName;
	serializeToFile();
}

// paths
void			FileGroup::setPaths(vector<string> vecPaths)
{
	m_vecPaths = vecPaths;
	serializeToFile();
}