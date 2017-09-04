#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Object/Singleton.h"
#include "Object/Manager.h"
#include <string>

class bxgi::RageResourceTypeManager;

class bxgi::RageManager : public bxcf::Manager, public bxcf::Singleton<RageManager>
{
public:
	RageManager(void);
	~RageManager(void);

	void											init(void);
	void											uninit(void);

	bxgi::RageResourceTypeManager*					getResourceTypeManager(void) { return m_pResourceTypeManager; }

	static uint32									getPackedOffset(uint32 uiOffset);
	static uint32									getPackedDataOffset(uint32 uiOffset);

	static bool										isRageFileExtension(std::string& strFileExtension);
	static bool										isRageModelExtension(std::string& strFileExtension);
	static bool										isRageTextureExtension(std::string& strFileExtension);
	static bool										isRageCollisionExtension(std::string& strFileExtension);

private:
	bxgi::RageResourceTypeManager*					m_pResourceTypeManager;
};