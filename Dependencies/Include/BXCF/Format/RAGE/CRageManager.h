#ifndef CRageManager_H
#define CRageManager_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"

class bxcf::CRageResourceTypeManager;

class bxcf::CRageManager : public bxcf::CManager, public bxcf::CSingleton<CRageManager>
{
public:
	CRageManager(void);
	~CRageManager(void);

	void											init(void);
	void											uninit(void);

	bxcf::CRageResourceTypeManager*						getResourceTypeManager(void) { return m_pResourceTypeManager; }

	static uint32									getPackedOffset(uint32 uiOffset);
	static uint32									getPackedDataOffset(uint32 uiOffset);

private:
	bxcf::CRageResourceTypeManager*						m_pResourceTypeManager;
};

#endif