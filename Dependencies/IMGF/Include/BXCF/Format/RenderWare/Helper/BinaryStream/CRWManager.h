#ifndef CRWManager_H
#define CRWManager_H

#include "bxcf.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include <string>

class bxcf::CRWVersionManager;

class bxcf::CRWManager : public bxcf::CManager, public bxcf::CSingleton<bxcf::CRWManager>
{
public:
	CRWManager(void);
	~CRWManager(void);

	void											init(void);
	void											uninit(void);

	bxcf::CRWVersionManager*						getVersionManager(void) { return m_pVersionManager; }

	static std::string								getRWVersionText(CRWVersion* pRWVersion) { return getRWVersionText(pRWVersion == nullptr ? RW_VERSION_UNKNOWN : pRWVersion->getVersionId()); }
	static std::string								getRWVersionText(bxcf::eRWVersion eRWVersionValue);

	std::string										getGameName(bxcf::ePlatformedGame ePlatformedGame);

	void											setRWVersionCCForSerialization(uint32 uiRWVersionCC) { m_uiRWVersionCCForSerialization = uiRWVersionCC; }
	uint32											getRWVersionCCForSerialization(void) { return m_uiRWVersionCCForSerialization; }

	static bool										isRWFileExtension(std::string& strFileExtension);
	static bool										isRWModelExtension(std::string& strFileExtension);
	static bool										isRWTextureExtension(std::string& strFileExtension);

private:
	bxcf::CRWVersionManager*						m_pVersionManager;
	uint32											m_uiRWVersionCCForSerialization;
};

#endif