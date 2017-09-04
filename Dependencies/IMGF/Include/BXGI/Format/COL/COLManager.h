#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "ECOLVersion.h"
#include "COLVersion.h"
#include "Game/EPlatformedGame.h"
#include <string>
#include <unordered_map>

class bxgi::COLFormat;
class bxgi::COLVersionManager;

class bxgi::COLManager : public bxcf::FormatManager<bxgi::COLFormat>, public bxcf::Singleton<bxgi::COLManager>
{
public:
	COLManager(void);
	~COLManager(void);

	void					init(void);
	void					uninit(void);

	void					initGameMaterials(void);

	bxgi::COLVersionManager*		getVersionManager(void) { return m_pVersionManager; }

	static ECOLVersion		getCOLVersionFromFourCC(std::string strFourCC);
	static std::string		getFourCCFromCOLVersion(ECOLVersion ECOLVersionValue);

	static std::string		getCOLVersionText(ECOLVersion ECOLVersionValue);
	static std::string		getCOLVersionText(COLVersion* pCOLVersion) { return getCOLVersionText(pCOLVersion->getVersionId()); }

	static uint32			getEntryHeaderSizeForPacking(ECOLVersion ECOLVersionValue);

	static bool				isCollisionExtension(std::string& strFileExtension);

private:
	bxgi::COLVersionManager*		m_pVersionManager;
	
	//std::unordered_map<EPlatformedGame, std::unordered_map<std::string, uint32>> umapGameMaterialIds; // todo
};