#ifndef CCOLManager_H
#define CCOLManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eCOLVersion.h"
#include "CCOLVersion.h"
#include "Collection/Games/ePlatformedGame.h"
#include "CCOLEntry.h"
#include <string>
#include <unordered_map>

class bxa::CCOLFormat;
class bxa::CCOLVersionManager;

class bxa::CCOLManager : public bxa::CFormatManager<bxa::CCOLFormat>, public bxa::CSingleton<bxa::CCOLManager>
{
public:
	CCOLManager(void);
	~CCOLManager(void);

	void					init(void);
	void					uninit(void);

	void					initGameMaterials(void);

	bxa::CCOLVersionManager*		getVersionManager(void) { return m_pVersionManager; }

	static CCOLVersion*		getCOLVersionFromFourCC(std::string strFourCC);
	static std::string		getFourCCFromCOLVersion(eCOLVersion eCOLVersionValue);

	static std::string		getCOLVersionText(eCOLVersion eCOLVersionValue);
	static std::string		getCOLVersionText(CCOLVersion* pCOLVersion) { return getCOLVersionText(pCOLVersion->getVersionId()); }

	static uint32			getEntryHeaderSizeForPacking(eCOLVersion eCOLVersionValue);

private:
	bxa::CCOLVersionManager*		m_pVersionManager;
	
	//std::unordered_map<ePlatformedGame, std::unordered_map<std::string, uint32>> umapGameMaterialIds; // todo
};

#endif