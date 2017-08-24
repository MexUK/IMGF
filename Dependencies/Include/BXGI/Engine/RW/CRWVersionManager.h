#ifndef CRWVersionManager_H
#define CRWVersionManager_H

#include "bxgi.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxgi::CRWVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxgi::CRWVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getVersionText(uint32 uiRawVersion);

	CRWVersion*										getEntryByVersionCC(uint32 uiVersionCC);
	CRWVersion*										getEntryByVersionId(bxgi::eRWVersion eRWVersion);
	CRWVersion*										getRWVersionFromGame(bxgi::ePlatformedGame ePlatformedGame);
	std::unordered_map<uint32, std::vector<std::string>>		getVersionNames(void);

private:
	void											initRWVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};

#endif