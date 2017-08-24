#ifndef CRWManager_H
#define CRWManager_H

#include "bxgi.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "CRWVersion.h"
#include <string>

class bxgi::CRWVersionManager;

class bxgi::CRWManager : public bxcf::CManager, public bxcf::CSingleton<bxgi::CRWManager>
{
public:
	CRWManager(void);
	~CRWManager(void);

	void											init(void);
	void											uninit(void);

	bxgi::CRWVersionManager*						getVersionManager(void) { return m_pVersionManager; }

	static std::string								getRWVersionText(CRWVersion* pRWVersion) { return getRWVersionText(pRWVersion == nullptr ? RW_VERSION_UNKNOWN : pRWVersion->getVersionId()); }
	static std::string								getRWVersionText(bxgi::eRWVersion eRWVersionValue);

	std::string										getGameName(bxgi::ePlatformedGame ePlatformedGame);

	void											setRWVersionCCForSerialization(uint32 uiRWVersionCC) { m_uiRWVersionCCForSerialization = uiRWVersionCC; }
	uint32											getRWVersionCCForSerialization(void) { return m_uiRWVersionCCForSerialization; }

	static bool										isRWFileExtension(std::string& strFileExtension);
	static bool										isRWModelExtension(std::string& strFileExtension);
	static bool										isRWTextureExtension(std::string& strFileExtension);

private:
	bxgi::CRWVersionManager*						m_pVersionManager;
	uint32											m_uiRWVersionCCForSerialization;
};

#endif