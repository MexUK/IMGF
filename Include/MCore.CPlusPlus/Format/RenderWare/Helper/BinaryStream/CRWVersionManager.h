#ifndef CRWVersionManager_H
#define CRWVersionManager_H

#include "bxa.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include "Pool/CVectorPool.h"
#include <vector>
#include <unordered_map>

class bxa::CRWVersionManager : public bxa::CManager, public bxa::CVectorPool<bxa::CRWVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	CRWVersion*										getEntryByVersionCC(uint32 uiVersionCC);
	CRWVersion*										getEntryByVersionId(bxa::eRWVersion eRWVersion);
	CRWVersion*										getRWVersionFromGame(bxa::ePlatformedGame ePlatformedGame);
	std::unordered_map<uint32, std::vector<std::string>>		getVersionNames(void);

private:
	void											initRWVersions(void);
};

#endif