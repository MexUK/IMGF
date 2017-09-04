#pragma once

#include "nsbxgi.h"
#include "Object/Manager.h"
#include "ECOLVersion.h"
#include "Pool/VectorPool.h"
#include "Game/EGame.h"
#include <string>
#include <unordered_map>

class bxgi::COLVersion;

class bxgi::COLVersionManager : public bxcf::Manager, public bxcf::VectorPool<bxgi::COLVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	COLVersion*									addVersion(ECOLVersion uiCOLVersion, std::string strVersionText, std::vector<EGame> vecGames = std::vector<EGame>());

	std::string										getVersionText(uint32 uiRawVersion);

	bxgi::COLVersion*								getEntryByVersionId(bxgi::ECOLVersion ECOLVersionValue);

private:
	void											initCOLVersions(void);
	void											uninitCOLVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};