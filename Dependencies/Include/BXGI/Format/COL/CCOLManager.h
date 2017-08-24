#ifndef CCOLManager_H
#define CCOLManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eCOLVersion.h"
#include "CCOLVersion.h"
#include "Games/ePlatformedGame.h"
#include <string>
#include <unordered_map>

class bxgi::CCOLFormat;
class bxgi::CCOLVersionManager;

class bxgi::CCOLManager : public bxcf::CFormatManager<bxgi::CCOLFormat>, public bxcf::CSingleton<bxgi::CCOLManager>
{
public:
	CCOLManager(void);
	~CCOLManager(void);

	void					init(void);
	void					uninit(void);

	void					initGameMaterials(void);

	bxgi::CCOLVersionManager*		getVersionManager(void) { return m_pVersionManager; }

	static CCOLVersion*		getCOLVersionFromFourCC(std::string strFourCC);
	static std::string		getFourCCFromCOLVersion(eCOLVersion eCOLVersionValue);

	static std::string		getCOLVersionText(eCOLVersion eCOLVersionValue);
	static std::string		getCOLVersionText(CCOLVersion* pCOLVersion) { return getCOLVersionText(pCOLVersion->getVersionId()); }

	static uint32			getEntryHeaderSizeForPacking(eCOLVersion eCOLVersionValue);

	static bool				isCollisionExtension(std::string& strFileExtension);

private:
	bxgi::CCOLVersionManager*		m_pVersionManager;
	
	//std::unordered_map<ePlatformedGame, std::unordered_map<std::string, uint32>> umapGameMaterialIds; // todo
};

#endif