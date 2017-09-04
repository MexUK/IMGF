#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Game/EPlatformedGame.h"
#include <string>
#include <vector>

class bxgi::IMGManager : public bxcf::FormatManager<bxgi::IMGFormat>, public bxcf::Singleton<bxgi::IMGManager>
{
public:
	IMGManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::string					getVersionName(bxgi::EIMGVersion eVersion, bool bIsEncrypted = false);
	static std::string					getVersionGames(bxgi::EIMGVersion eVersion);
	static std::string					getVersionNameWithGames(bxgi::EIMGVersion eVersion, bool bIsEncrypted = false);
	static uint32						getIMGEntryCount(std::string& strIMGFilePath, bxgi::EIMGVersion EIMGVersion = IMG_UNKNOWN);

	static bxgi::EIMGVersion			detectIMGVersion(std::string& strIMGFilePath, std::string& strHeader16B = bxcf::g_strBlankString, bool& bIsEncryptedOut = bxcf::g_bDefaultBool);
	static bool							detectIMGEncryptionState(std::string& strIMGFilePath);

	static std::string					encryptVersion3IMGString(std::string strData);
	static std::string					decryptVersion3IMGString(std::string strData);

	static std::vector<std::string>		getDefaultGameIMGSubPaths(bxgi::EPlatformedGame EPlatformedGameValue);

	static std::string					getCompressionTypeText(bxcf::ECompressionAlgorithm ECompressionAlgorithmValue);
	static std::string					getEncryptionText(bool bIsEncrypted);

	IMGFormat*							parseViaFile(std::string& strFilePath);
};