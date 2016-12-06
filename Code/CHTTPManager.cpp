#include "CHTTPManager.h"
#include "CSocketUtility.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Type/String/CString2.h"
#include "Debug/CDebug.h"
#include <WinSock2.h>

using namespace std;
using namespace mcore;

void				CHTTPManager::init(void)
{
}
void				CHTTPManager::uninit(void)
{
}

string				CHTTPManager::getFileContent(string strURL)
{
	CURLComponents url = CSocketUtility::getURLComponents(strURL);

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	happyhttp::Connection conn(url.m_strDomains.c_str(), url.m_usPort);
	try
	{
		conn.setcallbacks(OnBegin, OnData, OnComplete, 0);
		conn.request("GET", CString2::replace(url.m_strPath, " ", "%20").c_str(), 0, 0, 0);
	}
	catch (happyhttp::Wobbly error)
	{
		return "";
	};

	while (conn.outstanding())
	{
		conn.pump();
	}

	while (!m_bConnectionComplete)
	{
		Sleep(50);
	}

	return m_strReceivedData;
}

void		OnBegin(const happyhttp::Response* r, void* userdata)
{
	CHTTPManager::getInstance()->m_bConnectionComplete = false;
	CHTTPManager::getInstance()->m_strReceivedData = "";
}
void		OnData(const happyhttp::Response* r, void* userdata, const uint8* data, int n)
{
	CHTTPManager::getInstance()->m_strReceivedData.append((char*)data, n);
}
void		OnComplete(const happyhttp::Response* r, void* userdata)
{
	CHTTPManager::getInstance()->m_bConnectionComplete = true;
}