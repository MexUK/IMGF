#ifndef CRageManager_H
#define CRageManager_H

#include "mcore.h"
#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"

class mcore::CRageResourceTypeManager;

class mcore::CRageManager : public mcore::CManager, public mcore::CSingleton<CRageManager>
{
public:
	CRageManager(void);
	~CRageManager(void);

	void											init(void);
	void											uninit(void);

	mcore::CRageResourceTypeManager*						getResourceTypeManager(void) { return m_pResourceTypeManager; }

	static uint32									getPackedOffset(uint32 uiOffset);
	static uint32									getPackedDataOffset(uint32 uiOffset);

private:
	mcore::CRageResourceTypeManager*						m_pResourceTypeManager;
};

#endif