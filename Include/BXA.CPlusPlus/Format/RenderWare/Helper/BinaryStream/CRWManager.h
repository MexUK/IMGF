#ifndef CRWManager_H
#define CRWManager_H

#include "BXA.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include <string>

class bxa::CRWVersionManager;

class bxa::CRWManager : public bxa::CManager, public bxa::CSingleton<bxa::CRWManager>
{
public:
	CRWManager(void);
	~CRWManager(void);

	void											init(void);
	void											uninit(void);

	bxa::CRWVersionManager*								getVersionManager(void) { return m_pVersionManager; }

	static std::string								getRWVersionText(CRWVersion* pRWVersion) { return getRWVersionText(pRWVersion == nullptr ? RW_VERSION_UNKNOWN : pRWVersion->getVersionId()); }
	static std::string								getRWVersionText(bxa::eRWVersion eRWVersionValue);

	std::string										getGameName(bxa::ePlatformedGame ePlatformedGame);

	void											setRWVersionCCForSerialization(uint32 uiRWVersionCC) { m_uiRWVersionCCForSerialization = uiRWVersionCC; }
	uint32											getRWVersionCCForSerialization(void) { return m_uiRWVersionCCForSerialization; }

private:
	bxa::CRWVersionManager*								m_pVersionManager;
	uint32											m_uiRWVersionCCForSerialization;
};

#endif