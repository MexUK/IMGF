#pragma once

#include "nsbxgi.h"
#include "Object/Manager.h"
#include "RWVersion.h"
#include "Pool/VectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxgi::RWVersionManager : public bxcf::Manager, public bxcf::VectorPool<bxgi::RWVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	RWVersion*										addVersion(uint32 uiRawVersion, ERWVersion uiVersionId, bxcf::fileType::EFileType uiFileType, std::vector<bxgi::EPlatformedGame> vecPlatformedGames);

	std::string										getVersionText(uint32 uiRawVersion);

	RWVersion*										getEntryByVersionCC(uint32 uiVersionCC);
	RWVersion*										getEntryByVersionId(bxgi::ERWVersion ERWVersion);
	RWVersion*										getRWVersionFromGame(bxgi::EPlatformedGame EPlatformedGame);
	std::unordered_map<uint32, std::vector<std::string>>		getVersionNames(void);

private:
	void											initRWVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};