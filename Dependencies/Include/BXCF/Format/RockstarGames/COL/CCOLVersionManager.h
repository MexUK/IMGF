#ifndef CCOLVersionManager_H
#define CCOLVersionManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "eCOLVersion.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <unordered_map>

class bxcf::CCOLVersion;

class bxcf::CCOLVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxcf::CCOLVersion*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getVersionText(uint32 uiRawVersion);

	bxcf::CCOLVersion*								getEntryByVersionId(bxcf::eCOLVersion eCOLVersionValue);

private:
	void											initCOLVersions(void);
	void											uninitCOLVersions(void);

private:
	std::unordered_map<uint32, std::string>			m_umapRawVersionTexts;
};

#endif