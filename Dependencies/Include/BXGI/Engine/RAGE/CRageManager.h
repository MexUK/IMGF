#ifndef CRageManager_H
#define CRageManager_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include <string>

class bxgi::CRageResourceTypeManager;

class bxgi::CRageManager : public bxcf::CManager, public bxcf::CSingleton<CRageManager>
{
public:
	CRageManager(void);
	~CRageManager(void);

	void											init(void);
	void											uninit(void);

	bxgi::CRageResourceTypeManager*					getResourceTypeManager(void) { return m_pResourceTypeManager; }

	static uint32									getPackedOffset(uint32 uiOffset);
	static uint32									getPackedDataOffset(uint32 uiOffset);

	static bool										isRageFileExtension(std::string& strFileExtension);
	static bool										isRageModelExtension(std::string& strFileExtension);
	static bool										isRageTextureExtension(std::string& strFileExtension);
	static bool										isRageCollisionExtension(std::string& strFileExtension);

private:
	bxgi::CRageResourceTypeManager*					m_pResourceTypeManager;
};

#endif