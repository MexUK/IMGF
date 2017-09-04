#pragma once

#include "nsbxgi.h"
#include "Object/Singleton.h"
#include "Object/Manager.h"
#include "RWVersion.h"
#include <string>

class bxgi::RWVersionManager;

class bxgi::RWManager : public bxcf::Manager, public bxcf::Singleton<bxgi::RWManager>
{
public:
	RWManager(void);
	~RWManager(void);

	void											init(void);
	void											uninit(void);

	bxgi::RWVersionManager*						getVersionManager(void) { return m_pVersionManager; }

	void											setSerializationRWVersion(uint32 uiSerializationRWVersion) { m_uiSerializationRWVersion = uiSerializationRWVersion; }
	uint32											getSerializationRWVersion(void) { return m_uiSerializationRWVersion; }

	static bool										isRWFileExtension(std::string& strFileExtension);
	static bool										isRWModelExtension(std::string& strFileExtension);
	static bool										isRWTextureExtension(std::string& strFileExtension);

private:
	bxgi::RWVersionManager*						m_pVersionManager;
	uint32											m_uiSerializationRWVersion;
};