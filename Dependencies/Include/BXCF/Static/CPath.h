#ifndef CPath_H
#define CPath_H

#include "bxcf.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class bxcf::CPath
{
public:
	static std::string			getFileName(std::string strPath);
	static std::string			getFolderName(std::string& strPath);
	static std::string			getDirectory(std::string strPath);
	static std::string			removeFileName(std::string strPath);
	static std::string			removeFolderName(std::string& strPath);
	static std::string			replaceFolderName(std::string& strPath, std::string& strNewFolderName);
	static std::string			replaceFileName(std::string& strPath, std::string& strNewFileName);
	static std::string			getFileExtension(std::string& strPath);
	static std::string			replaceFileExtension(std::string strPath, std::string strExtension);
	static std::string			replaceFileExtensionWithCase(std::string& strPath, std::string strExtension);
	static std::string			removeFileExtension(std::string& strPath);
	static bool					isValidPath(std::string& strPath);
	static bool					isSlashAtEnd(std::string& strPath);
	static std::string			addSlashToEnd(std::string& strPath);
	static std::string			removeSlashFromEnd(std::string& strPath);
	static std::string			addSlashToFront(std::string& strPath);
	static std::string			removeSlashFromFront(std::string& strPath);
	static std::string			getNextFileName(std::string& strFilePath, uint32 uiFilenameIndex, std::string strNextSuffix);
	static std::vector<std::string>	getUniqueFilePaths(std::vector<std::string>& vecFilePaths, std::vector<std::string>& vecFileNames);
};

#endif