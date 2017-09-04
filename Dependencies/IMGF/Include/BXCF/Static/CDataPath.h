#pragma once

#include "nsbxcf.h"
#include <string>

class bxcf::CDataPath
{
public:
	static std::string			getLocalAppDataPath(void);		// e.g. "C:/Users/James/AppData/Local/"
	static std::string			getDataPath(void);				// e.g. "C:/Users/James/AppData/Local/IMGFactory/"

	static void					setAppFolderName(std::string strAppFolderName);		// e.g. strAppFolderName&:	"IMGFactory"
	static std::string&			getAppFolderName(void);								// e.g. return:				"IMGFactory"

	static void					setOpenFilePath(std::string& strKey, std::string& strFilePath);		// e.g. strKey&:	"openBMP",		strFilePath&:		<user chosen file>
	static std::string			getOpenFilePath(std::string& strKey);								// e.g. strKey&:	"openBMP",		return:				<user chosen file>

	static void					setSaveFilePath(std::string& strKey, std::string& strFilePath);		// e.g. strKey&:	"saveBMP",		strFilePath&:		<user chosen file>
	static std::string			getSaveFilePath(std::string& strKey);								// e.g. strKey&:	"saveBMP",		return:				<user chosen file>

	static void					setOpenFolderPath(std::string& strKey, std::string& strFolderPath);	// e.g. strKey&:	"openSession",	strFolderPath&:		<user chosen folder>
	static std::string			getOpenFolderPath(std::string& strKey);								// e.g. strKey&:	"openSession",	return:				<user chosen folder>

	static void					setSaveFolderPath(std::string& strKey, std::string& strFolderPath);	// e.g. strKey&:	"saveSession",	strFolderPath&:		<user chosen folder>
	static std::string			getSaveFolderPath(std::string& strKey);								// e.g. strKey&:	"saveSession",	return:				<user chosen folder>

private:
	static std::string			getPathForOpenFilePaths(void);
	static std::string			getPathForSaveFilePaths(void);
	static std::string			getPathForOpenFolderPaths(void);
	static std::string			getPathForSaveFolderPaths(void);

private:
	static std::string			m_strAppFolderName;				// e.g. "IMGFactory"

public:
	static const std::string	FOLDER_SEPARATOR;				// e.g. "\"

private:
	static const std::string	OPEN_FILE_PATHS_SECTION;		// e.g. "OpenFilePaths"
	static const std::string	SAVE_FILE_PATHS_SECTION;		// e.g. "SaveFilePaths"
	static const std::string	OPEN_FOLDER_PATHS_SECTION;		// e.g. "OpenFolderPaths"
	static const std::string	SAVE_FOLDER_PATHS_SECTION;		// e.g. "SaveFolderPaths"

	static const std::string	RELATIVE_PATHS_FOLDER;			// e.g. "Input"
};