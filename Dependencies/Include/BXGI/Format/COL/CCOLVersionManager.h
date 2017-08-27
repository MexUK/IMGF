#pragma once

#include "nsbxgi.h"
#include "Object/CManager.h"
#include "ECOLVersion.h"
#include "Pool/CVectorPool.h"
#include "Game/EGame.h"
#include <string>
#include <unordered_map>

class bxgi::CCOLVersion;

class bxgi::CCOLVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxgi::CCOLVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	CCOLVersion*									addVersion(ECOLVersion uiCOLVersion, std::string strVersionText, std::vector<EGame> vecGames = std::vector<EGame>());

	std::string										getVersionText(uint32 uiRawVersion);

	bxgi::CCOLVersion*								getEntryByVersionId(bxgi::ECOLVersion ECOLVersionValue);

private:
	void											initCOLVersions(void);
	void											uninitCOLVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};