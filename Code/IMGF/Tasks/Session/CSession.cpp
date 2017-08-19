#include "CSession.h"
#include "Static/CString2.h"
#include "Static/CRegistry.h"
#include "Globals.h"
#include "CIMGF.h"
#include "CSessionManager.h"
#include "Format/IMG/Regular/CIMGEntry.h"

using namespace std;
using namespace bxcf;

string			CSession::serialize(void)
{
	return m_strName + "; " + CString2::join(m_vecPaths, "; ");
}

void			CSession::setName(string strSessionName)
{
	m_strName = strSessionName;
	uint32 uiSessionIndex = getIMGF()->getSessionManager()->getIndexByEntry(this);
	CRegistry::setSoftwareValueString("IMGF\\Sessions", "Data_" + CString2::toString(uiSessionIndex), serialize());
}

void			CSession::setPaths(vector<string> vecPaths)
{
	m_vecPaths = vecPaths;
	uint32 uiSessionIndex = getIMGF()->getSessionManager()->getIndexByEntry(this);
	CRegistry::setSoftwareValueString("IMGF\\Sessions", "Data_" + CString2::toString(uiSessionIndex), serialize());
}