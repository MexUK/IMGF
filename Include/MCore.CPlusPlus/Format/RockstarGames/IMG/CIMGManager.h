#ifndef CIMGManager_H
#define CIMGManager_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CIMGFormat.h"
#include "Format/RAGE/CRageResourceType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class mcore::CIMGManager : public mcore::CFormatManager<mcore::CIMGFormat>, public mcore::CSingleton<mcore::CIMGManager>
{
public:
	CIMGManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::string					getIMGVersionName(mcore::eIMGVersion eVersion, bool bIsEncrypted = false);
	static std::string					getIMGVersionGames(mcore::eIMGVersion eVersion);
	static std::string					getIMGVersionNameWithGames(mcore::eIMGVersion eVersion, bool bIsEncrypted = false);
	static uint32						getIMGEntryCount(std::string& strIMGFilePath, mcore::eIMGVersion eIMGVersion = IMG_UNKNOWN);

	static mcore::eIMGVersion			detectIMGVersion(std::string& strIMGFilePath, std::string& strHeader16B = mcore::g_strBlankString, bool& bIsEncryptedOut = g_bDefaultBool);
	static bool							detectIMGEncryptionState(std::string& strIMGFilePath);

	static std::string					encryptVersion3IMGString(std::string strData);
	static std::string					decryptVersion3IMGString(std::string strData);

	static std::vector<std::string>		getDefaultGameIMGSubPaths(mcore::ePlatformedGame ePlatformedGameValue);

	static std::string					getCompressionTypeText(mcore::eCompressionAlgorithm eCompressionAlgorithmValue);
	static std::string					getEncryptionText(bool bIsEncrypted);

	CIMGFormat*							parseViaFile(std::string& strFilePath);
};

#endif