#include "UpdateConnectionManager.h"

using namespace bxcf;
using namespace imgf;

void			UpdateConnectionManager::init(void)
{
	initUpdateConnections();
}
void			UpdateConnectionManager::uninit(void)
{
	uninitUpdateConnections();
}

void			UpdateConnectionManager::initUpdateConnections(void)
{
	UpdateConnection *pUpdateConnection = nullptr;

	/*
	// test domain
	pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setIsAlpha(true);
	pUpdateConnection->setLatestVersionURL("http://sfdmjidurgh8dehiuhsdufgseiufhesw8fhduhszd.com/feadfsezf.txt");
	pUpdateConnection->setDownloadFolderURL("http://sfdmjidurgh8dehiuhsdufgseiufhesw8fhduhszd.com/nightly-sdfndsunhuisefudihusf/");
	addEntry(pUpdateConnection);
	*/

	// mvec.io
	pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setIsAlpha(true);
	pUpdateConnection->setLatestVersionURL("http://updater.imgfactory.mvec.io/nightly-latest-version.txt");
	pUpdateConnection->setDownloadFolderURL("http://updater.imgfactory.mvec.io/nightly-4509gfvcnr439eurgdn3fdd/");
	addEntry(pUpdateConnection);

	pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setIsAlpha(false);
	pUpdateConnection->setLatestVersionURL("http://updater.imgfactory.mvec.io/latest-version.txt");
	pUpdateConnection->setDownloadFolderURL("http://updater.imgfactory.mvec.io/versions/");
	addEntry(pUpdateConnection);

	// ukscifi.net
	pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setIsAlpha(true);
	pUpdateConnection->setLatestVersionURL("http://www.ukscifi.net/imgfactory/nightly-latest-version.txt");
	pUpdateConnection->setDownloadFolderURL("http://www.ukscifi.net/imgfactory/nightly-51s5165td1za3fg3fg3e16yun1/");
	addEntry(pUpdateConnection);

	pUpdateConnection = new UpdateConnection;
	pUpdateConnection->setIsAlpha(false);
	pUpdateConnection->setLatestVersionURL("http://www.ukscifi.net/imgfactory/latest-version.txt");
	pUpdateConnection->setDownloadFolderURL("http://www.ukscifi.net/imgfactory/versions/");
	addEntry(pUpdateConnection);
}

void			UpdateConnectionManager::uninitUpdateConnections(void)
{
	removeAllEntries();
}