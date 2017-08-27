#include "CSession.h"
#include "Static/CString2.h"
#include "Globals.h"
#include "IMGF.h"
#include "CSessionManager.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Format/Text/INI/CINIManager.h"
#include "Static/CAppDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

// serialize
string			CSession::serialize(void)
{
	return m_strName + "; " + CString2::join(m_vecPaths, "; ");
}

// serialize to file
void			CSession::serializeToFile(void)
{
	uint32 uiSessionIndex = getIMGF()->getSessionManager()->getIndexByEntry(this);
	CINIManager::setItem(CAppDataPath::getSessionsPath(), "Sessions", uiSessionIndex, serialize());
}

// name
void			CSession::setName(string strSessionName)
{
	m_strName = strSessionName;
	serializeToFile();
}

// paths
void			CSession::setPaths(vector<string> vecPaths)
{
	m_vecPaths = vecPaths;
	serializeToFile();
}