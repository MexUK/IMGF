#ifndef CIMGManager_H
#define CIMGManager_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CIMGFormat.h"
#include "Format/RAGE/CRageResourceType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxcf::CIMGManager : public bxcf::CFormatManager<bxcf::CIMGFormat>, public bxcf::CSingleton<bxcf::CIMGManager>
{
public:
	CIMGManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::string					getVersionName(bxcf::eIMGVersion eVersion, bool bIsEncrypted = false);
	static std::string					getVersionGames(bxcf::eIMGVersion eVersion);
	static std::string					getVersionNameWithGames(bxcf::eIMGVersion eVersion, bool bIsEncrypted = false);
	static uint32						getIMGEntryCount(std::string& strIMGFilePath, bxcf::eIMGVersion eIMGVersion = IMG_UNKNOWN);

	static bxcf::eIMGVersion			detectIMGVersion(std::string& strIMGFilePath, std::string& strHeader16B = bxcf::g_strBlankString, bool& bIsEncryptedOut = g_bDefaultBool);
	static bool							detectIMGEncryptionState(std::string& strIMGFilePath);

	static std::string					encryptVersion3IMGString(std::string strData);
	static std::string					decryptVersion3IMGString(std::string strData);

	static std::vector<std::string>		getDefaultGameIMGSubPaths(bxcf::ePlatformedGame ePlatformedGameValue);

	static std::string					getCompressionTypeText(bxcf::eCompressionAlgorithm eCompressionAlgorithmValue);
	static std::string					getEncryptionText(bool bIsEncrypted);

	CIMGFormat*							parseViaFile(std::string& strFilePath);
};

#endif