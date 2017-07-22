#ifndef CRageManager_H
#define CRageManager_H

#include "bxa.h"
#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"

class bxa::CRageResourceTypeManager;

class bxa::CRageManager : public bxa::CManager, public bxa::CSingleton<CRageManager>
{
public:
	CRageManager(void);
	~CRageManager(void);

	void											init(void);
	void											uninit(void);

	bxa::CRageResourceTypeManager*						getResourceTypeManager(void) { return m_pResourceTypeManager; }

	static uint32									getPackedOffset(uint32 uiOffset);
	static uint32									getPackedDataOffset(uint32 uiOffset);

private:
	bxa::CRageResourceTypeManager*						m_pResourceTypeManager;
};

#endif