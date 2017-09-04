#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "ECOLVersion.h"
#include "CCOLVersion.h"
#include "Game/EPlatformedGame.h"
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

	static ECOLVersion		getCOLVersionFromFourCC(std::string strFourCC);
	static std::string		getFourCCFromCOLVersion(ECOLVersion ECOLVersionValue);

	static std::string		getCOLVersionText(ECOLVersion ECOLVersionValue);
	static std::string		getCOLVersionText(CCOLVersion* pCOLVersion) { return getCOLVersionText(pCOLVersion->getVersionId()); }

	static uint32			getEntryHeaderSizeForPacking(ECOLVersion ECOLVersionValue);

	static bool				isCollisionExtension(std::string& strFileExtension);

private:
	bxgi::CCOLVersionManager*		m_pVersionManager;
	
	//std::unordered_map<EPlatformedGame, std::unordered_map<std::string, uint32>> umapGameMaterialIds; // todo
};