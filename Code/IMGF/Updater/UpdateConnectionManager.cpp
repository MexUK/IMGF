#include "UpdateConnectionManager.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

// initialization
void							UpdateConnectionManager::init(void)
{
	initUpdateConnections();
}
void							UpdateConnectionManager::uninit(void)
{
	uninitUpdateConnections();
}

void							UpdateConnectionManager::initUpdateConnections(void)
{
	addConnection("http://updater.imgfactory.mvec.io/imgf-builds/latest-version.txt", "http://updater.imgf.mvec.io/imgf-builds/versions/");
	addConnection("http://www.ukscifi.net/imgfactory/latest-version.txt", "http://www.ukscifi.net/imgfactory/versions/");
}

void							UpdateConnectionManager::uninitUpdateConnections(void)
{
	removeAllEntries();
}

// add/remove connection
UpdateConnection*				UpdateConnectionManager::addConnection(string strLatestVersionURL, string strBuildsFolderURL)
{
	UpdateConnection *pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setLatestVersionURL(strLatestVersionURL);
	pUpdateConnection->setDownloadFolderURL(strBuildsFolderURL);
	addEntry(pUpdateConnection);
	return pUpdateConnection;
}