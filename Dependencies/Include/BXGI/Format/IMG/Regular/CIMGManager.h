#ifndef CIMGManager_H
#define CIMGManager_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CIMGFormat.h"
#include "Engine/RAGE/CRageResourceType.h"
#include "Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxgi::CIMGManager : public bxcf::CFormatManager<bxgi::CIMGFormat>, public bxcf::CSingleton<bxgi::CIMGManager>
{
public:
	CIMGManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::string					getVersionName(bxgi::eIMGVersion eVersion, bool bIsEncrypted = false);
	static std::string					getVersionGames(bxgi::eIMGVersion eVersion);
	static std::string					getVersionNameWithGames(bxgi::eIMGVersion eVersion, bool bIsEncrypted = false);
	static uint32						getIMGEntryCount(std::string& strIMGFilePath, bxgi::eIMGVersion eIMGVersion = IMG_UNKNOWN);

	static bxgi::eIMGVersion			detectIMGVersion(std::string& strIMGFilePath, std::string& strHeader16B = bxcf::g_strBlankString, bool& bIsEncryptedOut = bxcf::g_bDefaultBool);
	static bool							detectIMGEncryptionState(std::string& strIMGFilePath);

	static std::string					encryptVersion3IMGString(std::string strData);
	static std::string					decryptVersion3IMGString(std::string strData);

	static std::vector<std::string>		getDefaultGameIMGSubPaths(bxgi::ePlatformedGame ePlatformedGameValue);

	static std::string					getCompressionTypeText(bxcf::eCompressionAlgorithm eCompressionAlgorithmValue);
	static std::string					getEncryptionText(bool bIsEncrypted);

	CIMGFormat*							parseViaFile(std::string& strFilePath);
};

#endif