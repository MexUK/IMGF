#ifndef CRWVersionManager_H
#define CRWVersionManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include "Pool/CVectorPool.h"
#include <vector>
#include <unordered_map>

class bxcf::CRWVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxcf::CRWVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	CRWVersion*										getEntryByVersionCC(uint32 uiVersionCC);
	CRWVersion*										getEntryByVersionId(bxcf::eRWVersion eRWVersion);
	CRWVersion*										getRWVersionFromGame(bxcf::ePlatformedGame ePlatformedGame);
	std::unordered_map<uint32, std::vector<std::string>>		getVersionNames(void);

private:
	void											initRWVersions(void);
};

#endif