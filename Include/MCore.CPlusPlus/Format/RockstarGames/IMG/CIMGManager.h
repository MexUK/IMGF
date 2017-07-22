#ifndef CIMGManager_H
#define CIMGManager_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CIMGFormat.h"
#include "Format/RAGE/CRageResourceType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxa::CIMGManager : public bxa::CFormatManager<bxa::CIMGFormat>, public bxa::CSingleton<bxa::CIMGManager>
{
public:
	CIMGManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::string					getIMGVersionName(bxa::eIMGVersion eVersion, bool bIsEncrypted = false);
	static std::string					getIMGVersionGames(bxa::eIMGVersion eVersion);
	static std::string					getIMGVersionNameWithGames(bxa::eIMGVersion eVersion, bool bIsEncrypted = false);
	static uint32						getIMGEntryCount(std::string& strIMGFilePath, bxa::eIMGVersion eIMGVersion = IMG_UNKNOWN);

	static bxa::eIMGVersion			detectIMGVersion(std::string& strIMGFilePath, std::string& strHeader16B = bxa::g_strBlankString, bool& bIsEncryptedOut = g_bDefaultBool);
	static bool							detectIMGEncryptionState(std::string& strIMGFilePath);

	static std::string					encryptVersion3IMGString(std::string strData);
	static std::string					decryptVersion3IMGString(std::string strData);

	static std::vector<std::string>		getDefaultGameIMGSubPaths(bxa::ePlatformedGame ePlatformedGameValue);

	static std::string					getCompressionTypeText(bxa::eCompressionAlgorithm eCompressionAlgorithmValue);
	static std::string					getEncryptionText(bool bIsEncrypted);

	CIMGFormat*							parseViaFile(std::string& strFilePath);
};

#endif