#ifndef CUpdateConnection_H
#define CUpdateConnection_H

#include <string>

class CUpdateConnection
{
public:
	void						unload(void) {}

	void						setIsAlpha(bool bIsAlpha) { m_bIsAlpha = bIsAlpha; }
	bool						isAlpha(void) { return m_bIsAlpha; }

	void						setLatestVersionURL(std::string strLatestVersionURL) { m_strLatestVersionURL = strLatestVersionURL; }
	std::string					getLatestVersionURL(void) { return m_strLatestVersionURL; }

	void						setDownloadFolderURL(std::string strDownloadFolderURL) { m_strDownloadFolderURL = strDownloadFolderURL; }
	std::string					getDownloadFolderURL(void) { return m_strDownloadFolderURL; }

	void						setProtocol(std::string strProtocol) { m_strProtocol = strProtocol; }
	std::string					getProtocol(void) { return m_strProtocol; }

private:
	bool						m_bIsAlpha;
	std::string					m_strLatestVersionURL;
	std::string					m_strDownloadFolderURL;
	std::string					m_strProtocol;
};

#endif