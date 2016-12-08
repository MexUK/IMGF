#ifndef CCOLManager_H
#define CCOLManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eCOLVersion.h"
#include "CCOLVersion.h"
#include "Collection/Games/ePlatformedGame.h"
#include "CCOLEntry.h"
#include <string>
#include <unordered_map>

class mcore::CCOLFormat;
class mcore::CCOLVersionManager;

class mcore::CCOLManager : public mcore::CFormatManager<mcore::CCOLFormat>, public mcore::CSingleton<mcore::CCOLManager>
{
public:
	CCOLManager(void);
	~CCOLManager(void);

	void					init(void);
	void					uninit(void);

	void					initGameMaterials(void);

	mcore::CCOLVersionManager*		getVersionManager(void) { return m_pVersionManager; }

	static CCOLVersion*		getCOLVersionFromFourCC(std::string strFourCC);
	static std::string		getFourCCFromCOLVersion(eCOLVersion eCOLVersionValue);

	static std::string		getCOLVersionText(eCOLVersion eCOLVersionValue);
	static std::string		getCOLVersionText(CCOLVersion* pCOLVersion) { return getCOLVersionText(pCOLVersion->getVersionId()); }

	static uint32			getEntryHeaderSizeForPacking(eCOLVersion eCOLVersionValue);

private:
	mcore::CCOLVersionManager*		m_pVersionManager;
	
	//std::unordered_map<ePlatformedGame, std::unordered_map<std::string, uint32>> umapGameMaterialIds; // todo
};

#endif