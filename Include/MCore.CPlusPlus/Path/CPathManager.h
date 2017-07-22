#ifndef CPathManager_H
#define CPathManager_H

#include "bxa.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class bxa::CPathManager
{
public:
	static std::string			getFileName(std::string& strPath);
	static std::string			getFolderName(std::string& strPath);
	static std::string			getDirectory(std::string& strPath);
	static std::string			removeFileName(std::string& strPath);
	static std::string			getFileExtension(std::string& strPath);
	static std::string			replaceFileExtension(std::string strPath, std::string strExtension);
	static std::string			replaceFileExtensionWithCase(std::string& strPath, std::string strExtension);
	static std::string			removeFileExtension(std::string& strPath);
	static std::string			addSlashToEnd(std::string& strPath);
	static std::string			removeSlashFromEnd(std::string& strPath);
	static std::string			addSlashToFront(std::string& strPath);
	static std::string			removeSlashFromFront(std::string& strPath);
	static std::string			getNextFileName(std::string& strFilePath, uint32 uiFilenameIndex, std::string strNextSuffix);
	static std::vector<std::string>	getUniqueFilePaths(std::vector<std::string>& vecFilePaths, std::vector<std::string>& vecFileNames);
	static bool					isModelExtension(std::string& strExtension);
	static bool					isTextureExtension(std::string& strExtension);
	static bool					isCollisionExtension(std::string& strExtension);
};

#endif