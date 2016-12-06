#include "CSocketUtility.h"
#include "Type/String/CString2.h"

using namespace std;
using namespace mcore;

CURLComponents			CSocketUtility::getURLComponents(string strURL)
{
	CURLComponents url;
	size_t uiPos;

	// protocol
	uiPos = strURL.find_first_of("://");
	if (uiPos == string::npos)
	{
		url.m_strProtocol = "http";
	}
	else
	{
		url.m_strProtocol = strURL.substr(0, uiPos);
		strURL = strURL.substr(uiPos + 3);
	}

	// hash
	uiPos = strURL.find_last_of("#");
	if (uiPos == string::npos)
	{
		url.m_strHash = "";
	}
	else
	{
		url.m_strHash = strURL.substr(uiPos + 1);
		strURL = strURL.substr(0, uiPos);
	}

	// query
	uiPos = strURL.find_last_of("?");
	if (uiPos == string::npos)
	{
		url.m_strQuery = "";
	}
	else
	{
		url.m_strQuery = strURL.substr(uiPos + 1);
		strURL = strURL.substr(0, uiPos);
	}

	// path
	uiPos = strURL.find_first_of("/");
	if (uiPos == string::npos)
	{
		url.m_strPath = "/";
	}
	else
	{
		url.m_strPath = strURL.substr(uiPos);
		strURL = strURL.substr(0, uiPos);
	}

	// port
	uiPos = strURL.find_first_of(":");
	if (uiPos == string::npos)
	{
		url.m_usPort = 80;
	}
	else
	{
		url.m_usPort = CString2::toNumber(strURL.substr(uiPos + 1));
		strURL = strURL.substr(0, uiPos);
	}

	// domains
	url.m_strDomains = strURL;

	return url;
}