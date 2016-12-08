#ifndef CRWManager_H
#define CRWManager_H

#include "mcore.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include <string>

class mcore::CRWVersionManager;

class mcore::CRWManager : public mcore::CManager, public mcore::CSingleton<mcore::CRWManager>
{
public:
	CRWManager(void);
	~CRWManager(void);

	void											init(void);
	void											uninit(void);

	mcore::CRWVersionManager*								getVersionManager(void) { return m_pVersionManager; }

	static std::string								getRWVersionText(CRWVersion* pRWVersion) { return getRWVersionText(pRWVersion == nullptr ? RW_VERSION_UNKNOWN : pRWVersion->getVersionId()); }
	static std::string								getRWVersionText(mcore::eRWVersion eRWVersionValue);

	std::string										getGameName(mcore::ePlatformedGame ePlatformedGame);

	void											setRWVersionCCForSerialization(uint32 uiRWVersionCC) { m_uiRWVersionCCForSerialization = uiRWVersionCC; }
	uint32											getRWVersionCCForSerialization(void) { return m_uiRWVersionCCForSerialization; }

private:
	mcore::CRWVersionManager*								m_pVersionManager;
	uint32											m_uiRWVersionCCForSerialization;
};

#endif