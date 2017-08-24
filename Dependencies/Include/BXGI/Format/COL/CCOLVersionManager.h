#ifndef CCOLVersionManager_H
#define CCOLVersionManager_H

#include "bxgi.h"
#include "Object/CManager.h"
#include "eCOLVersion.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <unordered_map>

class bxgi::CCOLVersion;

class bxgi::CCOLVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxgi::CCOLVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getVersionText(uint32 uiRawVersion);

	bxgi::CCOLVersion*								getEntryByVersionId(bxgi::eCOLVersion eCOLVersionValue);

private:
	void											initCOLVersions(void);
	void											uninitCOLVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};

#endif