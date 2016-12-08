#ifndef CRWVersionManager_H
#define CRWVersionManager_H

#include "mcore.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include "Pool/CVectorPool.h"
#include <vector>
#include <unordered_map>

class mcore::CRWVersionManager : public mcore::CManager, public mcore::CVectorPool<mcore::CRWVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	CRWVersion*										getEntryByVersionCC(uint32 uiVersionCC);
	CRWVersion*										getEntryByVersionId(mcore::eRWVersion eRWVersion);
	CRWVersion*										getRWVersionFromGame(mcore::ePlatformedGame ePlatformedGame);
	std::unordered_map<uint32, std::vector<std::string>>		getVersionNames(void);

private:
	void											initRWVersions(void);
};

#endif